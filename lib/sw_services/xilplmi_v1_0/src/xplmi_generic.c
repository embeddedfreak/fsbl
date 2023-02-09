/******************************************************************************
* Copyright (C) 2018 - 2020 Xilinx, Inc. All rights reserved.
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
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xplmi_generic.c
*
* This is the file which contains general commands.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   08/23/2018 Initial release
* 1.01  ma   02/03/2020 Change XPlmi_MeasurePerfTime to retrieve Performance
*                       time and print
*
* </pre>
*
* @note
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xplmi_generic.h"
#include "xstatus.h"
#include "xplmi_util.h"
#include "xplmi_proc.h"
#include "xplmi_hw.h"
#include "xcfupmc.h"
#include "sleep.h"
#include "xplmi_ssit.h"
#include "xplmi_event_logging.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @brief	Contains the module ID and PLM generic commands array
 *
 *****************************************************************************/
static XPlmi_Module XPlmi_Generic;

/*****************************************************************************/
/*****************************************************************************/
/**
 * @brief	This function checks if a particular PLM Command ID is supported
 * or not. Command ID is the only payload parameter.
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
int XPlmi_Features(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;

	if (Cmd->Payload[0U] < XPlmi_Generic.CmdCnt) {
		Cmd->Response[1U] = (u32)XST_SUCCESS;
	} else {
		Cmd->Response[1U] = (u32)XST_FAILURE;
	}
	Status = XST_SUCCESS;
	Cmd->Response[0U] = Status;

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides no operation. The command is supported for
 * alignment purposes. Zero command payload parameters.
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_Nop(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;

	XPlmi_Printf(DEBUG_DETAILED, "%s %p\n\r", __func__, Cmd);
	Status = XST_SUCCESS;

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function reads the device ID and fills in the response buffer.
 *			Command: GetDeviceID
 *  			Reserved[31:24]=0 Length[23:16]=[0] PLM=1 CMD_DEVID=18
 *  			Payload = 0
 *  			The command reads PMC_TAP_IDCODE register and
 *				EFUSE_CACHE_IP_DISABLE_0 register and fills the command
 *				response array with these values.
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_GetDeviceID( XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u32 ExtIdCode;

	XPlmi_Printf(DEBUG_DETAILED, "%s %p\n\r", __func__, Cmd);

	Cmd->Response[1U] = XPlmi_In32(PMC_TAP_IDCODE);
	ExtIdCode = XPlmi_In32(EFUSE_CACHE_IP_DISABLE_0)
			& EFUSE_CACHE_IP_DISABLE_0_EID_MASK;
	if (ExtIdCode != 0U) {
		if ((ExtIdCode & EFUSE_CACHE_IP_DISABLE_0_EID_SEL_MASK) == 0U) {
			ExtIdCode = (ExtIdCode & EFUSE_CACHE_IP_DISABLE_0_EID1_MASK)
						>> EFUSE_CACHE_IP_DISABLE_0_EID1_SHIFT;
		} else {
			ExtIdCode = (ExtIdCode & EFUSE_CACHE_IP_DISABLE_0_EID2_MASK)
					>> EFUSE_CACHE_IP_DISABLE_0_EID2_SHIFT;
		}
	}

	Cmd->Response[2U] = ExtIdCode;
	Status = XST_SUCCESS;

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides 32 bit mask poll command execution.
 *  		Command payload parameters are
 *				* Address
 *				* Mask
 *				* Expected Value
 *				* Timeout in us
 *				* Deferred Error flag - Optional
 *				*	0 - Return error in case of failure,
 *				*	1 - Ignore error, return success always
 *				*	2 - Defer error till the end of partition load
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_MaskPoll(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u32 Addr = Cmd->Payload[0U];
	u32 Mask = Cmd->Payload[1U];
	u32 ExpectedValue = Cmd->Payload[2U];
	u32 TimeOutInUs = Cmd->Payload[3U];
	u32 Flags = 0U;
#ifdef PLM_PRINT_PERF_POLL
	u64 PollTime = XPlmi_GetTimerValue();
	XPlmi_PerfTime PerfTime = {0U};
#endif

	/* HACK - waiting for min of 1s **/
	if (TimeOutInUs < 1000000U) {
		TimeOutInUs = 1000000U;
	}

	Status = XPlmi_UtilPoll(Addr, Mask, ExpectedValue, TimeOutInUs);
	if (Status != XST_SUCCESS) {
		XPlmi_Printf(DEBUG_GENERAL,
		"%s: Addr: 0x%0x,  Mask: 0x%0x, ExpVal: 0x%0x, "
		"Timeout: %u ...ERROR\r\n",  __func__,
		Addr, Mask, ExpectedValue, TimeOutInUs);
	} else {
		XPlmi_Printf(DEBUG_INFO,
		"%s: Addr: 0x%0x,  Mask: 0x%0x, ExpVal: 0x%0x, "
		"Timeout: %u ...Done\r\n",  __func__,
		Addr, Mask, ExpectedValue, TimeOutInUs);
	}
