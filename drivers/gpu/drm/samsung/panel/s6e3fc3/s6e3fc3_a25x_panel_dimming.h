/*
 * linux/drivers/video/fbdev/exynos/panel/s6e3fc3/s6e3fc3_a25x_panel_dimming.h
 *
 * Header file for S6E3FC3 Dimming Driver
 *
 * Copyright (c) 2016 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __S6E3FC3_A25X_PANEL_DIMMING_H___
#define __S6E3FC3_A25X_PANEL_DIMMING_H___
#include "../dimming.h"
#include "../panel_dimming.h"

/*
 * PANEL INFORMATION
 * LDI : S6E3FC3
 * PANEL : PRE
 */
#define S6E3FC3_NR_STEP (256)
#define S6E3FC3_HBM_STEP (255)
#define S6E3FC3_TOTAL_STEP (S6E3FC3_NR_STEP + S6E3FC3_HBM_STEP)

static unsigned int a25x_brt_tbl[S6E3FC3_TOTAL_STEP] = {
	BRT(0), BRT(1), BRT(2), BRT(3), BRT(4), BRT(5), BRT(6), BRT(7), BRT(8), BRT(9), BRT(10),
	BRT(11), BRT(12), BRT(13), BRT(14), BRT(15), BRT(16), BRT(17), BRT(18), BRT(19), BRT(20),
	BRT(21), BRT(22), BRT(23), BRT(24), BRT(25), BRT(26), BRT(27), BRT(28), BRT(29), BRT(30),
	BRT(31), BRT(32), BRT(33), BRT(34), BRT(35), BRT(36), BRT(37), BRT(38), BRT(39), BRT(40),
	BRT(41), BRT(42), BRT(43), BRT(44), BRT(45), BRT(46), BRT(47), BRT(48), BRT(49), BRT(50),
	BRT(51), BRT(52), BRT(53), BRT(54), BRT(55), BRT(56), BRT(57), BRT(58), BRT(59), BRT(60),
	BRT(61), BRT(62), BRT(63), BRT(64), BRT(65), BRT(66), BRT(67), BRT(68), BRT(69), BRT(70),
	BRT(71), BRT(72), BRT(73), BRT(74), BRT(75), BRT(76), BRT(77), BRT(78), BRT(79), BRT(80),
	BRT(81), BRT(82), BRT(83), BRT(84), BRT(85), BRT(86), BRT(87), BRT(88), BRT(89), BRT(90),
	BRT(91), BRT(92), BRT(93), BRT(94), BRT(95), BRT(96), BRT(97), BRT(98), BRT(99), BRT(100),
	BRT(101), BRT(102), BRT(103), BRT(104), BRT(105), BRT(106), BRT(107), BRT(108), BRT(109), BRT(110),
	BRT(111), BRT(112), BRT(113), BRT(114), BRT(115), BRT(116), BRT(117), BRT(118), BRT(119), BRT(120),
	BRT(121), BRT(122), BRT(123), BRT(124), BRT(125), BRT(126), BRT(127), BRT(128), BRT(129), BRT(130),
	BRT(131), BRT(132), BRT(133), BRT(134), BRT(135), BRT(136), BRT(137), BRT(138), BRT(139), BRT(140),
	BRT(141), BRT(142), BRT(143), BRT(144), BRT(145), BRT(146), BRT(147), BRT(148), BRT(149), BRT(150),
	BRT(151), BRT(152), BRT(153), BRT(154), BRT(155), BRT(156), BRT(157), BRT(158), BRT(159), BRT(160),
	BRT(161), BRT(162), BRT(163), BRT(164), BRT(165), BRT(166), BRT(167), BRT(168), BRT(169), BRT(170),
	BRT(171), BRT(172), BRT(173), BRT(174), BRT(175), BRT(176), BRT(177), BRT(178), BRT(179), BRT(180),
	BRT(181), BRT(182), BRT(183), BRT(184), BRT(185), BRT(186), BRT(187), BRT(188), BRT(189), BRT(190),
	BRT(191), BRT(192), BRT(193), BRT(194), BRT(195), BRT(196), BRT(197), BRT(198), BRT(199), BRT(200),
	BRT(201), BRT(202), BRT(203), BRT(204), BRT(205), BRT(206), BRT(207), BRT(208), BRT(209), BRT(210),
	BRT(211), BRT(212), BRT(213), BRT(214), BRT(215), BRT(216), BRT(217), BRT(218), BRT(219), BRT(220),
	BRT(221), BRT(222), BRT(223), BRT(224), BRT(225), BRT(226), BRT(227), BRT(228), BRT(229), BRT(230),
	BRT(231), BRT(232), BRT(233), BRT(234), BRT(235), BRT(236), BRT(237), BRT(238), BRT(239), BRT(240),
	BRT(241), BRT(242), BRT(243), BRT(244), BRT(245), BRT(246), BRT(247), BRT(248), BRT(249), BRT(250),
	BRT(251), BRT(252), BRT(253), BRT(254), BRT(255),
	BRT(256), BRT(257), BRT(258), BRT(259), BRT(260), BRT(261), BRT(262), BRT(263), BRT(264), BRT(265),
	BRT(266), BRT(267), BRT(268), BRT(269), BRT(270), BRT(271), BRT(272), BRT(273), BRT(274), BRT(275),
	BRT(276), BRT(277), BRT(278), BRT(279), BRT(280), BRT(281), BRT(282), BRT(283), BRT(284), BRT(285),
	BRT(286), BRT(287), BRT(288), BRT(289), BRT(290), BRT(291), BRT(292), BRT(293), BRT(294), BRT(295),
	BRT(296), BRT(297), BRT(298), BRT(299), BRT(300), BRT(301), BRT(302), BRT(303), BRT(304), BRT(305),
	BRT(306), BRT(307), BRT(308), BRT(309), BRT(310), BRT(311), BRT(312), BRT(313), BRT(314), BRT(315),
	BRT(316), BRT(317), BRT(318), BRT(319), BRT(320), BRT(321), BRT(322), BRT(323), BRT(324), BRT(325),
	BRT(326), BRT(327), BRT(328), BRT(329), BRT(330), BRT(331), BRT(332), BRT(333), BRT(334), BRT(335),
	BRT(336), BRT(337), BRT(338), BRT(339), BRT(340), BRT(341), BRT(342), BRT(343), BRT(344), BRT(345),
	BRT(346), BRT(347), BRT(348), BRT(349), BRT(350), BRT(351), BRT(352), BRT(353), BRT(354), BRT(355),
	BRT(356), BRT(357), BRT(358), BRT(359), BRT(360), BRT(361), BRT(362), BRT(363), BRT(364), BRT(365),
	BRT(366), BRT(367), BRT(368), BRT(369), BRT(370), BRT(371), BRT(372), BRT(373), BRT(374), BRT(375),
	BRT(376), BRT(377), BRT(378), BRT(379), BRT(380), BRT(381), BRT(382), BRT(383), BRT(384), BRT(385),
	BRT(386), BRT(387), BRT(388), BRT(389), BRT(390), BRT(391), BRT(392), BRT(393), BRT(394), BRT(395),
	BRT(396), BRT(397), BRT(398), BRT(399), BRT(400), BRT(401), BRT(402), BRT(403), BRT(404), BRT(405),
	BRT(406), BRT(407), BRT(408), BRT(409), BRT(410), BRT(411), BRT(412), BRT(413), BRT(414), BRT(415),
	BRT(416), BRT(417), BRT(418), BRT(419), BRT(420), BRT(421), BRT(422), BRT(423), BRT(424), BRT(425),
	BRT(426), BRT(427), BRT(428), BRT(429), BRT(430), BRT(431), BRT(432), BRT(433), BRT(434), BRT(435),
	BRT(436), BRT(437), BRT(438), BRT(439), BRT(440), BRT(441), BRT(442), BRT(443), BRT(444), BRT(445),
	BRT(446), BRT(447), BRT(448), BRT(449), BRT(450), BRT(451), BRT(452), BRT(453), BRT(454), BRT(455),
	BRT(456), BRT(457), BRT(458), BRT(459), BRT(460), BRT(461), BRT(462), BRT(463), BRT(464), BRT(465),
	BRT(466), BRT(467), BRT(468), BRT(469), BRT(470), BRT(471), BRT(472), BRT(473), BRT(474), BRT(475),
	BRT(476), BRT(477), BRT(478), BRT(479), BRT(480), BRT(481), BRT(482), BRT(483), BRT(484), BRT(485),
	BRT(486), BRT(487), BRT(488), BRT(489), BRT(490), BRT(491), BRT(492), BRT(493), BRT(494), BRT(495),
	BRT(496), BRT(497), BRT(498), BRT(499), BRT(500), BRT(501), BRT(502), BRT(503), BRT(504), BRT(505),
	BRT(506), BRT(507), BRT(508), BRT(509), BRT(510),
};

