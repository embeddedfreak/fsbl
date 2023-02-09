/******************************************************************************
*
* Copyright (C) 2018 - 2020 Xilinx, Inc.  All rights reserved.
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
*
* @file xplmi_ipi.h
*
* This is the header file which contains definitions for the ipi manager
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  mg   10/09/2018 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XPLMI_IPI_H
#define XPLMI_IPI_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xparameters.h"
#include "xplmi_modules.h"
#include "xplmi_cmd.h"
#include "xil_assert.h"
#ifdef XPAR_XIPIPSU_0_DEVICE_ID
#include "xipipsu.h"

/************************** Constant Definitions *****************************/
#define XPLMI_IPI_MASK_COUNT		XIPIPSU_MAX_TARGETS
#define XPLMI_IPI_MAX_MSG_LEN		XIPIPSU_MAX_MSG_LEN

/* IPI defines */
#define IPI_BASEADDR				(0xFF300000U)
#define IPI_PMC_ISR					(IPI_BASEADDR + 0x20010U)
#define IPI_PMC_ISR_PSM_BIT_MASK	(0x1U)

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
int XPlmi_IpiInit(void);
int XPlmi_IpiDispatchHandler(void *Data);
int XPlmi_IpiWrite(u32 DestCpuMask, u32 *MsgPtr, u32 MsgLen, u32 Type);
int XPlmi_IpiRead(u32 SrcCpuMask, u32 *MsgPtr, u32 MsgLen, u32 Type);
int XPlmi_IpiTrigger(u32 DestCpuMask);
int XPlmi_IpiPollForAck(u32 DestCpuMask, u32 TimeOutCount);
int XPlmi_ValidateIpiCmd(u32 CmdId);

/************************** Variable Definitions *****************************/

/*****************************************************************************/
#endif /* XPAR_XIPIPSU_0_DEVICE_ID */

#ifdef __cplusplus
}
#endif

#endif /* XPLMI_IPI_H */
