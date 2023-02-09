/******************************************************************************
* Copyright (c) 2019 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xloader_ddr.h
*
* This is the header file which contains DDR interface declarations
* for the xilloader.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   03/12/2019 Initial release
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XLOADER_DDR_H
#define XLOADER_DDR_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xplmi_hw.h"
#include "xplmi_dma.h"
#include "xplmi_status.h"
#include "xplmi_debug.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
int XLoader_DdrInit(u32 DeviceFlags);
int XLoader_DdrCopy(u32 SrcAddr, u64 DestAddress, u32 Length, u32 Flags);

/************************** Variable Definitions *****************************/

#ifdef __cplusplus
}
#endif

#endif  /* XLOADER_DDR_H */
