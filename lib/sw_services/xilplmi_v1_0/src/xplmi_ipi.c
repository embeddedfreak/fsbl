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
 * @file xplmi_ipi.c
 *
 * This is the file which contains ipi manager code.
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
/***************************** Include Files *********************************/
#include "xplmi_ipi.h"
#include "xplmi_proc.h"
#include "xplmi_generic.h"
#include "xplmi_hw.h"

#ifdef XPAR_XIPIPSU_0_DEVICE_ID
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/* Instance of IPI Driver */
static XIpiPsu IpiInst;
u32 IpiMaskList[XPLMI_IPI_MASK_COUNT] = {0U};

/*****************************************************************************/
/**
 * @brief	This function initializes the IPI.
 *
 * @param	None
 *
 * @return	Status	IPI initialization status
 *
 *****************************************************************************/
int XPlmi_IpiInit(void)
{
	int Status = XST_FAILURE;
	XIpiPsu_Config *IpiCfgPtr;
	u32 Index;

	/* Load Config for Processor IPI Channel */
	IpiCfgPtr = XIpiPsu_LookupConfig(XPAR_XIPIPSU_0_DEVICE_ID);
	if (IpiCfgPtr == NULL) {
		Status = XST_FAILURE;
		goto END;
	}

	/* Init Mask Lists */
	for (Index = 0U; Index < XPLMI_IPI_MASK_COUNT; Index++) {
		IpiMaskList[Index] = IpiCfgPtr->TargetList[Index].Mask;
	}

	/* Initialize the Instance pointer */
	Status = XIpiPsu_CfgInitialize(&IpiInst, IpiCfgPtr,
			IpiCfgPtr->BaseAddress);
	if (XST_SUCCESS != Status) {
		goto END;
	}

	/* Enable IPI from all Masters */
	for (Index = 0U; Index < XPLMI_IPI_MASK_COUNT; Index++) {
		XIpiPsu_InterruptEnable(&IpiInst,
			IpiCfgPtr->TargetList[Index].Mask);
	}

	/*
	 * Enable the IPI IRQ
	 */
	XPlmi_PlmIntrEnable(XPLMI_IPI_IRQ);

END:
	XPlmi_Printf(DEBUG_DETAILED,
			"%s: IPI init status: 0x%x\n\r", __func__, Status);
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This is the handler for IPI interrupts.
 *
 * @param	Data is unused and required for compliance with other
 *          interrupt handlers.
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XPlmi_IpiDispatchHandler(void *Data)
{
	int Status = XST_FAILURE;
	u32 SrcCpuMask;
	u32 Payload[XPLMI_IPI_MAX_MSG_LEN] = {0U};
	u32 MaskIndex;
	XPlmi_Cmd Cmd;

	/* For MISRA C */
	(void )Data;

	SrcCpuMask = Xil_In32(IPI_PMC_ISR);

	for (MaskIndex = 0; MaskIndex < XPLMI_IPI_MASK_COUNT; MaskIndex++) {
		if ((SrcCpuMask & IpiMaskList[MaskIndex]) != 0U) {
			Status = XPlmi_IpiRead(IpiMaskList[MaskIndex], &Payload[0U],
				XPLMI_IPI_MAX_MSG_LEN, XIPIPSU_BUF_TYPE_MSG);
			if (Status != XST_SUCCESS) {
				goto END;
			}
			Cmd.CmdId = Payload[0U];
			Cmd.IpiMask = IpiMaskList[MaskIndex];
			Status = XPlmi_ValidateIpiCmd(Cmd.CmdId);
			if (Status != XST_SUCCESS) {
				Status = XPLMI_UPDATE_STATUS(XPLMI_ERR_IPI_CMD, 0U);
				Cmd.Response[0U] = (u32)Status;
				/* Send response to caller */
				XPlmi_IpiWrite(Cmd.IpiMask, Cmd.Response,
							XPLMI_CMD_RESP_SIZE, XIPIPSU_BUF_TYPE_RESP);
				continue;
			}

			Cmd.Len = (Cmd.CmdId >> 16U) & 255U;
			if (Cmd.Len > 6U) {
				Cmd.Len = Payload[1U];
				Cmd.Payload = (u32 *)&Payload[2U];
			} else {
				Cmd.Payload = (u32 *)&Payload[1U];
			}
			Status = XPlmi_CmdExecute(&Cmd);
			Cmd.Response[0U] = (u32)Status;

			/* Send response to caller */
			XPlmi_IpiWrite(Cmd.IpiMask, Cmd.Response, XPLMI_CMD_RESP_SIZE,
				XIPIPSU_BUF_TYPE_RESP);
		}
	}

	XPlmi_Printf(DEBUG_DETAILED, "%s: IPI processed.\n\r", __func__);
	if (XST_SUCCESS != Status) {
		XPlmi_Printf(DEBUG_GENERAL, "%s: Error: Unhandled IPI received\n\r", __func__);
	}

	if ((LpdInitialized & LPD_INITIALIZED) == LPD_INITIALIZED) {
		/* Do not ack the PSM IPI interrupt as it is acked in LibPM */
		if (0U == (SrcCpuMask & IPI_PMC_ISR_PSM_BIT_MASK)) {
			XPlmi_Out32(IPI_PMC_ISR, SrcCpuMask);
		}
	}

END:
	/* Clear and enable the GIC IPI interrupt */
	XPlmi_PlmIntrClear(XPLMI_IPI_IRQ);
	XPlmi_PlmIntrEnable(XPLMI_IPI_IRQ);

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function writes the IPI message or response to destination CPU.
 *
 * @param	DestCpuMask Destination CPU IPI mask
 * 			MsgPtr		Pointer to message to be written
 * 			MsgLen		IPI message length
 * 			Type		IPI buffer type
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XPlmi_IpiWrite(u32 DestCpuMask, u32 *MsgPtr, u32 MsgLen, u32 Type)
{
	int Status = XST_FAILURE;

	if ((LpdInitialized & LPD_INITIALIZED) == LPD_INITIALIZED) {
		if ((NULL == MsgPtr) ||
			((MsgLen == 0U) || (MsgLen > XPLMI_IPI_MAX_MSG_LEN)) ||
			((XIPIPSU_BUF_TYPE_MSG != Type) && (XIPIPSU_BUF_TYPE_RESP != Type))) {
			/* Do nothing */
		} else {
			Status = XIpiPsu_WriteMessage(&IpiInst, DestCpuMask,
				MsgPtr, MsgLen, Type);
			if (Status != XST_SUCCESS) {
				goto END;
			}
		}
		XPlmi_Printf(DEBUG_DETAILED, "%s: IPI write status: 0x%x\r\n",
				__func__, Status);
	}

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function read the IPI message or response from source CPU.
 *
 * @param	SrcCpuMask	Source CPU IPI mask
 * 			MsgPtr 		IPI read message buffer
 * 			MsgLen		IPI message length
 * 			Type		IPI buffer type
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XPlmi_IpiRead(u32 SrcCpuMask, u32 *MsgPtr, u32 MsgLen, u32 Type)
{
	int Status = XST_FAILURE;

	if ((NULL == MsgPtr) ||
			((MsgLen == 0U) || (MsgLen > XPLMI_IPI_MAX_MSG_LEN)) ||
			((XIPIPSU_BUF_TYPE_MSG != Type) && (XIPIPSU_BUF_TYPE_RESP != Type))) {
		/* Do nothing */
	} else {
		/* Read Entire Message to Buffer */
		Status = XIpiPsu_ReadMessage(&IpiInst, SrcCpuMask, MsgPtr, MsgLen,
				Type);
		if (Status != XST_SUCCESS) {
			goto END;
		}
	}
	XPlmi_Printf(DEBUG_DETAILED, "%s: IPI read status: 0x%x\r\n", __func__, Status);

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function triggers the IPI interrupt to destination CPU.
 *
 * @param	DestCpuMask Destination CPU IPI mask
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
inline int XPlmi_IpiTrigger(u32 DestCpuMask)
{
	int Status = XST_FAILURE;

	Status = XIpiPsu_TriggerIpi(&IpiInst, DestCpuMask);

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function polls for IPI acknowledgment from destination CPU.
 *
 * @param	DestCpuMask Destination CPU IPI mask
 * 			TimeOutCount Timeout value
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
inline int XPlmi_IpiPollForAck(u32 DestCpuMask, u32 TimeOutCount)
{
	int Status = XST_FAILURE;

	Status = XIpiPsu_PollForAck(&IpiInst, DestCpuMask, TimeOutCount);

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function checks whether the CmdID passed is supported
 * 			via IPI mechanism or not.
 *
 * @param	CmddId is the command ID
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XPlmi_ValidateIpiCmd(u32 CmdId)
{
	int Status = XST_FAILURE;

	if ((CmdId & XPLMI_CMD_HNDLR_MASK) == XPLMI_CMD_HNDLR_PLM_VAL) {
		/* Only DEVICE ID and Event Logging commands are allowed through IPI.
		 *  All other commands are allowed only from CDO file.
		 */
		if((((CmdId & XPLMI_PLM_GENERIC_CMD_ID_MASK) >=
				XPLMI_PLM_GENERIC_DEVICE_ID_VAL) &&
				((CmdId & XPLMI_PLM_GENERIC_CMD_ID_MASK) <=
					XPLMI_PLM_GENERIC_EVENT_LOGGING_VAL)) ||
					((CmdId & XPLMI_PLM_GENERIC_CMD_ID_MASK) ==
						XPLMI_PLM_MODULES_FEATURES_VAL)) {
			Status = XST_SUCCESS;
		}
	} else if (((CmdId & XPLMI_CMD_HNDLR_MASK) == XPLMI_CMD_HNDLR_EM_VAL) &&
				((CmdId & XPLMI_CMD_API_ID_MASK) ==
					XPLMI_PLM_MODULES_FEATURES_VAL)) {
		/*
		 * Only features command is allowed in EM module through IPI.
		 * Other EM commands are allowed only from CDO file.
		 */
		Status = XST_SUCCESS;
	} else if ((CmdId & XPLMI_CMD_HNDLR_MASK) != XPLMI_CMD_HNDLR_EM_VAL) {
		/*
		 * Other module's commands are allowed through IPI.
		 */
		Status = XST_SUCCESS;
	} else {
		/* Added for MISRA C */
	}

	return Status;
}
#endif /* XPAR_XIPIPSU_0_DEVICE_ID */
