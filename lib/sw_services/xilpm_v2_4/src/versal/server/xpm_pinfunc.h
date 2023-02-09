/******************************************************************************
*
* Copyright (C) 2018-2019 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*
*
******************************************************************************/

#ifndef XPM_PINFUNC_H_
#define XPM_PINFUNC_H_

#include "xpm_device.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FUNC_NAME_SIZE		(16)		/* Function name string size */
#define MAX_GROUPS_PER_RES	(6)		/* Max No. of groups per query response */
#define INVALID_FUNC_ID 	(0xFFFFU)
#define END_OF_GRP		(0xFFU)		/* -1 */
#define RESERVED_GRP		(0xFFFEU)	/* -2 */

typedef struct XPm_PinFunc XPm_PinFunc;

enum PmPinGrpIds {
	PIN_GRP_SPI0_0,
	PIN_GRP_SPI0_0_SS0,
	PIN_GRP_SPI0_0_SS1,
	PIN_GRP_SPI0_0_SS2,
	PIN_GRP_SPI0_1,
	PIN_GRP_SPI0_1_SS0,
	PIN_GRP_SPI0_1_SS1,
	PIN_GRP_SPI0_1_SS2,
	PIN_GRP_SPI0_2,
	PIN_GRP_SPI0_2_SS0,
	PIN_GRP_SPI0_2_SS1,
	PIN_GRP_SPI0_2_SS2,
	PIN_GRP_SPI0_3,
	PIN_GRP_SPI0_3_SS0,
	PIN_GRP_SPI0_3_SS1,
	PIN_GRP_SPI0_3_SS2,
	PIN_GRP_SPI0_4,
	PIN_GRP_SPI0_4_SS0,
	PIN_GRP_SPI0_4_SS1,
	PIN_GRP_SPI0_4_SS2,
	PIN_GRP_SPI0_5,
	PIN_GRP_SPI0_5_SS0,
	PIN_GRP_SPI0_5_SS1,
	PIN_GRP_SPI0_5_SS2,
	PIN_GRP_SPI1_0,
	PIN_GRP_SPI1_0_SS0,
	PIN_GRP_SPI1_0_SS1,
	PIN_GRP_SPI1_0_SS2,
	PIN_GRP_SPI1_1,
	PIN_GRP_SPI1_1_SS0,
	PIN_GRP_SPI1_1_SS1,
	PIN_GRP_SPI1_1_SS2,
	PIN_GRP_SPI1_2,
	PIN_GRP_SPI1_2_SS0,
	PIN_GRP_SPI1_2_SS1,
	PIN_GRP_SPI1_2_SS2,
	PIN_GRP_SPI1_3,
	PIN_GRP_SPI1_3_SS0,
	PIN_GRP_SPI1_3_SS1,
	PIN_GRP_SPI1_3_SS2,
	PIN_GRP_SPI1_4,
	PIN_GRP_SPI1_4_SS0,
	PIN_GRP_SPI1_4_SS1,
	PIN_GRP_SPI1_4_SS2,
	PIN_GRP_SPI1_5,
	PIN_GRP_SPI1_5_SS0,
	PIN_GRP_SPI1_5_SS1,
	PIN_GRP_SPI1_5_SS2,
	PIN_GRP_CAN0_0,
	PIN_GRP_CAN0_1,
	PIN_GRP_CAN0_2,
	PIN_GRP_CAN0_3,
	PIN_GRP_CAN0_4,
	PIN_GRP_CAN0_5,
	PIN_GRP_CAN0_6,
	PIN_GRP_CAN0_7,
	PIN_GRP_CAN0_8,
	PIN_GRP_CAN0_9,
	PIN_GRP_CAN0_10,
	PIN_GRP_CAN0_11,
	PIN_GRP_CAN0_12,
	PIN_GRP_CAN0_13,
	PIN_GRP_CAN0_14,
	PIN_GRP_CAN0_15,
	PIN_GRP_CAN0_16,
	PIN_GRP_CAN0_17,
	PIN_GRP_CAN1_0,
	PIN_GRP_CAN1_1,
	PIN_GRP_CAN1_2,
	PIN_GRP_CAN1_3,
	PIN_GRP_CAN1_4,
	PIN_GRP_CAN1_5,
	PIN_GRP_CAN1_6,
	PIN_GRP_CAN1_7,
	PIN_GRP_CAN1_8,
	PIN_GRP_CAN1_9,
	PIN_GRP_CAN1_10,
	PIN_GRP_CAN1_11,
	PIN_GRP_CAN1_12,
	PIN_GRP_CAN1_13,
	PIN_GRP_CAN1_14,
	PIN_GRP_CAN1_15,
	PIN_GRP_CAN1_16,
	PIN_GRP_CAN1_17,
	PIN_GRP_CAN1_18,
	PIN_GRP_I2C0_0,
	PIN_GRP_I2C0_1,
	PIN_GRP_I2C0_2,
	PIN_GRP_I2C0_3,
	PIN_GRP_I2C0_4,
	PIN_GRP_I2C0_5,
	PIN_GRP_I2C0_6,
	PIN_GRP_I2C0_7,
	PIN_GRP_I2C0_8,
	PIN_GRP_I2C0_9,
	PIN_GRP_I2C0_10,
	PIN_GRP_I2C0_11,
	PIN_GRP_I2C0_12,
	PIN_GRP_I2C0_13,
	PIN_GRP_I2C0_14,
	PIN_GRP_I2C0_15,
	PIN_GRP_I2C0_16,
	PIN_GRP_I2C0_17,
	PIN_GRP_I2C1_0,
	PIN_GRP_I2C1_1,
	PIN_GRP_I2C1_2,
	PIN_GRP_I2C1_3,
	PIN_GRP_I2C1_4,
	PIN_GRP_I2C1_5,
	PIN_GRP_I2C1_6,
	PIN_GRP_I2C1_7,
	PIN_GRP_I2C1_8,
	PIN_GRP_I2C1_9,
	PIN_GRP_I2C1_10,
	PIN_GRP_I2C1_11,
	PIN_GRP_I2C1_12,
	PIN_GRP_I2C1_13,
	PIN_GRP_I2C1_14,
	PIN_GRP_I2C1_15,
	PIN_GRP_I2C1_16,
	PIN_GRP_I2C1_17,
	PIN_GRP_I2C1_18,
	PIN_GRP_I2C_PMC_0,
	PIN_GRP_I2C_PMC_1,
	PIN_GRP_I2C_PMC_2,
	PIN_GRP_I2C_PMC_3,
	PIN_GRP_I2C_PMC_4,
	PIN_GRP_I2C_PMC_5,
	PIN_GRP_I2C_PMC_6,
	PIN_GRP_I2C_PMC_7,
	PIN_GRP_I2C_PMC_8,
	PIN_GRP_I2C_PMC_9,
	PIN_GRP_I2C_PMC_10,
	PIN_GRP_I2C_PMC_11,
	PIN_GRP_I2C_PMC_12,
	PIN_GRP_TTC0_0_CLK,
	PIN_GRP_TTC0_1_CLK,
	PIN_GRP_TTC0_2_CLK,
	PIN_GRP_TTC0_3_CLK,
	PIN_GRP_TTC0_4_CLK,
	PIN_GRP_TTC0_5_CLK,
	PIN_GRP_TTC0_6_CLK,
	PIN_GRP_TTC0_7_CLK,
	PIN_GRP_TTC0_8_CLK,
	PIN_GRP_TTC0_0_WAV,
	PIN_GRP_TTC0_1_WAV,
	PIN_GRP_TTC0_2_WAV,
	PIN_GRP_TTC0_3_WAV,
	PIN_GRP_TTC0_4_WAV,
	PIN_GRP_TTC0_5_WAV,
	PIN_GRP_TTC0_6_WAV,
	PIN_GRP_TTC0_7_WAV,
	PIN_GRP_TTC0_8_WAV,
	PIN_GRP_TTC1_0_CLK,
	PIN_GRP_TTC1_1_CLK,
	PIN_GRP_TTC1_2_CLK,
	PIN_GRP_TTC1_3_CLK,
	PIN_GRP_TTC1_4_CLK,
	PIN_GRP_TTC1_5_CLK,
	PIN_GRP_TTC1_6_CLK,
	PIN_GRP_TTC1_7_CLK,
	PIN_GRP_TTC1_8_CLK,
	PIN_GRP_TTC1_0_WAV,
	PIN_GRP_TTC1_1_WAV,
	PIN_GRP_TTC1_2_WAV,
	PIN_GRP_TTC1_3_WAV,
	PIN_GRP_TTC1_4_WAV,
	PIN_GRP_TTC1_5_WAV,
	PIN_GRP_TTC1_6_WAV,
	PIN_GRP_TTC1_7_WAV,
	PIN_GRP_TTC1_8_WAV,
	PIN_GRP_TTC2_0_CLK,
	PIN_GRP_TTC2_1_CLK,
	PIN_GRP_TTC2_2_CLK,
	PIN_GRP_TTC2_3_CLK,
	PIN_GRP_TTC2_4_CLK,
	PIN_GRP_TTC2_5_CLK,
	PIN_GRP_TTC2_6_CLK,
	PIN_GRP_TTC2_7_CLK,
	PIN_GRP_TTC2_8_CLK,
	PIN_GRP_TTC2_0_WAV,
	PIN_GRP_TTC2_1_WAV,
	PIN_GRP_TTC2_2_WAV,
	PIN_GRP_TTC2_3_WAV,
	PIN_GRP_TTC2_4_WAV,
	PIN_GRP_TTC2_5_WAV,
	PIN_GRP_TTC2_6_WAV,
	PIN_GRP_TTC2_7_WAV,
	PIN_GRP_TTC2_8_WAV,
	PIN_GRP_TTC3_0_CLK,
	PIN_GRP_TTC3_1_CLK,
	PIN_GRP_TTC3_2_CLK,
	PIN_GRP_TTC3_3_CLK,
	PIN_GRP_TTC3_4_CLK,
	PIN_GRP_TTC3_5_CLK,
	PIN_GRP_TTC3_6_CLK,
	PIN_GRP_TTC3_7_CLK,
	PIN_GRP_TTC3_8_CLK,
	PIN_GRP_TTC3_0_WAV,
	PIN_GRP_TTC3_1_WAV,
	PIN_GRP_TTC3_2_WAV,
	PIN_GRP_TTC3_3_WAV,
	PIN_GRP_TTC3_4_WAV,
	PIN_GRP_TTC3_5_WAV,
	PIN_GRP_TTC3_6_WAV,
	PIN_GRP_TTC3_7_WAV,
	PIN_GRP_TTC3_8_WAV,
	PIN_GRP_WWDT0_0,
	PIN_GRP_WWDT0_1,
	PIN_GRP_WWDT0_2,
	PIN_GRP_WWDT0_3,
	PIN_GRP_WWDT0_4,
	PIN_GRP_WWDT0_5,
	PIN_GRP_WWDT1_0,
	PIN_GRP_WWDT1_1,
	PIN_GRP_WWDT1_2,
	PIN_GRP_WWDT1_3,
	PIN_GRP_WWDT1_4,
	PIN_GRP_WWDT1_5,
	PIN_GRP_SYSMON_I2C0_0,
	PIN_GRP_SYSMON_I2C0_1,
	PIN_GRP_SYSMON_I2C0_2,
	PIN_GRP_SYSMON_I2C0_3,
	PIN_GRP_SYSMON_I2C0_4,
	PIN_GRP_SYSMON_I2C0_5,
	PIN_GRP_SYSMON_I2C0_6,
	PIN_GRP_SYSMON_I2C0_7,
	PIN_GRP_SYSMON_I2C0_8,
	PIN_GRP_SYSMON_I2C0_9,
	PIN_GRP_SYSMON_I2C0_10,
	PIN_GRP_SYSMON_I2C0_11,
	PIN_GRP_SYSMON_I2C0_12,
	PIN_GRP_SYSMON_I2C0_13,
	PIN_GRP_SYSMON_I2C0_14,
	PIN_GRP_SYSMON_I2C0_15,
	PIN_GRP_SYSMON_I2C0_16,
	PIN_GRP_SYSMON_I2C0_17,
	PIN_GRP_SYSMON_I2C0_0_ALERT,
	PIN_GRP_SYSMON_I2C0_1_ALERT,
	PIN_GRP_SYSMON_I2C0_2_ALERT,
	PIN_GRP_SYSMON_I2C0_3_ALERT,
	PIN_GRP_SYSMON_I2C0_4_ALERT,
	PIN_GRP_SYSMON_I2C0_5_ALERT,
	PIN_GRP_SYSMON_I2C0_6_ALERT,
	PIN_GRP_SYSMON_I2C0_7_ALERT,
	PIN_GRP_SYSMON_I2C0_8_ALERT,
	PIN_GRP_SYSMON_I2C0_9_ALERT,
	PIN_GRP_SYSMON_I2C0_10_ALERT,
	PIN_GRP_SYSMON_I2C0_11_ALERT,
	PIN_GRP_SYSMON_I2C0_12_ALERT,
	PIN_GRP_SYSMON_I2C0_13_ALERT,
	PIN_GRP_SYSMON_I2C0_14_ALERT,
	PIN_GRP_SYSMON_I2C0_15_ALERT,
	PIN_GRP_SYSMON_I2C0_16_ALERT,
	PIN_GRP_SYSMON_I2C0_17_ALERT,
	PIN_GRP_UART0_0,
	PIN_GRP_UART0_1,
	PIN_GRP_UART0_2,
	PIN_GRP_UART0_3,
	PIN_GRP_UART0_4,
	PIN_GRP_UART0_5,
	PIN_GRP_UART0_6,
	PIN_GRP_UART0_7,
	PIN_GRP_UART0_8,
	PIN_GRP_UART0_0_CTRL,
	PIN_GRP_UART0_1_CTRL,
	PIN_GRP_UART0_2_CTRL,
	PIN_GRP_UART0_3_CTRL,
	PIN_GRP_UART0_4_CTRL,
	PIN_GRP_UART0_5_CTRL,
	PIN_GRP_UART0_6_CTRL,
	PIN_GRP_UART0_7_CTRL,
	PIN_GRP_UART0_8_CTRL,
	PIN_GRP_UART1_0,
	PIN_GRP_UART1_1,
	PIN_GRP_UART1_2,
	PIN_GRP_UART1_3,
	PIN_GRP_UART1_4,
	PIN_GRP_UART1_5,
	PIN_GRP_UART1_6,
	PIN_GRP_UART1_7,
	PIN_GRP_UART1_8,
	PIN_GRP_UART1_0_CTRL,
	PIN_GRP_UART1_1_CTRL,
	PIN_GRP_UART1_2_CTRL,
	PIN_GRP_UART1_3_CTRL,
	PIN_GRP_UART1_4_CTRL,
	PIN_GRP_UART1_5_CTRL,
	PIN_GRP_UART1_6_CTRL,
	PIN_GRP_UART1_7_CTRL,
	PIN_GRP_UART1_8_CTRL,
	PIN_GRP_GPIO0_0,
	PIN_GRP_GPIO0_1,
	PIN_GRP_GPIO0_2,
	PIN_GRP_GPIO0_3,
	PIN_GRP_GPIO0_4,
	PIN_GRP_GPIO0_5,
	PIN_GRP_GPIO0_6,
	PIN_GRP_GPIO0_7,
	PIN_GRP_GPIO0_8,
	PIN_GRP_GPIO0_9,
	PIN_GRP_GPIO0_10,
	PIN_GRP_GPIO0_11,
	PIN_GRP_GPIO0_12,
	PIN_GRP_GPIO0_13,
	PIN_GRP_GPIO0_14,
	PIN_GRP_GPIO0_15,
	PIN_GRP_GPIO0_16,
	PIN_GRP_GPIO0_17,
	PIN_GRP_GPIO0_18,
	PIN_GRP_GPIO0_19,
	PIN_GRP_GPIO0_20,
	PIN_GRP_GPIO0_21,
	PIN_GRP_GPIO0_22,
	PIN_GRP_GPIO0_23,
	PIN_GRP_GPIO0_24,
	PIN_GRP_GPIO0_25,
	PIN_GRP_GPIO1_0,
	PIN_GRP_GPIO1_1,
	PIN_GRP_GPIO1_2,
	PIN_GRP_GPIO1_3,
	PIN_GRP_GPIO1_4,
	PIN_GRP_GPIO1_5,
	PIN_GRP_GPIO1_6,
	PIN_GRP_GPIO1_7,
	PIN_GRP_GPIO1_8,
	PIN_GRP_GPIO1_9,
	PIN_GRP_GPIO1_10,
	PIN_GRP_GPIO1_11,
	PIN_GRP_GPIO1_12,
	PIN_GRP_GPIO1_13,
	PIN_GRP_GPIO1_14,
	PIN_GRP_GPIO1_15,
	PIN_GRP_GPIO1_16,
	PIN_GRP_GPIO1_17,
	PIN_GRP_GPIO1_18,
	PIN_GRP_GPIO1_19,
	PIN_GRP_GPIO1_20,
	PIN_GRP_GPIO1_21,
	PIN_GRP_GPIO1_22,
	PIN_GRP_GPIO1_23,
	PIN_GRP_GPIO1_24,
	PIN_GRP_GPIO1_25,
	PIN_GRP_GPIO2_0,
	PIN_GRP_GPIO2_1,
	PIN_GRP_GPIO2_2,
	PIN_GRP_GPIO2_3,
	PIN_GRP_GPIO2_4,
	PIN_GRP_GPIO2_5,
	PIN_GRP_GPIO2_6,
	PIN_GRP_GPIO2_7,
	PIN_GRP_GPIO2_8,
	PIN_GRP_GPIO2_9,
	PIN_GRP_GPIO2_10,
	PIN_GRP_GPIO2_11,
	PIN_GRP_GPIO2_12,
	PIN_GRP_GPIO2_13,
	PIN_GRP_GPIO2_14,
	PIN_GRP_GPIO2_15,
	PIN_GRP_GPIO2_16,
	PIN_GRP_GPIO2_17,
	PIN_GRP_GPIO2_18,
	PIN_GRP_GPIO2_19,
	PIN_GRP_GPIO2_20,
	PIN_GRP_GPIO2_21,
	PIN_GRP_GPIO2_22,
	PIN_GRP_GPIO2_23,
	PIN_GRP_GPIO2_24,
	PIN_GRP_GPIO2_25,
	PIN_GRP_EMIO0_0,
	PIN_GRP_EMIO0_1,
	PIN_GRP_EMIO0_2,
	PIN_GRP_EMIO0_3,
	PIN_GRP_EMIO0_4,
	PIN_GRP_EMIO0_5,
	PIN_GRP_EMIO0_6,
	PIN_GRP_EMIO0_7,
	PIN_GRP_EMIO0_8,
	PIN_GRP_EMIO0_9,
	PIN_GRP_EMIO0_10,
	PIN_GRP_EMIO0_11,
	PIN_GRP_EMIO0_12,
	PIN_GRP_EMIO0_13,
	PIN_GRP_EMIO0_14,
	PIN_GRP_EMIO0_15,
	PIN_GRP_EMIO0_16,
	PIN_GRP_EMIO0_17,
	PIN_GRP_EMIO0_18,
	PIN_GRP_EMIO0_19,
	PIN_GRP_EMIO0_20,
	PIN_GRP_EMIO0_21,
	PIN_GRP_EMIO0_22,
	PIN_GRP_EMIO0_23,
	PIN_GRP_EMIO0_24,
	PIN_GRP_EMIO0_25,
	PIN_GRP_EMIO0_26,
	PIN_GRP_EMIO0_27,
	PIN_GRP_EMIO0_28,
	PIN_GRP_EMIO0_29,
	PIN_GRP_EMIO0_30,
	PIN_GRP_EMIO0_31,
	PIN_GRP_EMIO0_32,
	PIN_GRP_EMIO0_33,
	PIN_GRP_EMIO0_34,
	PIN_GRP_EMIO0_35,
	PIN_GRP_EMIO0_36,
	PIN_GRP_EMIO0_37,
	PIN_GRP_EMIO0_38,
	PIN_GRP_EMIO0_39,
	PIN_GRP_EMIO0_40,
	PIN_GRP_EMIO0_41,
	PIN_GRP_EMIO0_42,
	PIN_GRP_EMIO0_43,
	PIN_GRP_EMIO0_44,
	PIN_GRP_EMIO0_45,
	PIN_GRP_EMIO0_46,
	PIN_GRP_EMIO0_47,
	PIN_GRP_EMIO0_48,
	PIN_GRP_EMIO0_49,
	PIN_GRP_EMIO0_50,
	PIN_GRP_EMIO0_51,
	PIN_GRP_EMIO0_52,
	PIN_GRP_EMIO0_53,
	PIN_GRP_EMIO0_54,
	PIN_GRP_EMIO0_55,
	PIN_GRP_EMIO0_56,
	PIN_GRP_EMIO0_57,
	PIN_GRP_EMIO0_58,
	PIN_GRP_EMIO0_59,
	PIN_GRP_EMIO0_60,
	PIN_GRP_EMIO0_61,
	PIN_GRP_EMIO0_62,
	PIN_GRP_EMIO0_63,
	PIN_GRP_EMIO0_64,
	PIN_GRP_EMIO0_65,
	PIN_GRP_EMIO0_66,
	PIN_GRP_EMIO0_67,
	PIN_GRP_EMIO0_68,
	PIN_GRP_EMIO0_69,
	PIN_GRP_EMIO0_70,
	PIN_GRP_EMIO0_71,
	PIN_GRP_EMIO0_72,
	PIN_GRP_EMIO0_73,
	PIN_GRP_EMIO0_74,
	PIN_GRP_EMIO0_75,
	PIN_GRP_EMIO0_76,
	PIN_GRP_EMIO0_77,
	PIN_GRP_GEM0_0,
	PIN_GRP_GEM0_1,
	PIN_GRP_GEM1_0,
	PIN_GRP_GEM1_1,
	PIN_GRP_TRACE0_0,
	PIN_GRP_TRACE0_1,
	PIN_GRP_TRACE0_2,
	PIN_GRP_TRACE0_0_CLK,
	PIN_GRP_TRACE0_1_CLK,
	PIN_GRP_TRACE0_2_CLK,
	PIN_GRP_MDIO0_0,
	PIN_GRP_MDIO0_1,
	PIN_GRP_MDIO1_0,
	PIN_GRP_MDIO1_1,
	PIN_GRP_GEM_TSU0_0,
	PIN_GRP_GEM_TSU0_1,
	PIN_GRP_GEM_TSU0_2,
	PIN_GRP_GEM_TSU0_3,
	PIN_GRP_PCIE0_0,
	PIN_GRP_PCIE0_1,
	PIN_GRP_PCIE0_2,
	PIN_GRP_SMAP0_0,
	PIN_GRP_USB0_0,
	PIN_GRP_SD0_0,
	PIN_GRP_SD0_4BIT_0_0,
	PIN_GRP_SD0_4BIT_0_1,
	PIN_GRP_SD0_1BIT_0_0,
	PIN_GRP_SD0_1BIT_0_1,
	PIN_GRP_SD0_1BIT_0_2,
	PIN_GRP_SD0_1BIT_0_3,
	PIN_GRP_SD0_1BIT_0_4,
	PIN_GRP_SD0_1BIT_0_5,
	PIN_GRP_SD0_1BIT_0_6,
	PIN_GRP_SD0_1BIT_0_7,
	PIN_GRP_SD0_1,
	PIN_GRP_SD0_4BIT_1_0,
	PIN_GRP_SD0_4BIT_1_1,
	PIN_GRP_SD0_1BIT_1_0,
	PIN_GRP_SD0_1BIT_1_1,
	PIN_GRP_SD0_1BIT_1_2,
	PIN_GRP_SD0_1BIT_1_3,
	PIN_GRP_SD0_1BIT_1_4,
	PIN_GRP_SD0_1BIT_1_5,
	PIN_GRP_SD0_1BIT_1_6,
	PIN_GRP_SD0_1BIT_1_7,
	PIN_GRP_SD0_0_PC,
	PIN_GRP_SD0_1_PC,
	PIN_GRP_SD0_0_CD,
	PIN_GRP_SD0_1_CD,
	PIN_GRP_SD0_0_WP,
	PIN_GRP_SD0_1_WP,
	PIN_GRP_SD1_0,
	PIN_GRP_SD1_4BIT_0_0,
	PIN_GRP_SD1_4BIT_0_1,
	PIN_GRP_SD1_1BIT_0_0,
	PIN_GRP_SD1_1BIT_0_1,
	PIN_GRP_SD1_1BIT_0_2,
	PIN_GRP_SD1_1BIT_0_3,
	PIN_GRP_SD1_1BIT_0_4,
	PIN_GRP_SD1_1BIT_0_5,
	PIN_GRP_SD1_1BIT_0_6,
	PIN_GRP_SD1_1BIT_0_7,
	PIN_GRP_SD1_1,
	PIN_GRP_SD1_4BIT_1_0,
	PIN_GRP_SD1_4BIT_1_1,
	PIN_GRP_SD1_1BIT_1_0,
	PIN_GRP_SD1_1BIT_1_1,
	PIN_GRP_SD1_1BIT_1_2,
	PIN_GRP_SD1_1BIT_1_3,
	PIN_GRP_SD1_1BIT_1_4,
	PIN_GRP_SD1_1BIT_1_5,
	PIN_GRP_SD1_1BIT_1_6,
	PIN_GRP_SD1_1BIT_1_7,
	PIN_GRP_SD1_0_PC,
	PIN_GRP_SD1_1_PC,
	PIN_GRP_SD1_0_CD,
	PIN_GRP_SD1_1_CD,
	PIN_GRP_SD1_0_WP,
	PIN_GRP_SD1_1_WP,
	PIN_GRP_OSPI0_0,
	PIN_GRP_OSPI0_0_SS,
	PIN_GRP_QSPI0_0,
	PIN_GRP_QSPI0_0_FBCLK,
	PIN_GRP_QSPI0_0_SS,
	PIN_GRP_TEST_CLK_0,
	PIN_GRP_TEST_SCAN_0,
	PIN_GRP_TAMPER_TRIGGER_0,
};

