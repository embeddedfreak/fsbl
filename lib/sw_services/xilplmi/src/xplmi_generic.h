/******************************************************************************
* Copyright (c) 2018 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file xplmi_generic.h
*
* This is the file which contains .
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   08/23/2018 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/
#ifndef XPLMI_GENERIC_H
#define XPLMI_GENERIC_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xil_types.h"
#include "xplmi_debug.h"
#include "xil_io.h"
#include "xil_assert.h"
#include "xplmi_modules.h"
#include "xplmi_dma.h"
#include "xplmi_cmd.h"

/************************** Constant Definitions *****************************/
enum {
	XPLMI_ERR_MASKPOLL = 0x10U,
	XPLMI_ERR_MASKPOLL64, /**< 0x11U */
	XPLMI_ERR_CMD_NOT_SUPPORTED, /**< 0x12U */
};

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define XPLMI_SBI_DEST_ADDR				(0xFFFFFFFFFFFFFFFFL)
#define XPLMI_READBK_INTF_TYPE_SMAP		(0x0U)
#define XPLMI_READBK_INTF_TYPE_JTAG		(0x1U)
#define XPLMI_READBK_INTF_TYPE_DDR		(0x2U)
#define XPLMI_SET_CHUNK_SIZE			(128U)

/* Mask poll command flag descriptions */
#define XPLMI_MASKPOLL_LEN_EXT			(5U)
#define XPLMI_MASKPOLL64_LEN_EXT		(6U)
#define XPLMI_MASKPOLL_FLAGS_MASK		(0x3U)
#define XPLMI_MASKPOLL_FLAGS_ERR		(0x0U)
#define XPLMI_MASKPOLL_FLAGS_SUCCESS		(0x1U)
#define XPLMI_MASKPOLL_FLAGS_DEFERRED_ERR	(0x2U)
#define XPLMI_PLM_GENERIC_CMD_ID_MASK		(0xFFU)
#define XPLMI_PLM_MODULES_FEATURES_VAL		(0x00U)
#define XPLMI_PLM_GENERIC_DEVICE_ID_VAL		(0x12U)
#define XPLMI_PLM_GENERIC_EVENT_LOGGING_VAL	(0x13U)

/************************** Function Prototypes ******************************/
void XPlmi_GenericInit(void);
int XPlmi_CfiRead(XPlmi_Cmd * Cmd);
int XPlmi_DmaWriteKeyHole(XPlmi_Cmd * Cmd);
int XPlmi_CfiWrite(u32 SrcAddr, u64 DestAddr, u32 Keyholesize, u32 Len,
		XPlmi_Cmd* Cmd);

/************************** Variable Definitions *****************************/

/*****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* XPLMI_GENERIC_H */