static unsigned int a25x_lum_tbl[S6E3FC3_A25X_TOTAL_NR_LUMINANCE] = {
	/* normal 8x32 */
	2, 2, 3, 4, 4, 5, 6, 7,
	8, 8, 9, 10, 11, 12, 13, 15,
	16, 17, 18, 19, 20, 21, 23, 24,
	25, 26, 28, 29, 30, 32, 33, 34,
	36, 37, 38, 40, 41, 42, 44, 45,
	47, 48, 50, 51, 53, 54, 56, 57,
	59, 60, 62, 63, 65, 67, 68, 70,
	71, 73, 75, 76, 78, 80, 81, 83,
	85, 86, 88, 90, 91, 93, 95, 96,
	98, 100, 102, 103, 105, 107, 109, 111,
	112, 114, 116, 118, 120, 121, 123, 125,
	127, 129, 131, 132, 134, 136, 138, 140,
	142, 144, 146, 148, 149, 151, 153, 155,
	157, 159, 161, 163, 165, 167, 169, 171,
	173, 175, 177, 179, 181, 183, 185, 187,
	189, 191, 193, 195, 197, 199, 201, 203,
	205, 207, 209, 211, 214, 216, 218, 220,
	222, 224, 226, 228, 230, 233, 235, 237,
	239, 241, 243, 245, 248, 250, 252, 254,
	256, 258, 261, 263, 265, 267, 269, 271,
	274, 276, 278, 280, 283, 285, 287, 289,
	291, 294, 296, 298, 300, 303, 305, 307,
	310, 312, 314, 316, 319, 321, 323, 326,
	328, 330, 332, 335, 337, 339, 342, 344,
	346, 349, 351, 353, 356, 358, 360, 363,
	365, 367, 370, 372, 375, 377, 379, 382,
	384, 387, 389, 391, 394, 396, 399, 401,
	403, 406, 408, 411, 413, 415, 418, 420,
	423, 425, 428, 430, 433, 435, 437, 440,
	442, 445, 447, 450, 452, 455, 457, 460,
	462, 465, 467, 470, 472, 475, 477, 480,
	482, 485, 487, 490, 492, 495, 497, 500,
	/* hbm 8x31+7 */
	502, 504, 506, 508, 510, 512, 514, 516,
	518, 520, 522, 524, 525, 527, 529, 531,
	533, 535, 537, 539, 541, 543, 545, 547,
	549, 551, 553, 555, 557, 559, 561, 563,
	565, 567, 569, 571, 573, 575, 576, 578,
	580, 582, 584, 586, 588, 590, 592, 594,
	596, 598, 600, 602, 604, 606, 608, 610,
	612, 614, 616, 618, 620, 622, 624, 625,
	627, 629, 631, 633, 635, 637, 639, 641,
	643, 645, 647, 649, 651, 653, 655, 657,
	659, 661, 663, 665, 667, 669, 671, 673,
	675, 676, 678, 680, 682, 684, 686, 688,
	690, 692, 694, 696, 698, 700, 702, 704,
	706, 708, 710, 712, 714, 716, 718, 720,
	722, 724, 725, 727, 729, 731, 733, 735,
	737, 739, 741, 743, 745, 747, 749, 751,
	753, 755, 757, 759, 761, 763, 765, 767,
	769, 771, 773, 775, 776, 778, 780, 782,
	784, 786, 788, 790, 792, 794, 796, 798,
	800, 802, 804, 806, 808, 810, 812, 814,
	816, 818, 820, 822, 824, 825, 827, 829,
	831, 833, 835, 837, 839, 841, 843, 845,
	847, 849, 851, 853, 855, 857, 859, 861,
	863, 865, 867, 869, 871, 873, 875, 876,
	878, 880, 882, 884, 886, 888, 890, 892,
	894, 896, 898, 900, 902, 904, 906, 908,
	910, 912, 914, 916, 918, 920, 922, 924,
	925, 927, 929, 931, 933, 935, 937, 939,
	941, 943, 945, 947, 949, 951, 953, 955,
	957, 959, 961, 963, 965, 967, 969, 971,
	973, 975, 976, 978, 980, 982, 984, 986,
	988, 990, 992, 994, 996, 998, 1000,
};

