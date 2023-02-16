/******************************************************************************
* Copyright (c) 2018 - 2020 Xilinx, Inc. All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file xplm_proc.c
*
* This file contains the processor related code.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   03/27/2018 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xplm_proc.h"
#include "xplm_default.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
static void XPlm_ExceptionInit(void);
static void XPlm_ExceptionHandler(u32 Status);

/************************** Variable Definitions *****************************/
extern u32 _stack;
extern u32 _stack_end;

/*****************************************************************************/
/**
 * @brief This function enables the exceptions and interrupts
 * Enable interrupts from the hardware
 *
 * @param	None
 *
 * @return	None
 *
 *****************************************************************************/
static void XPlm_ExceptionInit(void)
{
	int Status = XST_FAILURE;
	u32 Index;
	Xil_ExceptionInit();

	/* Register exception handlers */
	for (Index = XIL_EXCEPTION_ID_FIRST;
	     Index <= XIL_EXCEPTION_ID_LAST; Index++)
	{
		Status = XPLMI_UPDATE_STATUS(XPLM_ERR_EXCEPTION, Index);
		Xil_ExceptionRegisterHandler(Index,
			     (Xil_ExceptionHandler)XPlm_ExceptionHandler,
			     (void *)Status);
	}

	/** Write stack high and low register for stack protection */
	mtslr(&_stack_end);
	mtshr(&_stack);
	microblaze_enable_exceptions();
}

/*****************************************************************************/
/**
 * @brief This is a function handler for all exceptions
 *
 * @param	Status Error Status that needs to be updated in Error Register.
 * Status is initialized during exception initialization having Index and
 * exception error code.
 *
 * @return	None
 *
 *****************************************************************************/
void XPlm_ExceptionHandler(u32 Status)
{
	XPlmi_Printf(DEBUG_GENERAL, "Received Exception \n\r"
		      "MSR: 0x%08x, EAR: 0x%08x, EDR: 0x%08x, ESR: 0x%08x, \n\r"
		      "R14: 0x%08x, R15: 0x%08x, R16: 0x%08x, R17: 0x%08x \n\r",
		      mfmsr(), mfear(), mfedr(), mfesr(),
		      mfgpr(r14), mfgpr(r15), mfgpr(r16), mfgpr(r17));

	XPlmi_ErrMgr(Status);

	/* Just in case if it returns */
	while(1U);
}

/*****************************************************************************/
/**
 * @brief This function initializes the processor, enables exceptions and start
 * timer
 *
 * @param	None
 * @return	Status as defined in xplmi_status.h
 *
 *****************************************************************************/
int XPlm_InitProc(void)
{
	int Status = XST_FAILURE;

	XPlm_ExceptionInit();
	Status = XPlmi_StartTimer();

	return Status;
}
