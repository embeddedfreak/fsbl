/******************************************************************************
* Copyright (c) 2019 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
 *
 * @file xplmi_sysmon.c
 *
 * This is the file which contains SysMon manager code.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date        Changes
 * ----- ---- -------- -------------------------------------------------------
 * 1.00  sn   07/01/2019 Initial release
 *
 * </pre>
 *
 * @note
 *
 ******************************************************************************/
/***************************** Include Files *********************************/
#include "xplmi_sysmon.h"
#include "sleep.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/* Instance of SysMon Driver */
static XSysMonPsv SysMonInst;
static XSysMonPsv *SysMonInstPtr = &SysMonInst;

/*****************************************************************************/
/**
 * @brief	This function initializes the SysMon.
 *
 * @param	void
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XPlmi_SysMonInit(void)
{
	int Status = XST_FAILURE;
	XSysMonPsv_Config *ConfigPtr;

	ConfigPtr = XSysMonPsv_LookupConfig();
	if (ConfigPtr != NULL) {
		XSysMonPsv_CfgInitialize(SysMonInstPtr, ConfigPtr);

		/*
		* Enable Over-temperature handling.  We need to unlock PCSR to
		* enable SysMon interrupt.  Lock it back in after write.
		*/
		XPlmi_Out32(ConfigPtr->BaseAddress + XSYSMONPSV_PCSR_LOCK,
			PCSR_UNLOCK_VAL);
		XSysMonPsv_IntrEnable(SysMonInstPtr, XSYSMONPSV_IER0_OT_MASK, 0U);
		XPlmi_Out32(ConfigPtr->BaseAddress + XSYSMONPSV_PCSR_LOCK, 0U);
		Status = XST_SUCCESS;
	}
	XPlmi_Printf(DEBUG_DETAILED,
		 "%s: SysMon init status: 0x%x\n\r", __func__, Status);

	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function detects if we are still in over-temperature condition.
 *
 * @param	None
 *
 * @return	None
 *
 *****************************************************************************/
void XPlmi_SysMonOTDetect(void)
{
	u32 Val;
	u32 Count;

	/*
	 * If Interrupt Status Register does not indicate an over-temperature
	 * condition, we are done.
	 */
	Val = XPlmi_In32((XSYSMONPSV_BASEADDR + XSYSMONPSV_ISR_OFFSET));
	if (0U == (Val & XSYSMONPSV_ISR_OT_MASK)) {
		goto END;
	}

	XPlmi_Out32(XSYSMONPSV_BASEADDR + XSYSMONPSV_PCSR_LOCK,
		PCSR_UNLOCK_VAL);

	/* Wait until over-temperature condition is resolved. */
	Count = 1000U;
	while (0U != (Val & XSYSMONPSV_ISR_OT_MASK)) {
		XPlmi_Out32((XSYSMONPSV_BASEADDR + XSYSMONPSV_ISR_OFFSET),
			XSYSMONPSV_ISR_OT_MASK);
		usleep(1000U);
		Count--;
		if (0U == Count) {
			XPlmi_Printf(DEBUG_GENERAL,
				"Warning: Over-temperature condition!\r\n");
			Count = 1000U;
		}
		Val = XPlmi_In32((XSYSMONPSV_BASEADDR + XSYSMONPSV_ISR_OFFSET));
	}

	XPlmi_Out32(XSYSMONPSV_BASEADDR + XSYSMONPSV_PCSR_LOCK, 0);

END:
	return;
}
