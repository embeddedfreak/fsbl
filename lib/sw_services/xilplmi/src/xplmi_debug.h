/******************************************************************************
* Copyright (c) 2018 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file XPlmi_debug.h
*
* This file contains the code to enable debug levels in PLM.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver	Who	Date		Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a kc   07/13/2018 Initial release
* 1.01  ma   03/02/2020 Add timestamp for each PLM print
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XPLMI_DEBUG_H
#define XPLMI_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xil_printf.h"
#include "xparameters.h"
#include "xplmi_config.h"
#include "xplmi_event_logging.h"
#include "xplmi_proc.h"

/************************** Constant Definitions *****************************/
/**
 * Debug levels for PLM
 */
#define DEBUG_PRINT_ALWAYS	(0x00000001U)    /* unconditional messages */
#define DEBUG_GENERAL		(0x00000002U)    /* general debug  messages */
#define DEBUG_INFO			(0x00000004U)    /* More debug information */
#define DEBUG_DETAILED		(0x00000008U)    /* More debug information */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#ifdef PLM_PRINT_PERF
#define DEBUG_PRINT_PERF	DEBUG_PRINT_ALWAYS
#else
#define DEBUG_PRINT_PERF	(0U)
#endif

#if defined (PLM_DEBUG_DETAILED)
#define XPlmiDbgCurrentTypes ((DEBUG_DETAILED) | (DEBUG_INFO) | \
				(DEBUG_GENERAL) | (DEBUG_PRINT_ALWAYS))
#elif defined (PLM_DEBUG_INFO)
#define XPlmiDbgCurrentTypes ((DEBUG_INFO) | (DEBUG_GENERAL) | \
				(DEBUG_PRINT_ALWAYS))
#elif defined (PLM_DEBUG)
#define XPlmiDbgCurrentTypes ((DEBUG_GENERAL) | (DEBUG_PRINT_ALWAYS))
#elif defined (PLM_PRINT)
#define XPlmiDbgCurrentTypes (DEBUG_PRINT_ALWAYS)
#else
#define XPlmiDbgCurrentTypes (0U)
#endif

/* Check if UART is present in design */
#if defined (STDOUT_BASEADDRESS)
/* Check if MDM uart or PS Uart */
#if (STDOUT_BASEADDRESS == 0xF0310000U)
#define DEBUG_UART_MDM
#elif ((STDOUT_BASEADDRESS == 0xFF000000U) || \
			(STDOUT_BASEADDRESS == 0xFF010000U))
#define DEBUG_UART_PS
#endif
#endif

/************************** Function Prototypes ******************************/
/* Functions defined in xplmi_debug.c */
int XPlmi_InitUart(void);

/************************** Variable Definitions *****************************/
extern u8 LpdInitialized;

#define UART_INITIALIZED	(1U << 0U)
#define LPD_INITIALIZED		(1U << 1U)

#define XPlmi_Printf(DebugType, ...) \
	if(((DebugType) & (XPlmiDbgCurrentTypes & DebugLog.LogLevel)) != FALSE) { \
		XPlmi_PrintPlmTimeStamp(); \
		xil_printf (__VA_ARGS__); \
	}

/*****************************************************************************/
/**
 * @brief	This function resets LpdInitialized variable to 0.
 *
 * @param	None
 *
 * @return	None
 *
 *****************************************************************************/
inline void XPlmi_ResetLpdInitialized(void)
{
	LpdInitialized = FALSE;
}

#ifdef __cplusplus
}
#endif

#endif /* XPLMI_DEBUG_H */
