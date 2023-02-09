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
* @file xloader_ddr.c
*
* This is the file which contains DDR init and copy functions
* related code for the platform loader.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   03/12/2019 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/
/***************************** Include Files *********************************/
#include "xloader.h"
#include "xplmi_util.h"
#include "xloader_ddr.h"
#include "xplmi_hw.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/


/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * This function is used to initialize for DDR init. Nothing is required in
 * this. DDR must be already initialized by this time.
 *
 * @param	DeviceFlags Loader init prototype requires flags.
 *
 * @return	SUCCESS
 *
 *****************************************************************************/
int XLoader_DdrInit(u32 DeviceFlags)
{
	(void)DeviceFlags;

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
 * This function is used to copy the data from DDR to destination
 * address
 *
 * @param SrcAddress
 *
 * @param DestAddress is the address of the destination where it
 * should copy to
 *
 * @param Length Length of the bytes to be copied
 *
 * @param Flags that denote blocking / non-blocking dma
 *
 * @return
 *		- XST_SUCCESS for successful copy
 *		- errors as mentioned in xplmi_status.h
 *
 *****************************************************************************/
int XLoader_DdrCopy(u32 SrcAddress, u64 DestAddress, u32 Length, u32 Flags)
{
	int Status = XST_FAILURE;
	u32 DmaFlags;

	DmaFlags = XPLMI_PMCDMA_1;
	Flags = Flags & XLOADER_DEVICE_COPY_STATE_MASK;

	/** Just wait for the Data to be copied */
	if (Flags == XLOADER_DEVICE_COPY_STATE_WAIT_DONE)
	{
		XPlmi_WaitForNonBlkDma();
		Status = XST_SUCCESS;
		goto END;
	}

	/** Update the flags for NON blocking DMA call */
	if (Flags == XLOADER_DEVICE_COPY_STATE_INITIATE)
	{
		DmaFlags |= XPLMI_DMA_SRC_NONBLK;
	}
	Status = XPlmi_DmaXfr((u64)SrcAddress, DestAddress, Length/4, DmaFlags);
END:
	return Status;
}

/*****************************************************************************/
/**
 * This function is used to release the sd settings
 *
 * @param	None
 *
 * @return	None
 *
 *****************************************************************************/
int XLoader_DdrRelease(void )
{

	return XST_SUCCESS;
}
