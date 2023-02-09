/******************************************************************************
* Copyright (C) 2019 - 2020 Xilinx, Inc. All rights reserved.
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
* @file xloader_cmd.c
*
* This file contains the xloader commands implementation.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   03/12/2019 Initial release
		har  08/28/2019 Fixed MISRA C violations
* </pre>
*
* @note
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xloader.h"
#include "xplmi_cmd.h"
#include "xplmi_modules.h"
#ifdef XPLM_SEM
#include "xilsem.h"
#endif
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
extern XilPdi* BootPdiPtr;
extern XLoader_DeviceOps DeviceOps[];
static XPlmi_Module XPlmi_Loader;
/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/*****************************************************************************/
/**
 * @brief This function checks if a particular Loader Command ID is supported
 * or not. Command ID is the only payload parameter.
 *
 * @param Pointer to the command structure
 *
 * @return Returns XST_SUCCESS
 *****************************************************************************/
static int XLoader_Features(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;

	if (Cmd->Payload[0U] < XPlmi_Loader.CmdCnt) {
		Cmd->Response[1U] = XLOADER_SUCCESS;
	}
	else
	{
		Cmd->Response[1U] = XLOADER_FAILURE;
	}
	Status = XST_SUCCESS;
	Cmd->Response[0U] = Status;
	return Status;
}


/*****************************************************************************/
/**
 * @brief This function provides load ddr copy image execution
 * Command payload parameters are
 *	* imgid - of ddr copied image
 *
 * @param Pointer to the command structure
 *
 * @return Returns the Load PDI command
 *****************************************************************************/
static int XLoader_LoadDdrCpyImg(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;

	u32 ImgId;
	XilPdi* PdiPtr = BootPdiPtr;
	PdiPtr->ImageNum = 1U;
	PdiPtr->PrtnNum = 1U;
	XPlmi_Printf(DEBUG_INFO, "%s \n\r", __func__);

#if defined(XPLM_SEM) && defined(XSEM_CFRSCAN_EN)
	/** Stop the SEM scan before Image load */
	Status = XSem_CfrStopScan();
	if (Status != XST_SUCCESS) {
		Status = XPLMI_UPDATE_STATUS(XLOADER_ERR_SEM_STOP_SCAN, Status);
		goto END;
	}
#endif
	/*
	 * Store the command fields in resume data
	 */
	PdiPtr->PdiType = XLOADER_PDI_TYPE_RESTORE;
	PdiPtr->PdiSrc = XLOADER_PDI_SRC_DDR;
	PdiPtr->DeviceCopy = DeviceOps[XLOADER_PDI_SRC_DDR].Copy;
	PdiPtr->MetaHdr.DeviceCopy = PdiPtr->DeviceCopy;
	ImgId = Cmd->Payload[0U];
	PdiPtr->PdiAddr = PdiPtr->MetaHdr.FlashOfstAddr =
						XLOADER_DDR_COPYIMAGE_BASEADDR;
	PdiPtr->CopyToMem = FALSE;
	PdiPtr->DelayHandoff = FALSE;

	Status = XLoader_LoadImage(PdiPtr, ImgId);
	if (Status == XST_SUCCESS) {
		Status = XLoader_StartImage(PdiPtr);
	}
	if (Status != XST_SUCCESS) {
		/* Update the error code */
		XPlmi_ErrMgr(Status);
		goto END;
	}
END:
#if defined(XPLM_SEM) && defined(XSEM_CFRSCAN_EN)
	/** ReStart the SEM SCAN */
	Status = XSem_CfrInit();
	if (Status != XST_SUCCESS) {
		Status = XPLMI_UPDATE_STATUS(XLOADER_ERR_SEM_CFR_INIT, Status);
		goto END;
	}
#endif
	Cmd->Response[0U] = Status;
	return Status;
}


/*****************************************************************************/
/**
 * @brief This function provides load subsystem PDI command execution
 *  Command payload parameters are
 *	* PdiSrc - Boot Mode values, DDR, PCIe
 *	* PdiAddr - 64bit PDI address located in the Source
 *
 * @param Pointer to the command structure
 *
 * @return Returns the Load PDI command
 *****************************************************************************/
static int XLoader_LoadSubsystemPdi(XPlmi_Cmd * Cmd)
{
	int Status = XST_FAILURE;
	u32 PdiSrc;
	u64 PdiAddr;
	XilPdi* PdiPtr = &SubsystemPdiIns;

	XPlmi_Printf(DEBUG_DETAILED, "%s \n\r", __func__);

	/** store the command fields in resume data */
	PdiSrc = Cmd->Payload[0U];
	PdiAddr = (u64 )Cmd->Payload[1U];
	PdiAddr = ((u64 )Cmd->Payload[2U] |
		   (PdiAddr << 32U));

	XPlmi_Printf(DEBUG_INFO, "Subsystem PDI Load: Started\n\r");

	PdiPtr->PdiType = XLOADER_PDI_TYPE_PARTIAL;
	Status = XLoader_LoadPdi(PdiPtr, PdiSrc, PdiAddr);
	if (Status != XST_SUCCESS)
	{
		/* Update the error code */
		XPlmi_ErrMgr(Status);
		goto END;
	}

	XPlmi_Printf(DEBUG_GENERAL, "Subsystem PDI Load: Done\n\r");
END:
	Cmd->Response[0U] = Status;
	return Status;
}

/*****************************************************************************/
/**
 * @brief contains the array of PLM loader commands
 *
 *****************************************************************************/
static XPlmi_ModuleCmd XLoader_Cmds[] =
{
	XPLMI_MODULE_COMMAND(XLoader_Features),
	XPLMI_MODULE_COMMAND(XLoader_LoadSubsystemPdi),
	XPLMI_MODULE_COMMAND(XLoader_LoadDdrCpyImg)
};

/*****************************************************************************/
/**
 * @brief Contains the module ID and loader commands array
 *
 *****************************************************************************/
static XPlmi_Module XPlmi_Loader =
{
	XPLMI_MODULE_LOADER_ID,
	XLoader_Cmds,
	XPLMI_ARRAY_SIZE(XLoader_Cmds),
};

/*****************************************************************************/
/**
 * @brief This function registers the PLM Loader commands to the PLMI
 *
 * @param none
 *
 * @return none
 *
 *****************************************************************************/
void XLoader_CmdsInit(void)
{
	XPlmi_ModuleRegister(&XPlmi_Loader);
}
