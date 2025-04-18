/*
 *
 * FocalTech TouchScreen driver.
 *
 * Copyright (c) 2012-2020, Focaltech Ltd. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*****************************************************************************
*
* File Name: focaltech_gestrue.c
*
* Author: Focaltech Driver Team
*
* Created: 2016-08-08
*
* Abstract:
*
* Reference:
*
*****************************************************************************/

/*****************************************************************************
* 1.Included header files
*****************************************************************************/
#include "focaltech_core.h"

/******************************************************************************
* Private constant and macro definitions using #define
*****************************************************************************/
#define GESTURE_SWIPE							0x22
#define GESTURE_DOUBLECLICK                     0x24
#define GESTURE_AOD						        0x25
#define GESTURE_SINGLETAP						0x27

/*****************************************************************************
* Private enumerations, structures and unions using typedef
*****************************************************************************/
/*
* gesture_id    - mean which gesture is recognised
* point_num     - points number of this gesture
* coordinate_x  - All gesture point x coordinate
* coordinate_y  - All gesture point y coordinate
* mode          - gesture enable/disable, need enable by host
*               - 1:enable gesture function(default)  0:disable
* active        - gesture work flag,
*                 always set 1 when suspend, set 0 when resume
*/
struct fts_gesture_st {
	u8 gesture_id;
	u8 point_num;
	u16 coordinate_x[FTS_GESTURE_POINTS_MAX];
	u16 coordinate_y[FTS_GESTURE_POINTS_MAX];
};

/*****************************************************************************
* Static variables
*****************************************************************************/
static struct fts_gesture_st fts_gesture_data;

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/

/*****************************************************************************
 * Static function prototypes
 *****************************************************************************/

#if !IS_ENABLED(CONFIG_SAMSUNG_PRODUCT_SHIP)
static ssize_t fts_gesture_show(
    struct device *dev, struct device_attribute *attr, char *buf)
{
	int count = 0;
	u8 val = 0;
	struct fts_ts_data *ts_data = fts_data;

	mutex_lock(&ts_data->pdata->enable_mutex);
	fts_read_reg(FTS_REG_GESTURE_EN, &val);
	count = snprintf(buf, PAGE_SIZE, "Gesture Mode:%s\n",
	                 ts_data->gesture_mode ? "On" : "Off");
	count += snprintf(buf + count, PAGE_SIZE, "Reg(0xD0)=%d\n", val);
	mutex_unlock(&ts_data->pdata->enable_mutex);

	return count;
}

static ssize_t fts_gesture_store(
    struct device *dev,
    struct device_attribute *attr, const char *buf, size_t count)
{
	struct fts_ts_data *ts_data = fts_data;

	mutex_lock(&ts_data->pdata->enable_mutex);
	if (FTS_SYSFS_ECHO_ON(buf)) {
		FTS_DEBUG("enable gesture");
		ts_data->gesture_mode = ENABLE;
	} else if (FTS_SYSFS_ECHO_OFF(buf)) {
		FTS_DEBUG("disable gesture");
		ts_data->gesture_mode = DISABLE;
	}
	mutex_unlock(&ts_data->pdata->enable_mutex);

	return count;
}

static ssize_t fts_gesture_buf_show(
    struct device *dev, struct device_attribute *attr, char *buf)
{
	int count = 0;
	int i = 0;
	struct sec_ts_plat_data *pdata = fts_data->pdata;
	struct fts_gesture_st *gesture = &fts_gesture_data;

	mutex_lock(&pdata->enable_mutex);
	count = snprintf(buf, PAGE_SIZE, "Gesture ID:%d\n", gesture->gesture_id);
	count += snprintf(buf + count, PAGE_SIZE, "Gesture PointNum:%d\n",
	                  gesture->point_num);
	count += snprintf(buf + count, PAGE_SIZE, "Gesture Points Buffer:\n");

	/* save point data,max:6 */
	for (i = 0; i < FTS_GESTURE_POINTS_MAX; i++) {
		count += snprintf(buf + count, PAGE_SIZE, "%3d(%4d,%4d) ", i,
		                  gesture->coordinate_x[i], gesture->coordinate_y[i]);
		if ((i + 1) % 4 == 0)
			count += snprintf(buf + count, PAGE_SIZE, "\n");
	}
	count += snprintf(buf + count, PAGE_SIZE, "\n");
	mutex_unlock(&pdata->enable_mutex);

	return count;
}

static ssize_t fts_gesture_buf_store(
    struct device *dev,
    struct device_attribute *attr, const char *buf, size_t count)
{
	return -EPERM;
}


