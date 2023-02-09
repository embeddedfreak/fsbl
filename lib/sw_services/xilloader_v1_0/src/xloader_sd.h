/******************************************************************************
* Copyright (C) 2018-2020 Xilinx, Inc. All rights reserved.
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
* @file xloader_sd.h
*
* This is the header file which contains qspi declarations for the PLM.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   02/21/2018 Initial release
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XLOADER_SD_H
#define XLOADER_SD_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************** Include Files *********************************/
#include "xplmi_hw.h"
#include "xplmi_status.h"
#if defined(XLOADER_SD_0) || defined(XLOADER_SD_1)
#include "xsdps.h"
#include "xplmi_debug.h"
/************************** Constant Definitions *****************************/
/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define XLOADER_BASE_FILE_NAME_LEN_SD_1 	(11U)
#define XLOADER_NUM_DIGITS_IN_FILE_NAME 	(4U)
#define XLOADER_SD_DRV_NUM_0			(0U)
#define XLOADER_SD_DRV_NUM_1			(1U)
#define XLOADER_SD_DRV_NUM_4			(4U)
#define XLOADER_SD_RAW_BLK_SIZE			(512U)
#define XLOADER_SD_RAW_NUM_SECTORS		(128U)

/************************** Function Prototypes ******************************/

int XLoader_SdInit(u32 DeviceFlags);
int XLoader_SdCopy(u32 SrcAddr, u64 DestAddress, u32 Length, u32 Flags);
int XLoader_SdRelease(void );
int XLoader_RawInit(u32 DrvNum);
int XLoader_RawCopy(u32 SrcAddr, u64 DestAddress, u32 Length, u32 Flags);

/************************** Variable Definitions *****************************/


#endif /* end of XLOADER_SD */

#ifdef __cplusplus
}
#endif

#endif  /* XLOADER_SD_H */