/**
 * The Pin Function class.
 */
struct XPm_PinFunc {
	char Name[FUNC_NAME_SIZE]; /**< Function name */
	u8 Id; /**< Function ID */
	u8 NumPins; /**< Number of pins needed for this function */
	u8 NumGroups; /**< Number of groups for this function */
	u16 DevIdx; /**< Device index for this function */
	u16 LmioRegMask; /**< Register mask value to select this function */
	u16 PmioRegMask; /**< Register mask value to select this function */
	u16 *Groups; /**< Array of group identifier */
};

/************************** Function Prototypes ******************************/
XStatus XPmPinFunc_Init(XPm_PinFunc *PinFunc,
	u32 Id, char *Name, XPm_Device *Device, u16 RegMask, u8 NumPins);
XStatus XPmPinFunc_AddGroup(XPm_PinFunc *PinFunc, u16 Group);

XPm_PinFunc *XPmPinFunc_GetById(u32 FuncId);
XStatus XPmPinFunc_GetNumFuncs(u32 *NumFuncs);
XStatus XPmPinFunc_GetFuncName(u32 FuncId, char *FuncName);
XStatus XPmPinFunc_GetNumFuncGroups(u32 FuncId, u32 *NumGroups);
XStatus XPmPinFunc_GetFuncGroups(u32 FuncId, u32 Index, u16 *Groups);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* XPM_PINFUNC_H_ */