static unsigned int a25x_step_cnt_tbl[S6E3FC3_TOTAL_STEP] = {
	[0 ... S6E3FC3_TOTAL_STEP - 1] = 1,
};

static struct brightness_table s6e3fc3_a25x_panel_brightness_table = {
	.control_type = BRIGHTNESS_CONTROL_TYPE_GAMMA_MODE2,
	.brt = a25x_brt_tbl,
	.sz_brt = ARRAY_SIZE(a25x_brt_tbl),
	.sz_ui_brt = S6E3FC3_NR_STEP,
	.sz_hbm_brt = S6E3FC3_HBM_STEP,
	.lum = a25x_lum_tbl,
	.sz_lum = S6E3FC3_A25X_TOTAL_NR_LUMINANCE,
	.sz_ui_lum = S6E3FC3_A25X_NR_LUMINANCE,
	.sz_hbm_lum = S6E3FC3_A25X_NR_HBM_LUMINANCE,
	.sz_ext_hbm_lum = 0,
	.brt_to_step = NULL,
	.sz_brt_to_step = 0,
	.step_cnt = a25x_step_cnt_tbl,
	.sz_step_cnt = ARRAY_SIZE(a25x_step_cnt_tbl),
	.vtotal = 0,
};

static struct panel_dimming_info s6e3fc3_a25x_panel_dimming_info = {
	.name = "s6e3fc3_a25x",
	.dim_init_info = {
		NULL,
	},
	.target_luminance = -1,
	.nr_luminance = 0,
	.hbm_target_luminance = -1,
	.nr_hbm_luminance = 0,
	.extend_hbm_target_luminance = -1,
	.nr_extend_hbm_luminance = 0,
	.brt_tbl = &s6e3fc3_a25x_panel_brightness_table,
	/* dimming parameters */
	.dimming_maptbl = NULL,
	.dim_flash_on = false,
	.hbm_aor = NULL,
};
#endif /* __S6E3FC3_PANEL_DIMMING_H___ */