/* sysfs gesture node
 *   read example: cat  fts_gesture_mode       ---read gesture mode
 *   write example:echo 1 > fts_gesture_mode   --- write gesture mode to 1
 *
 */
static DEVICE_ATTR(fts_gesture_mode, S_IRUGO | S_IWUSR, fts_gesture_show,
                   fts_gesture_store);
/*
 *   read example: cat fts_gesture_buf        --- read gesture buf
 */
static DEVICE_ATTR(fts_gesture_buf, S_IRUGO | S_IWUSR,
                   fts_gesture_buf_show, fts_gesture_buf_store);

static struct attribute *fts_gesture_mode_attrs[] = {
	&dev_attr_fts_gesture_mode.attr,
	&dev_attr_fts_gesture_buf.attr,
	NULL,
};

static struct attribute_group fts_gesture_group = {
	.attrs = fts_gesture_mode_attrs,
};

static int fts_create_gesture_sysfs(struct device *dev)
{
	int ret = 0;

	ret = sysfs_create_group(&dev->kobj, &fts_gesture_group);
	if (ret) {
		FTS_ERROR("gesture sys node create fail");
		sysfs_remove_group(&dev->kobj, &fts_gesture_group);
		return ret;
	}

	return 0;
}
#endif

static void fts_gesture_report(struct fts_ts_data *ts_data, struct fts_gesture_st *gesture)
{
	switch (gesture->gesture_id) {
	case GESTURE_SWIPE:
		sec_input_gesture_report(ts_data->dev, SPONGE_EVENT_TYPE_SPAY, 0, 0);
		break;
	case GESTURE_SINGLETAP:
		sec_input_gesture_report(ts_data->dev, SPONGE_EVENT_TYPE_SINGLE_TAP,
			gesture->coordinate_x[0], gesture->coordinate_y[0]);
		break;
	case GESTURE_DOUBLECLICK:
		FTS_DEBUG("Double Tap to wake up");
		input_report_key(ts_data->input_dev, KEY_WAKEUP, 1);
		input_sync(ts_data->input_dev);
		input_report_key(ts_data->input_dev, KEY_WAKEUP, 0);
		input_sync(ts_data->input_dev);
		break;
	case GESTURE_AOD:
		sec_input_gesture_report(ts_data->dev, SPONGE_EVENT_TYPE_AOD_DOUBLETAB,
			gesture->coordinate_x[0], gesture->coordinate_y[0]);
		break;
	default:
		break;
	}
}

/*****************************************************************************
* Name: fts_gesture_readdata
* Brief: Read information about gesture: enable flag/gesture points..., if ges-
*        ture enable, save gesture points' information, and report to OS.
*        It will be called this function every intrrupt when FTS_GESTURE_EN = 1
*
*        gesture data length: 1(enable) + 1(reserve) + 2(header) + 6 * 4
* Input: ts_data - global struct data
*        data    - gesture data buffer if non-flash, else NULL
* Output:
* Return: 0 - read gesture data successfully, the report data is gesture data
*         1 - tp not in suspend/gesture not enable in TP FW
*         -Exx - error
*****************************************************************************/
int fts_gesture_readdata(struct fts_ts_data *ts_data, u8 *data)
{
	int ret = 0;
	int i = 0;
	int index = 0;
	u8 buf[FTS_GESTURE_DATA_LEN] = { 0 };
	struct fts_gesture_st *gesture = &fts_gesture_data;

	if (!ts_data->suspended || (atomic_read(&ts_data->pdata->power_state) != SEC_INPUT_STATE_LPM)) {
		return 1;
	}
/*
	ret = fts_read_reg(FTS_REG_GESTURE_EN, &buf[0]);
	if ((ret < 0) || (buf[0] != ENABLE)) {
		FTS_DEBUG("gesture not enable in fw, don't process gesture");
		return 1;
	}
*/
	buf[2] = FTS_REG_GESTURE_OUTPUT_ADDRESS;
	ret = fts_read(&buf[2], 1, &buf[2], FTS_GESTURE_DATA_LEN - 2);
	if (ret < 0) {
		FTS_ERROR("read gesture header data fail");
		return ret;
	}

	/* init variable before read gesture point */
	memset(gesture->coordinate_x, 0, FTS_GESTURE_POINTS_MAX * sizeof(u16));
	memset(gesture->coordinate_y, 0, FTS_GESTURE_POINTS_MAX * sizeof(u16));
	gesture->gesture_id = buf[2];
	gesture->point_num = buf[3];

	if (gesture->gesture_id == 0xFE || gesture->gesture_id == 0x00)
		return 0;

	FTS_DEBUG("gesture_id=0x%x, point_num=%d", gesture->gesture_id, gesture->point_num);

	/* save point data,max:6 */
	for (i = 0; i < FTS_GESTURE_POINTS_MAX; i++) {
		index = 4 * i + 4;
		gesture->coordinate_x[i] = (u16)(((buf[0 + index] & 0x0F) << 8)
		                                 + buf[1 + index]);
		gesture->coordinate_y[i] = (u16)(((buf[2 + index] & 0x0F) << 8)
		                                 + buf[3 + index]);
	}

	/* report gesture to OS */
	fts_gesture_report(ts_data, gesture);
	return 0;
}

