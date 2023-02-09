/******************************************************************************
* Copyright (c) 2018 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xplmi_dma.h
*
* This is the file which contains common code for the PLM.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   02/21/2017 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XPLMI_DMA_H
#define XPLMI_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xpmcdma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/
/** DMA XFER flags */
#define XPLMI_SRC_CH_AXI_FIXED		(0x1U)
#define XPLMI_DMA_SRC_NONBLK		(0x1U << 1U)
#define XPLMI_DST_CH_AXI_FIXED		(0x1U << 16U)
#define XPLMI_DMA_DST_NONBLK		(0x1U << 17U)
#define XPLMI_PMCDMA_0				(0x100U)
#define XPLMI_PMCDMA_1				(0x200U)
#define XPLMI_DMA_SRC_NPI			(0x4U)
#define XPLMI_DMA_DST_TYPE_SHIFT	(18U)
#define XPLMI_DMA_DST_TYPE_MASK		(0x3U << 18U)
#define XPLMI_READ_AXI_FIXED		(0x1U)

/* SSS configurations and masks */
#define XPLMI_SSSCFG_DMA0_MASK		(0x0000000FU)
#define XPLMI_SSSCFG_DMA1_MASK		(0x000000F0U)
#define XPLMI_SSSCFG_PTP1_MASK		(0x00000F00U)
#define XPLMI_SSSCFG_AES_MASK		(0x0000F000U)
#define XPLMI_SSSCFG_SHA_MASK		(0x000F0000U)
#define XPLMI_SSSCFG_SBI_MASK		(0x00F00000U)

#define XPLMI_SSS_SBI_DMA0			(0x00500000U)
#define XPLMI_SSS_SBI_DMA1			(0x00B00000U)

#define XPLMI_SSS_SHA_DMA0			(0x000C0000U)
#define XPLMI_SSS_SHA_DMA1			(0x00070000U)

#define XPLMI_SSS_AES_DMA0			(0x0000E000U)
#define XPLMI_SSS_AES_DMA1			(0x00005000U)

#define XPLMI_SSS_PTPI_DMA0			(0x00000D00U)
#define XPLMI_SSS_PTPI_DMA1			(0x00000A00U)

#define XPLMI_SSS_DMA1_DMA1			(0x00000090U)
#define XPLMI_SSS_DMA1_AES			(0x00000070U)
#define XPLMI_SSS_DMA1_SBI			(0x000000E0U)
#define XPLMI_SSS_DMA1_PZM			(0x00000040U)

#define XPLMI_SSS_DMA0_DMA0			(0x0000000DU)
#define XPLMI_SSS_DMA0_AES			(0x00000006U)
#define XPLMI_SSS_DMA0_SBI			(0x0000000BU)
#define XPLMI_SSS_DMA0_PZM			(0x00000003U)

#define XPLMI_DATA_INIT_PZM			(0xDEADBEEFU)
#define XPLMI_PZM_WORD_LEN			(16U)

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
int XPlmi_DmaInit();
XPmcDma *XPlmi_GetDmaInstance(u32 DeviceId);
int XPlmi_DmaXfr(u64 SrcAddr, u64 DestAddr, u32 Len, u32 Flags);
int XPlmi_SbiDmaXfer(u64 DestAddr, u32 Len, u32 Flags);
int XPlmi_DmaSbiXfer(u64 SrcAddr, u32 Len, u32 Flags);
int XPlmi_EccInit(u64 Addr, u32 Len);
int XPlmi_InitNVerifyMem(u64 Addr, u32 Len);
int XPlmi_StartDma(u64 SrcAddr, u64 DestAddr, u32 Len, u32 Flags,
		XPmcDma** DmaPtrAddr);
void XPlmi_WaitForNonBlkSrcDma(void);
void XPlmi_WaitForNonBlkDma(void);
void XPlmi_SetMaxOutCmds(u32 Val);

#ifdef __cplusplus
}
#endif

#endif  /* XPLMI_DMA_H */
