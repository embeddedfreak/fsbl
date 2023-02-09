/******************************************************************************
* Copyright (c) 2017 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file xloader_sbi.c
*
* This is the file which contains SBI related code for the platform loader.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   09/21/2017 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xloader.h"
#include "xplmi_generic.h"
#include "xplmi_util.h"
#include "xloader_sbi.h"
#include "xplmi_hw.h"

#if defined(XLOADER_SBI)
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
/* SBI definitions */
#define XLOADER_SBI_CTRL_INTERFACE_SMAP                  (0x0U)
#define XLOADER_SBI_CTRL_INTERFACE_JTAG                  (0x4U)
#define XLOADER_SBI_CTRL_INTERFACE_AXI_SLAVE             (0x8U)
#define XLOADER_SBI_CTRL_ENABLE                          (0x1U)

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @brief	This function is used to initialize the SBI for SMAP and
 * JTAG boot modes.
 *
 * @param	DeviceFlags used to differentiate between SMAP and JTAG
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XLoader_SbiInit(u32 DeviceFlags)
{
	int Status = XST_FAILURE;

	switch (DeviceFlags) {
		case XLOADER_PDI_SRC_SMAP:
			XPlmi_UtilRMW(SLAVE_BOOT_SBI_CTRL,
			       SLAVE_BOOT_SBI_CTRL_INTERFACE_MASK,
			       XLOADER_SBI_CTRL_INTERFACE_SMAP);
			Status = XST_SUCCESS;
			break;
		case XLOADER_PDI_SRC_JTAG:
			XPlmi_UtilRMW(SLAVE_BOOT_SBI_CTRL,
			       SLAVE_BOOT_SBI_CTRL_INTERFACE_MASK,
			       XLOADER_SBI_CTRL_INTERFACE_JTAG);
			Status = XST_SUCCESS;
			break;
		case XLOADER_PDI_SRC_PCIE:
			XPlmi_UtilRMW(SLAVE_BOOT_SBI_CTRL,
			       SLAVE_BOOT_SBI_CTRL_INTERFACE_MASK,
			       XLOADER_SBI_CTRL_INTERFACE_AXI_SLAVE);
			Status = XST_SUCCESS;
			break;
		case XLOADER_PDI_SRC_SBI:
			Status = XST_SUCCESS;
			break;
		default:
			break;
	}
	if (Status != XST_SUCCESS) {
		goto END;
	}

	/*
	 * Enable the SBI. This is required for
	 * error cases and PCIe boot modes.
	 */
	XPlmi_UtilRMW(SLAVE_BOOT_SBI_CTRL, SLAVE_BOOT_SBI_CTRL_ENABLE_MASK,
		     SLAVE_BOOT_SBI_CTRL_ENABLE_MASK);

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function is used to initialize the SBI with user inputs.
 *
 * @param	CtrlInterface is interface value for configuring SBI
 *
 * @return	None
 *
 *****************************************************************************/
void XLoader_SbiConfig(u32 CtrlInterface)
{
	XPlmi_UtilRMW(SLAVE_BOOT_SBI_CTRL,
		SLAVE_BOOT_SBI_CTRL_INTERFACE_MASK, CtrlInterface);
	XPlmi_UtilRMW(SLAVE_BOOT_SBI_CTRL,
		SLAVE_BOOT_SBI_CTRL_ENABLE_MASK, XLOADER_SBI_CTRL_ENABLE);
}

/*****************************************************************************/
/**
 * @brief	This function is used to initialize the SBI for Slave SLRs.
 *
 * @param	SlrBaseAddr is the base address of slave device
 *
 * @return	None
 *
 *****************************************************************************/
void XLoader_SlaveSbiConfig(u64 SlrBaseAddr)
{
	u64 SbiCtrlAddr = ((u64)SlrBaseAddr +((u64)(SLAVE_BOOT_SBI_CTRL -
				PMC_LOCAL_BASEADDR)));

	XPlmi_UtilRMW64((SbiCtrlAddr >> 32U),
			(SbiCtrlAddr & XLOADER_32BIT_MASK),
			SLAVE_BOOT_SBI_CTRL_INTERFACE_MASK,
			XLOADER_SBI_CTRL_INTERFACE_AXI_SLAVE);

	XPlmi_UtilRMW64((SbiCtrlAddr >> 32U),
			(SbiCtrlAddr & XLOADER_32BIT_MASK),
			SLAVE_BOOT_SBI_CTRL_ENABLE_MASK,
			XLOADER_SBI_CTRL_ENABLE);
}

/*****************************************************************************/
/**
 * @brief	This function is used to copy the data from SMAP/JTAG to
 * destination address through SBI interface.
 *
 * @param	SrcAddress is unused and is only passed for compatibility
 *		with the copy functions of other boot modes
 * @param	DestAddress is the address of the destination to which the data
 *		should be copied to
 * @param	Length is number of bytes to be copied
 * @param	Flags indicate parameters for DMA transfer
 *
 * @return	XST_SUCCESS on success and error code on failure
 *
 *****************************************************************************/
int XLoader_SbiCopy(u32 SrcAddress, u64 DestAddress, u32 Length, u32 Flags)
{
	int Status = XST_FAILURE;
	u32 ReadFlags;
	(void) (SrcAddress);

	ReadFlags = Flags | XPLMI_PMCDMA_1;
	Status = XPlmi_SbiDmaXfer(DestAddress, Length / XPLMI_WORD_LEN,
		ReadFlags);
	if (Status != XST_SUCCESS) {
		goto END;
	}

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function will reset the SBI interface.
 *
 * @param	None
 *
 * @return	None
 *
 *****************************************************************************/
void XLoader_SbiRecovery(void)
{
	u32 SbiCtrl;

	SbiCtrl = XPlmi_In32(SLAVE_BOOT_SBI_CTRL);
	/* Reset DMA1, SBI */
	XPlmi_Out32(CRP_RST_SBI, 0x1U);
	XPlmi_UtilRMW(CRP_RST_PDMA, CRP_RST_PDMA_RESET1_MASK,
		      CRP_RST_PDMA_RESET1_MASK);
	usleep(10U);
	XPlmi_Out32(CRP_RST_SBI, 0x0U);
	XPlmi_UtilRMW(CRP_RST_PDMA, CRP_RST_PDMA_RESET1_MASK, 0x0U);

	/* Restore the interface setting */
	XPlmi_Out32(SLAVE_BOOT_SBI_CTRL, SbiCtrl);
}
#endif /* end of XLOADER_SBI */
