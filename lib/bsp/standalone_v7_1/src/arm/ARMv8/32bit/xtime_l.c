/******************************************************************************
*
* Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
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
/*****************************************************************************/
/**
* @file xtime_l.c
*
* This file contains low level functions to get/set time from the Generic Counter
* register in the ARM Cortex A53 MPcore.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ------ -------- ---------------------------------------------------
* 5.2	pkp	   28/05/15 First release
* 5.5	pkp	   04/13/16 Added XTime_StartTimer API to start the global timer
*					 	counter if it is disabled. Also XTime_GetTime calls
*						this API to ensure the global timer counter is enabled
* </pre>
*
* @note		None.
*
******************************************************************************/
/***************************** Include Files *********************************/

#include "xtime_l.h"
#include "xpseudo_asm.h"
#include "xil_types.h"
#include "xil_assert.h"
#include "xil_io.h"

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions *******************************/

/************************** Constant Definitions *****************************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

/****************************************************************************/
/**
* @brief	Start the 64-bit physical timer counter.
*
* @param	None.
*
* @return	None.
*
* @note		The timer is initialized only if it is disabled. If the timer is
*			already running this function does not perform any operation.
*
****************************************************************************/
void XTime_StartTimer(void)
{
	/* Enable the counter only if it is disable */
	if(((Xil_In32(XIOU_SCNTRS_BASEADDR + XIOU_SCNTRS_CNT_CNTRL_REG_OFFSET)) &
		 XIOU_SCNTRS_CNT_CNTRL_REG_EN_MASK) != XIOU_SCNTRS_CNT_CNTRL_REG_EN){

		/*write frequency to System Time Stamp Generator Register*/
		Xil_Out32((XIOU_SCNTRS_BASEADDR + XIOU_SCNTRS_FREQ_REG_OFFSET),
					XIOU_SCNTRS_FREQ);

		/*Enable the counter*/
		Xil_Out32((XIOU_SCNTRS_BASEADDR + XIOU_SCNTRS_CNT_CNTRL_REG_OFFSET),
					XIOU_SCNTRS_CNT_CNTRL_REG_EN);
	}
}
/****************************************************************************/
/**
* @brief	Timer of A53 runs continuously and the time can not be set as
*			desired. This API doesn't contain anything. It is defined to have
*			uniformity across platforms.
*
* @param	Xtime_Global: 64bit Value to be written to the Global Timer Counter
*			Register. But since the function does not contain anything, the
*			value is not used for anything.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void XTime_SetTime(XTime Xtime_Global)
{
	(void) Xtime_Global;
/*As the generic timer of A53 runs constantly time can not be set as desired
so the API is left unimplemented*/
}

/****************************************************************************/
/**
* @brief	Get the time from the physical timer counter register.
*
* @param	Xtime_Global: Pointer to the 64-bit location to be updated with
*			the current value in physical timer counter.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void XTime_GetTime(XTime *Xtime_Global)
{
	/* Start global timer counter, it will only be enabled if it is disabled */
	XTime_StartTimer();

	*Xtime_Global = arch_counter_get_cntvct();
}