void fts_gesture_recovery(struct fts_ts_data *ts_data)
{
	FTS_DEBUG("gesture recovery...");

	if (ts_data->gesture_mode && ts_data->suspended) {
		if (ts_data->aot_enable)
			fts_write_reg(FTS_REG_DOUBLETAP_TO_WAKEUP_EN, !!(ts_data->gesture_mode & GESTURE_DOUBLECLICK_EN));

		if (ts_data->singletap_enable)
			fts_write_reg(FTS_REG_SINGLETAP_EN, !!(ts_data->gesture_mode & GESTURE_SINGLETAP_EN));

		if (ts_data->aod_enable)
			fts_write_reg(FTS_REG_AOD_EN, !!(ts_data->gesture_mode & GESTURE_AOD_EN));

		if (ts_data->spay_enable)
			fts_write_reg(FTS_REG_SPAY_EN, !!(ts_data->gesture_mode & GESTURE_SPAY_EN));

		fts_write_reg(FTS_REG_GESTURE_EN, ENABLE);
	}
}

int fts_gesture_suspend(struct fts_ts_data *ts_data)
{
	int i = 0;
	u8 state = 0xFF;

	if (enable_irq_wake(ts_data->irq)) {
		FTS_DEBUG("enable_irq_wake(irq:%d) fail", ts_data->irq);
	}

	if (ts_data->aot_enable)
		fts_write_reg(FTS_REG_DOUBLETAP_TO_WAKEUP_EN, !!(ts_data->gesture_mode & GESTURE_DOUBLECLICK_EN));

	if (ts_data->aod_enable)
		fts_write_reg(FTS_REG_AOD_EN, !!(ts_data->gesture_mode & GESTURE_AOD_EN));
	
	if (ts_data->singletap_enable)
		fts_write_reg(FTS_REG_SINGLETAP_EN, !!(ts_data->gesture_mode & GESTURE_SINGLETAP_EN));

	if (ts_data->spay_enable)
		fts_write_reg(FTS_REG_SPAY_EN, !!(ts_data->gesture_mode & GESTURE_SPAY_EN));

	for (i = 0; i < 5; i++) {
		fts_write_reg(FTS_REG_GESTURE_EN, ENABLE);
		sec_delay(1);
		fts_read_reg(FTS_REG_GESTURE_EN, &state);
		if (state == ENABLE)
			break;
	}

	if (i >= 5)
		FTS_ERROR("make IC enter into gesture(suspend) fail, state:0x%02X", state);
	else
		FTS_INFO("Enter into gesture(suspend) successfully");

	return 0;
}

int fts_gesture_resume(struct fts_ts_data *ts_data)
{
	int i = 0;
	u8 state = 0xFF;

	if (disable_irq_wake(ts_data->irq)) {
		FTS_DEBUG("disable_irq_wake(irq:%d) fail", ts_data->irq);
	}

	for (i = 0; i < 5; i++) {
		fts_write_reg(FTS_REG_GESTURE_EN, DISABLE);
		sec_delay(1);
		fts_read_reg(FTS_REG_GESTURE_EN, &state);
		if (state == DISABLE)
			break;
	}

	if (i >= 5)
		FTS_ERROR("make IC exit gesture(resume) fail, state:0x%02X", state);
	else
		FTS_INFO("resume from gesture successfully");

	return 0;
}

int fts_gesture_init(struct fts_ts_data *ts_data)
{
	FTS_FUNC_ENTER();

#if !IS_ENABLED(CONFIG_SAMSUNG_PRODUCT_SHIP)
	fts_create_gesture_sysfs(ts_data->dev);
#endif
	memset(&fts_gesture_data, 0, sizeof(struct fts_gesture_st));
	ts_data->gesture_mode = FTS_GESTURE_EN;

	FTS_FUNC_EXIT();
	return 0;
}

int fts_gesture_exit(struct fts_ts_data *ts_data)
{
	FTS_FUNC_ENTER();
#if !IS_ENABLED(CONFIG_SAMSUNG_PRODUCT_SHIP)
	sysfs_remove_group(&ts_data->dev->kobj, &fts_gesture_group);
#endif
	FTS_FUNC_EXIT();
	return 0;
}