#ifdef PLM_PRINT_PERF_POLL
	XPlmi_MeasurePerfTime(PollTime, &PerfTime);
	XPlmi_Printf(DEBUG_PRINT_PERF,
	" %u.%u ms Poll Time: Addr: 0x%0x,  Mask: 0x%0x, ExpVal: 0x%0x, "
	"Timeout: %u \r\n",
	(u32)PerfTime.TPerfMs, (u32)PerfTime.TPerfMsFrac,
	Addr, Mask, ExpectedValue, TimeOutInUs);
#endif

	/* If command length is 5, flags are included */
	if ((Cmd->Len == XPLMI_MASKPOLL_LEN_EXT) && (Status != XST_SUCCESS)) {
		Flags = Cmd->Payload[4U] & XPLMI_MASKPOLL_FLAGS_MASK;
		if (Flags == XPLMI_MASKPOLL_FLAGS_SUCCESS) {
			/* Ignore the error */
			Status = XST_SUCCESS;
		} else if (Flags == XPLMI_MASKPOLL_FLAGS_DEFERRED_ERR) {
			/* Defer the error till the end of CDO processing */
			Status = XST_SUCCESS;
			Cmd->DeferredError = TRUE;
		} else {
			/* Return mask_poll status */
		}
	}

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides 32 bit mask write command execution.
 *  		Command payload parameters are
 *				* Address
 *				* Mask
 *				* Value
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_MaskWrite(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u32 Addr = Cmd->Payload[0U];
	u32 Mask = Cmd->Payload[1U];
	u32 Value = Cmd->Payload[2U];

	XPlmi_Printf(DEBUG_DETAILED,
		"%s, Addr: 0x%0x,  Mask 0x%0x, Value: 0x%0x\n\r",
		__func__, Addr, Mask, Value);

	XPlmi_UtilRMW(Addr, Mask, Value);
	Status = XST_SUCCESS;

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides 32 bit Write command execution.
 *  		Command payload parameters are
 *				* Address
 *				* Value
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_Write(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u32 Addr = Cmd->Payload[0U];
	u32 Value = Cmd->Payload[1U];

	XPlmi_Printf(DEBUG_DETAILED,
		"%s, Addr: 0x%0x,  Val: 0x%0x\n\r",
		__func__, Addr, Value);

	XPlmi_Out32(Addr, Value);
	Status = XST_SUCCESS;

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides delay command execution.
 *  		Command payload parameter
				Delay in micro seconds
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_Delay(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u32 Delay;

	Delay = Cmd->Payload[0U];
	XPlmi_Printf(DEBUG_DETAILED,
		"%s, Delay: %d\n\r",
		__func__, Delay);

	usleep(Delay);
	Status = XST_SUCCESS;

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides DMA write command execution.
 *  		Command payload parameters are
 *				* High Dest Addr
 *				* Low Dest Addr
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
static int XPlmi_DmaWrite(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u64 DestAddr;
	u64 SrcAddr;
	u32 Len = Cmd->PayloadLen;
	u32 Flags;
	u32 DestOffset = 0U;

	XPlmi_Printf(DEBUG_DETAILED, "%s \n\r", __func__);

	if (Cmd->ProcessedLen == 0U) {
		/* Store the destination address in resume data */
		Cmd->ResumeData[0U] = Cmd->Payload[0U];
		Cmd->ResumeData[1U] = Cmd->Payload[1U];
		SrcAddr = (u64)(UINTPTR) &Cmd->Payload[2U];
		Len -= 2U;
	} else {
		SrcAddr = (u64)(UINTPTR) &Cmd->Payload[0U];
		/* Decrement the destination offset by CMD params */
		DestOffset = 2U;
	}

	DestAddr = (u64) Cmd->ResumeData[0U];
	DestAddr = ((u64)Cmd->ResumeData[1U] | (DestAddr << 32U));
	DestAddr += ((Cmd->ProcessedLen - DestOffset) * XPLMI_WORD_LEN);

	/* Set DMA flags to DMA0 and INCR */
	Flags = XPLMI_PMCDMA_0;

	Status = XPlmi_DmaXfr(SrcAddr, DestAddr, Len, Flags);
	if(Status != XST_SUCCESS) {
		XPlmi_Printf(DEBUG_GENERAL, "DMA WRITE Failed\n\r");
		goto END;
	}

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides 64 bit mask poll command execution.
 *  		Command payload parameters are
 *				* High Address
 *				* Low Address
 *				* Mask
 *				* Expected Value
 *				* Timeout in us
 *				* Deferred Error flag - Optional
 *				*	0 - Return error in case of failure,
 *				*	1 - Ignore error, return success always
 *				*	2 - Defer error till the end of partition load
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
static int XPlmi_MaskPoll64(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u64 Addr = (((u64)Cmd->Payload[0U] << 32U) | Cmd->Payload[1U]);
	u32 Mask = Cmd->Payload[2U];
	u32 ExpectedValue = Cmd->Payload[3U];
	u32 TimeOutInUs = Cmd->Payload[4U];
	u32 Flags = 0U;

	XPlmi_Printf(DEBUG_DETAILED,
		"%s, Addr: 0x%0x%08x,  Mask 0x%0x, ExpVal: 0x%0x, Timeout: %u\n\r",
		__func__, (u32)(Addr >> 32U), (u32)Addr, Mask, ExpectedValue, TimeOutInUs);

	Status = XPlmi_UtilPoll64(Addr, Mask, ExpectedValue, TimeOutInUs);
	if (Status != XST_SUCCESS) {
		Status = XPLMI_ERR_MASKPOLL64;
	}

	/* If command length is 6, flags are included */
	if ((Cmd->Len == XPLMI_MASKPOLL64_LEN_EXT) && (Status != XST_SUCCESS)) {
		Flags = Cmd->Payload[5U] & XPLMI_MASKPOLL_FLAGS_MASK;
		if (Flags == XPLMI_MASKPOLL_FLAGS_SUCCESS) {
			/* Ignore the error */
			Status = XST_SUCCESS;
		} else if (Flags == XPLMI_MASKPOLL_FLAGS_DEFERRED_ERR) {
			/* Defer the error till the end of CDO processing */
			Status = XST_SUCCESS;
			Cmd->DeferredError = TRUE;
		} else {
			/* Return mask_poll status */
		}
	}

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides 64 bit mask write command execution.
 *  		Command payload parameters are
 *				* High Address
 *				* Low Address
 *				* Mask
 *				* Value
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_MaskWrite64(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u64 Addr = (((u64)Cmd->Payload[0U] << 32U) | Cmd->Payload[1U]);
	u32 Mask = Cmd->Payload[2U];
	u32 Value = Cmd->Payload[3U];
	u32 ReadVal;

	XPlmi_Printf(DEBUG_DETAILED,
		"%s, Addr: 0x%0x%08x,  Mask 0x%0x, Val: 0x%0x\n\r",
		__func__, (u32)(Addr >> 32U), (u32)Addr, Mask, Value);

	/*
	 * Read the Register value
	 */
	ReadVal = XPlmi_In64(Addr);
	ReadVal = (ReadVal & (~Mask)) | (Mask & Value);
	XPlmi_Out64(Addr, ReadVal);
	Status = XST_SUCCESS;

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides 64 bit write command execution.
 *  		Command payload parameters are
 *				* High Address
 *				* Low Address
 *				* Value
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_Write64(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u64 Addr = (((u64)Cmd->Payload[0U] << 32U) | Cmd->Payload[1U]);
	u32 Value = Cmd->Payload[2U];

	XPlmi_Printf(DEBUG_DETAILED,
		"%s, Addr: 0x%0x%08x,  Val: 0x%0x\n\r",
		__func__, (u32)(Addr>>32), (u32)Addr, Value);

	XPlmi_Out64(Addr, Value);
	Status = XST_SUCCESS;

	return Status;
}

/*****************************************************************************/
/**
 * @brief	The function reads data from Npi address space.
 *
 * @param	Npi Src Address
 * @param   Destination Address
 * @param	Len is number of words to be read
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 ******************************************************************************/
int XPlmi_NpiRead(u64 SrcAddr, u64 DestAddr, u32 Len)
{
	int Status = XST_FAILURE;
	u32 RegVal;
	u32 Count = 0U;
	u32 Offset;
	u32 ProcWords = 0U;
	u32 RegValAddr = (u32)(&RegVal);

	/* For NPI READ command, the source address needs to be
	 * 16 byte aligned. Use XPlmi_Out64 till the destination address
	 * becomes 16 byte aligned.
	 */
	while ((ProcWords < Len) && (((SrcAddr + Count) & (0xFU)) != 0U)) {
		RegVal = XPlmi_In64(SrcAddr + Count);
		if (DestAddr != XPLMI_SBI_DEST_ADDR) {
			XPlmi_Out64(DestAddr + (ProcWords * XPLMI_WORD_LEN), RegVal);
		} else {
			Status = XPlmi_DmaSbiXfer(RegValAddr, 1U, XPLMI_PMCDMA_1);
			if (Status != XST_SUCCESS) {
				goto END;
			}
		}
		Count += XPLMI_WORD_LEN;
		++ProcWords;
	}

	if (DestAddr != XPLMI_SBI_DEST_ADDR) {
		Status = XPlmi_DmaXfr((u64)(SrcAddr + Count), (u64)(DestAddr + Count),
			((Len - ProcWords) & (~(XPLMI_WORD_LEN - 1U))), XPLMI_PMCDMA_0);
	} else {
		Status = XPlmi_DmaSbiXfer((u64)(SrcAddr + Count),
			((Len - ProcWords) & (~(XPLMI_WORD_LEN - 1U))), XPLMI_PMCDMA_1);
	}
	if (Status != XST_SUCCESS) {
		goto END;
	}

	/* For NPI_READ command, Offset variable should
	 *  be updated with the unaligned bytes.
	 */
	ProcWords = ProcWords + ((Len - ProcWords) & (~(XPLMI_WORD_LEN - 1U)));
	Offset = ProcWords * XPLMI_WORD_LEN;

	while (ProcWords < Len) {
		RegVal = XPlmi_In64(SrcAddr + Offset);
		if (DestAddr != XPLMI_SBI_DEST_ADDR) {
			XPlmi_Out64(DestAddr + Offset, RegVal);
		} else {
			Status = XPlmi_DmaSbiXfer(RegValAddr, 1U, XPLMI_PMCDMA_1);
			if (Status != XST_SUCCESS) {
				goto END;
			}
		}
		Offset += XPLMI_WORD_LEN;
		ProcWords++;
	}

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides DMA Xfer command execution.
 *  		Command payload parameters are
 *				* High Src Addr
 *				* Low Src Addr
 *				* High Dest Addr
 *				* Low Dest Addr
 *				* Params - AXI burst type (Fixed/INCR)
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
static int XPlmi_DmaXfer(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u64 DestAddr;
	u64 SrcAddr;
	u32 Len;
	u32 Flags;

	XPlmi_Printf(DEBUG_DETAILED, "%s \n\r", __func__);

	if (Cmd->ProcessedLen == 0U) {
		/* Store the command fields in resume data */
		Cmd->ResumeData[0U] = Cmd->Payload[0U];
		Cmd->ResumeData[1U] = Cmd->Payload[1U];
		Cmd->ResumeData[2U] = Cmd->Payload[2U];
		Cmd->ResumeData[3U] = Cmd->Payload[3U];
		Cmd->ResumeData[4U] = Cmd->Payload[4U];
		Cmd->ResumeData[5U] = Cmd->Payload[5U];
	}

	SrcAddr = (u64)Cmd->ResumeData[0U];
	SrcAddr = ((u64)Cmd->ResumeData[1U] | (SrcAddr << 32U));
	DestAddr = (u64)Cmd->ResumeData[2U];
	DestAddr = ((u64)Cmd->ResumeData[3U] | (DestAddr << 32U));
	DestAddr += (Cmd->ProcessedLen * XPLMI_WORD_LEN);
	Len = Cmd->ResumeData[4U];

	/* Set DMA flags to DMA0 */
	Flags = Cmd->ResumeData[5U] | XPLMI_PMCDMA_0;

	if (DestAddr == XPLMI_SBI_DEST_ADDR) {
		XPlmi_UtilRMW(SLAVE_BOOT_SBI_MODE,
			SLAVE_BOOT_SBI_MODE_SELECT_MASK,
			SLAVE_BOOT_SBI_MODE_SELECT_MASK);
		if ((Flags & XPLMI_DMA_SRC_NPI) == XPLMI_DMA_SRC_NPI) {
			Status = XPlmi_NpiRead(SrcAddr,DestAddr,Len);
		} else {
			Status = XPlmi_DmaSbiXfer(SrcAddr, Len, Cmd->ResumeData[5U]
				| XPLMI_PMCDMA_1);
		}
		if (Status != XST_SUCCESS) {
			XPlmi_UtilRMW(SLAVE_BOOT_SBI_MODE,
				SLAVE_BOOT_SBI_MODE_SELECT_MASK, 0U);
			goto END;
		}

		Status = XPlmi_UtilPoll(SLAVE_BOOT_SBI_STATUS,
				SLAVE_BOOT_SBI_STATUS_CMN_BUF_SPACE_MASK,
				SLAVE_BOOT_SBI_STATUS_CMN_BUF_SPACE_VAL,
				XPLMI_TIME_OUT_DEFAULT);
		if (Status != XST_SUCCESS) {
			XPlmi_UtilRMW(SLAVE_BOOT_SBI_MODE,
				SLAVE_BOOT_SBI_MODE_SELECT_MASK, 0U);
			goto END;
		}

		Status = XPlmi_UtilPoll(SLAVE_BOOT_SBI_STATUS,
				SLAVE_BOOT_SBI_STATUS_JTAG_DOUT_FIFO_SPACE_MASK,
				SLAVE_BOOT_SBI_STATUS_JTAG_DOUT_FIFO_SPACE_VAL,
				XPLMI_TIME_OUT_DEFAULT);
		XPlmi_UtilRMW(SLAVE_BOOT_SBI_MODE,
				SLAVE_BOOT_SBI_MODE_SELECT_MASK, 0U);
		if (Status != XST_SUCCESS) {
			goto END;
		}
	} else {
		if ((Flags & XPLMI_DMA_SRC_NPI) == XPLMI_DMA_SRC_NPI) {
			Status = XPlmi_NpiRead(SrcAddr, DestAddr, Len);
		} else {
			Status = XPlmi_DmaXfr(SrcAddr, DestAddr, Len, Flags);
		}
		if (Status != XST_SUCCESS) {
			XPlmi_Printf(DEBUG_GENERAL, "DMA XFER Failed\n\r");
			goto END;
		}
	}

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides INIT_SEQ command execution.
 *  		Command payload parameters are
 *				* DATA
 *
 * @param	Cmd is pointer to the command structure and unused
 *
 * @return	XPLMI_ERR_CMD_NOT_SUPPORTED
 *
 *****************************************************************************/
static int XPlmi_InitSeq(XPlmi_Cmd * Cmd)
{
	/* For MISRA C */
	(void )Cmd;

	return XPLMI_ERR_CMD_NOT_SUPPORTED;
}

/*****************************************************************************/
/**
 * @brief	This function provides CFI READ command execution.
 *  		Command payload parameters are
 *				* Params - SMPA/JTAG/DDR
 *				* High Dest Addr
 *				* Low Dest Addr
 *				* Read Length in number of words to be read from CFU
 *				* DATA (CFU READ Packets)
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XPlmi_CfiRead(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u32 SrcType = Cmd->Payload[0U];
	u64 DestAddrHigh;
	u32 DestAddrLow;
	u32 Len = Cmd->Payload[3U];
	u32 SrcAddr = CFU_FDRO_ADDR;
	u64 DestAddr;

	XPlmi_SetMaxOutCmds(1U);
	if (SrcType == XPLMI_READBK_INTF_TYPE_DDR) {
		DestAddrHigh = Cmd->Payload[1U];
		DestAddrLow =  Cmd->Payload[2U];
		DestAddr = (DestAddrHigh << 32U) | DestAddrLow;

		Status = XPlmi_DmaXfr(CFU_FDRO_ADDR, DestAddr, Len,
			XPLMI_PMCDMA_1 | XPLMI_SRC_CH_AXI_FIXED |
						XPLMI_DMA_SRC_NONBLK);
	} else {
		if (SrcType == XPLMI_READBK_INTF_TYPE_JTAG) {
			XPlmi_UtilRMW(SLAVE_BOOT_SBI_CTRL,
				SLAVE_BOOT_SBI_CTRL_INTERFACE_MASK,
				XPLMI_SBI_CTRL_INTERFACE_JTAG);
		} else if(SrcType == XPLMI_READBK_INTF_TYPE_SMAP) {
			XPlmi_UtilRMW(SLAVE_BOOT_SBI_CTRL,
				SLAVE_BOOT_SBI_CTRL_INTERFACE_MASK,
				XPLMI_SBI_CTRL_INTERFACE_SMAP);
		} else {
			/* Do Nothing */
		}

		XPlmi_UtilRMW(SLAVE_BOOT_SBI_MODE,
			SLAVE_BOOT_SBI_MODE_SELECT_MASK,
			SLAVE_BOOT_SBI_MODE_SELECT_MASK);
		Status = XPlmi_DmaSbiXfer(CFU_FDRO_ADDR, Len, XPLMI_PMCDMA_1
				| XPLMI_SRC_CH_AXI_FIXED | XPLMI_DMA_SRC_NONBLK);
	}
	if (Status != XST_SUCCESS) {
		goto END;
	}
	XPlmi_SetMaxOutCmds(8U);
	SrcAddr = (u32)(&Cmd->Payload[4U]);

	Status = XPlmi_DmaXfr(SrcAddr, (u64)CFU_STREAM_ADDR,
		Cmd->PayloadLen - 4U, XPLMI_PMCDMA_0);

	if (SrcType == XPLMI_READBK_INTF_TYPE_DDR) {
		XPlmi_WaitForNonBlkDma();
		goto END;
	} else {
		XPlmi_WaitForNonBlkSrcDma();
	}

	Status = XPlmi_UtilPoll(SLAVE_BOOT_SBI_STATUS,
		SLAVE_BOOT_SBI_STATUS_CMN_BUF_SPACE_MASK,
		SLAVE_BOOT_SBI_STATUS_CMN_BUF_SPACE_VAL,
		XPLMI_TIME_OUT_DEFAULT);
	if (Status != XST_SUCCESS) {
		goto END;
	}

	if (SrcType == XPLMI_READBK_INTF_TYPE_SMAP) {
		Status = XPlmi_UtilPoll(SLAVE_BOOT_SBI_STATUS,
			SLAVE_BOOT_SBI_STATUS_SMAP_DOUT_FIFO_SPACE_MASK,
			SLAVE_BOOT_SBI_STATUS_SMAP_DOUT_FIFO_SPACE_VAL,
			XPLMI_TIME_OUT_DEFAULT);
	} else {
		Status = XPlmi_UtilPoll(SLAVE_BOOT_SBI_STATUS,
			SLAVE_BOOT_SBI_STATUS_JTAG_DOUT_FIFO_SPACE_MASK,
			SLAVE_BOOT_SBI_STATUS_JTAG_DOUT_FIFO_SPACE_VAL,
			XPLMI_TIME_OUT_DEFAULT);
	}
	if(Status != XST_SUCCESS) {
		goto END;
	}

END:
	XPlmi_UtilRMW(SLAVE_BOOT_SBI_MODE, SLAVE_BOOT_SBI_MODE_SELECT_MASK, 0U);
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides SET command execution.
 *  		Command payload parameters are
 *				* High Dest Addr
 *				* Low Dest Addr
 *				* Length (Length of words to set to value)
 *				* Value
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS
 *
 *****************************************************************************/
static int XPlmi_Set(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u64 DestAddrHigh = Cmd->Payload[0U];
	u32 DestAddrLow = Cmd->Payload[1U];
	u64 DestAddr = (DestAddrHigh << 32U) | DestAddrLow;
	u32 Len = Cmd->Payload[2U];
	u32 Val = Cmd->Payload[3U];
	u32 Src[XPLMI_SET_CHUNK_SIZE];
	u32 Count;
	u32 Index;
	u32 SrcAddrLow = (u32)(&Src[0U]);
	u64 SrcAddr = (u64)(SrcAddrLow);
	u32 ChunkSize;

	if (Val == XPLMI_DATA_INIT_PZM)	{
		XPlmi_EccInit(DestAddr, Len * XPLMI_WORD_LEN);
	} else {
		if (Len < XPLMI_SET_CHUNK_SIZE) {
			ChunkSize = Len;
		} else {
			ChunkSize = XPLMI_SET_CHUNK_SIZE;
		}

		for (Index = 0U; Index < ChunkSize; ++Index) {
			Src[Index] = Val;
		}

		Count = Len / XPLMI_SET_CHUNK_SIZE ;

		/* DMA in chunks of 512 Bytes */
		for (Index = 0U; Index < Count; ++Index) {
			XPlmi_DmaXfr(SrcAddr, DestAddr, XPLMI_SET_CHUNK_SIZE,
				XPLMI_PMCDMA_0);
			DestAddr += (XPLMI_SET_CHUNK_SIZE * XPLMI_WORD_LEN);
		}

		/* DMA of residual bytes */
		XPlmi_DmaXfr(SrcAddr, DestAddr, Len % XPLMI_SET_CHUNK_SIZE,
			XPLMI_PMCDMA_0);
	}

	Status = XST_SUCCESS;
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function provides DMA key hole write command execution.
 *  		Command payload parameters are
 *				* High Dest Addr
 *				* Low Dest Addr
 *				* Keyhole Size in bytes
 *				* DATA...
 *
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XPlmi_DmaWriteKeyHole(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u64 DestAddr;
	u32 SrcAddr;
	u32 Len = Cmd->PayloadLen;
	u32 Flags;
	u32 Keyholesize;
	u32 ChunkLen;
	u32 Count;
	u32* CfiDataPtr;
	u64 BaseAddr;
	u32 DestOffset;
	u32 ChunkLenTemp = 0U;
	XPlmi_Printf(DEBUG_DETAILED, "%s \n\r", __func__);

	if (Cmd->ProcessedLen == 0U) {
		/* Store the destination address in resume data */
		Cmd->ResumeData[0U] = Cmd->Payload[0U];
		Cmd->ResumeData[1U] = Cmd->Payload[1U];
		Cmd->ResumeData[2U] = Cmd->Payload[2U];
		Keyholesize = Cmd->Payload[2U];
		SrcAddr = (u32)(UINTPTR) &Cmd->Payload[3U];
		Len -= 3U;
		Cmd->ResumeData[3U] = 0U;
		DestOffset = 0U;
	} else {
		SrcAddr = (u32)(UINTPTR) &Cmd->Payload[0U];
		Keyholesize = Cmd->ResumeData[2U];
		DestOffset = 3U;
	}

	DestAddr = (u64)Cmd->ResumeData[0U];
	DestAddr = ((u64)Cmd->ResumeData[1U] | (DestAddr << 32U));
	BaseAddr = DestAddr;

	if (Cmd->KeyHoleParams.PdiSrc != 0xFFU) {
		/* This is for direct DMA to CFI from PdiSrc bypassing PMCRAM */
		Status = XPlmi_CfiWrite(SrcAddr, DestAddr, Keyholesize, Len, Cmd);
		if (Status != XST_SUCCESS) {
			goto END;
		}
	} else {
		DestAddr = (((Cmd->ProcessedLen - Cmd->ResumeData[3U] - DestOffset) *
			XPLMI_WORD_LEN) & (Keyholesize - 1U)) + BaseAddr;
		/* Set DMA flags to DMA0 */
		Flags = XPLMI_PMCDMA_0;
		if (Cmd->ProcessedLen != 0U) {
			Count = Cmd->ResumeData[3U];
			if (Count > 0U) {
				while ((Count > 0U) && (Count < 4U)) {
					CfiDataPtr = (u32*)SrcAddr;
					Cmd->ResumeData[Count + XPLMI_WORD_LEN] = *CfiDataPtr;
					SrcAddr += XPLMI_WORD_LEN;
					--Len;
					++Count;
				}
				Status = XPlmi_DmaXfr((u32)&Cmd->ResumeData[4U], DestAddr, 4U, Flags);
				if(Status != XST_SUCCESS) {
					XPlmi_Printf(DEBUG_GENERAL, "DMA WRITE Key Hole Failed\n\r");
					goto END;
				}
				DestAddr = ((Cmd->ProcessedLen-Cmd->ResumeData[3U]-DestOffset+Count)*4U)%Keyholesize + BaseAddr;
			}
			Cmd->ResumeData[3U] = 0U;
	}

	ChunkLen = Len - (Len & (XPLMI_WORD_LEN - 1U));

	if ((DestAddr + (ChunkLen * XPLMI_WORD_LEN)) > (BaseAddr + Keyholesize)) {
		ChunkLenTemp = ((BaseAddr + Keyholesize) - DestAddr) / XPLMI_WORD_LEN;
		Status = XPlmi_DmaXfr(SrcAddr, DestAddr, ChunkLenTemp, Flags);
		if (Status != XST_SUCCESS) {
			XPlmi_Printf(DEBUG_GENERAL, "DMA WRITE Key Hole Failed\n\r");
			goto END;
		}
		DestAddr = BaseAddr;
	}

	Status = XPlmi_DmaXfr(SrcAddr + (ChunkLenTemp * XPLMI_WORD_LEN),
		DestAddr, (ChunkLen - ChunkLenTemp), Flags);
	if (Status != XST_SUCCESS) {
		XPlmi_Printf(DEBUG_GENERAL, "DMA WRITE Key Hole Failed\n\r");
		goto END;
	}

		Cmd->ResumeData[3U]= Len & (XPLMI_WORD_LEN - 1U);
		CfiDataPtr = (u32*)(SrcAddr + ChunkLen * XPLMI_WORD_LEN);
		Count = 0U;
		while (ChunkLen < Len) {
			Cmd->ResumeData[Count + 4U] =  *CfiDataPtr;
			CfiDataPtr++;
			ChunkLen++;
			++Count;
		}

		/*
		* Send unaligned bytes left at the end if any
		*/
		if ((Cmd->ProcessedLen + (ChunkLen - (Len % XPLMI_WORD_LEN)) +
			(Cmd->PayloadLen - Len)) == (Cmd->Len - (Len % XPLMI_WORD_LEN))) {
			if (Count > 0U) {
				XPlmi_Printf(DEBUG_DETAILED, "Last remaining bytes\r\n");
				Status = XPlmi_DmaXfr((u32)&Cmd->ResumeData[4U], DestAddr,
					Count, Flags);
			}
		}
	}

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	Contains the array of PLM generic commands
 *
 *****************************************************************************/
static XPlmi_ModuleCmd XPlmi_GenericCmds[] =
{
	XPLMI_MODULE_COMMAND(XPlmi_Features),
	XPLMI_MODULE_COMMAND(XPlmi_MaskPoll),
	XPLMI_MODULE_COMMAND(XPlmi_MaskWrite),
	XPLMI_MODULE_COMMAND(XPlmi_Write),
	XPLMI_MODULE_COMMAND(XPlmi_Delay),
	XPLMI_MODULE_COMMAND(XPlmi_DmaWrite),
	XPLMI_MODULE_COMMAND(XPlmi_MaskPoll64),
	XPLMI_MODULE_COMMAND(XPlmi_MaskWrite64),
	XPLMI_MODULE_COMMAND(XPlmi_Write64),
	XPLMI_MODULE_COMMAND(XPlmi_DmaXfer),
	XPLMI_MODULE_COMMAND(XPlmi_InitSeq),
	XPLMI_MODULE_COMMAND(XPlmi_CfiRead),
	XPLMI_MODULE_COMMAND(XPlmi_Set),
	XPLMI_MODULE_COMMAND(XPlmi_DmaWriteKeyHole),
	XPLMI_MODULE_COMMAND(XPlmi_SsitSyncMaster),
	XPLMI_MODULE_COMMAND(XPlmi_SsitSyncSlaves),
	XPLMI_MODULE_COMMAND(XPlmi_SsitWaitSlaves),
	XPLMI_MODULE_COMMAND(XPlmi_Nop),
	XPLMI_MODULE_COMMAND(XPlmi_GetDeviceID),
	XPLMI_MODULE_COMMAND(XPlmi_EventLogging),
};

/*****************************************************************************/
/**
 * @brief	This function registers the PLM generic commands to the PLMI.
 *
 * @param	None
 *
 * @return	None
 *
 *****************************************************************************/
void XPlmi_GenericInit(void)
{
	XPlmi_Generic.Id = XPLMI_MODULE_GENERIC_ID;
	XPlmi_Generic.CmdAry = XPlmi_GenericCmds;
	XPlmi_Generic.CmdCnt = XPLMI_ARRAY_SIZE(XPlmi_GenericCmds);

	XPlmi_ModuleRegister(&XPlmi_Generic);
}

/*****************************************************************************/
/**
 * @brief	This function provides DMA transfer to CFI bypassing PMCRAM
 *
 * @param	SrcAddr is the address to read cfi data from
 * @param	DestAddr is the addres to write cfi data to.
 * @param	Keyholesize is the size of the DMA key hole in bytes
 * @param	Len is number of words already transferred
 * @param	Cmd is pointer to the command structure
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XPlmi_CfiWrite(u32 SrcAddr, u64 DestAddr, u32 Keyholesize, u32 Len,
	XPlmi_Cmd* Cmd)
{
	int Status = XST_FAILURE;
	u64 BaseAddr;
	u32 RemData;
	u32 ChunkLen;

	Status = XPlmi_DmaXfr(SrcAddr, DestAddr, Len, XPLMI_PMCDMA_0);
	if (Status != XST_SUCCESS) {
		XPlmi_Printf(DEBUG_GENERAL, "DMA WRITE Key Hole Failed\n\r");
		goto END;
	}

	BaseAddr = DestAddr;
	DestAddr = (Len * XPLMI_WORD_LEN) % Keyholesize + BaseAddr;
	SrcAddr = Cmd->KeyHoleParams.SrcAddr;
	RemData = (Cmd->Len - Cmd->PayloadLen) * XPLMI_WORD_LEN;

	if (Cmd->KeyHoleParams.Func != NULL) {
		/* The block is for qspi, ospi, sbi and smap boot modes */
		if (Cmd->KeyHoleParams.InChunkCopy == FALSE) {
			/*
			 * The block is for sbi and smap boot modes which
			 * support fixed modes
			 */
			Status = (int) Cmd->KeyHoleParams.Func(SrcAddr, DestAddr,
				RemData, XPLMI_DST_CH_AXI_FIXED);
			if (Status != XST_SUCCESS) {
				XPlmi_Printf(DEBUG_GENERAL, "DMA WRITE Key Hole Failed\n\r");
				goto END;
			}
			Cmd->ProcessedLen = Cmd->Len;
		} else {
			/*
			 * Qspi and Ospi donot support fixed modes.
			 * Hence the bitstream is copied in chunks of keyhole size.
			 * This block of code will also get executed for SSIT.
			 */
			ChunkLen =  BaseAddr + Keyholesize - DestAddr;
			if (ChunkLen > RemData) {
				ChunkLen = RemData;
			}
			Status = Cmd->KeyHoleParams.Func(
				SrcAddr, DestAddr, ChunkLen, 0U);
			if (Status != XST_SUCCESS) {
				XPlmi_Printf(DEBUG_GENERAL,
						"DMA WRITE Key Hole Failed\n\r");
				goto END;
			}
			SrcAddr += ChunkLen;
			Cmd->ProcessedLen = Len + 3U + ChunkLen / XPLMI_WORD_LEN;
			DestAddr = BaseAddr;
			RemData -= ChunkLen;

			while (RemData > 0U) {
				if (RemData > Keyholesize) {
					ChunkLen = Keyholesize;
					Status = (int) Cmd->KeyHoleParams.Func(SrcAddr,
						DestAddr, ChunkLen, 0U);
					Cmd->ProcessedLen += ChunkLen / XPLMI_WORD_LEN;
					SrcAddr += ChunkLen;
					RemData -= ChunkLen;
				} else {
					Status = Cmd->KeyHoleParams.Func(SrcAddr,
						DestAddr, RemData, 0U);
					Cmd->ProcessedLen = Cmd->Len;
					break;
				}
				if (Status != XST_SUCCESS) {
					XPlmi_Printf(DEBUG_GENERAL,
					"DMA WRITE Key Hole Failed\n\r");
					goto END;
				}
			}
		}
	} else {
		/* The code is for for direct DMA from DDR to CFI */
		Status = XPlmi_DmaXfr(SrcAddr, DestAddr, (Cmd->Len - Cmd->PayloadLen),
			XPLMI_DST_CH_AXI_FIXED | XPLMI_PMCDMA_0);
		if (Status != XST_SUCCESS) {
			XPlmi_Printf(DEBUG_GENERAL,
					"DMA WRITE Key Hole Failed\n\r");
			goto END;
		}
		Cmd->ProcessedLen = Cmd->Len;
	}
	Cmd->KeyHoleParams.ExtraWords = Cmd->Len - Cmd->PayloadLen;
	Cmd->PayloadLen = Cmd->Len + 1U;

END:
	return Status;
}
