/******************************************************************************
* Copyright (C) 2018 Xilinx, Inc. All rights reserved.
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
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
******************************************************************************/
/*****************************************************************************/
/**
*
* @file xilpli_ospi.h
*
* This is the header file which contains ospi declarations for the PLM.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   02/21/2017 Initial release
* </pre>
*
* @note
*
******************************************************************************/
#ifndef XILPLI_OSPI_H
#define XILPLI_OSPI_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************** Include Files *********************************/
//#define XILPLI_OSPI
#ifdef XILPLI_OSPI
#include "xparameters.h"	/* SDK generated parameters */
#include "xospipsv.h"		/* OSPIPSV device driver */

/************************** Constant Definitions *****************************/

/**
 * Flash connection type as defined in PCW
 */
#define FLASH_SIZE_16MB				(0x1000000U)
#define MICRON_ID				(0x20U)
#define FLASH_SIZE_ID_512M			(0x20U)
#define FLASH_SIZE_512M				(0x4000000U)
#define READ_CMD_OCTAL_4B    			(0x7CU)
#define READ_ID					(0x9FU)
#define MICRON_INDEX_START			(0x0U)
#define WRITE_DISABLE_CMD			(0x4U)
#define WRITE_ENABLE_CMD			(0x6U)
#define ENTER_4B_ADDR_MODE      0xB7
#define EXIT_4B_ADDR_MODE       0xE9
#define READ_FLAG_STATUS_CMD	0X70
/*
 * Identification of Flash
 * Micron:
 * Byte 0 is Manufacturer ID;
 * Byte 1 is first byte of Device ID - 0x5B
 * Byte 2 is second byte of Device ID describes flash size:
 * 512Mbit : 0x1A
 */
#define	MICRON_OCTAL_ID_BYTE0	0x2C
#define MICRON_OCTAL_ID_BYTE2_512	0x1A


/* Error Codes */
#define XILPLI_ERR_OSPI_INIT                            (0x4000)
#define XILPLI_ERR_OSPI_CFG                             (0x4100)
#define XILPLI_ERR_UNSUPPORTED_OSPI                     (0x4200)
#define XILPLI_ERR_UNSUPPORTED_OSPI_SIZE        	(0x4300)

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

int XPli_OspiInit(u32 DeviceFlags);
int XPli_OspiCopy(u32 SrcAddr, u64 DestAddress, u32 Length, u32 Flags);
int XPli_OspiRelease(void );
int FlashEnterExit4BAddMode(XOspiPsv *OspiPsvPtr);
/************************** Variable Definitions *****************************/


#endif /* end of XILPLI_QSPI */

#ifdef __cplusplus
}
#endif

#endif  /* XILPLI_QSPI_H */
