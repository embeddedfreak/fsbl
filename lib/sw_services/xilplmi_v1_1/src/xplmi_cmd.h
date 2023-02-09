/******************************************************************************
* Copyright (c) 2018 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file xplmi_cmd.h
*
* This is the file which contains command execution code.
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
#ifndef XPLMI_CMD_H
#define XPLMI_CMD_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xil_assert.h"
#include "xil_types.h"
#include "xplmi_status.h"

/************************** Constant Definitions *****************************/
#define XPLMI_CMD_API_ID_MASK			(0xFFU)
#define XPLMI_CMD_MODULE_ID_MASK		(0xFF00U)
#define XPLMI_CMD_LEN_MASK			(0xFF0000U)
#define XPLMI_CMD_RESP_SIZE			(8U)
#define XPLMI_CMD_RESUME_DATALEN			(8U)
#define XPLMI_CMD_HNDLR_MASK				(0xFF00U)
#define XPLMI_CMD_HNDLR_PLM_VAL				(0x100U)
#define XPLMI_CMD_HNDLR_EM_VAL				(0x800U)

/**************************** Type Definitions *******************************/
typedef struct XPlmi_Cmd XPlmi_Cmd;
typedef struct XPlmi_KeyHoleParams XPlmi_KeyHoleParams;

struct XPlmi_KeyHoleParams {
	u16 PdiSrc; /**< Source of Pdi */
	/** < True implies copied in chunks of 64K */
	/** < False implies complete bitstream is copied in one chunk */
	u8 InChunkCopy;
	u32 SrcAddr; /**< Boot Source address */
	u32 ExtraWords; /**< Words that are directly DMAed to CFI */
	int (*Func) (u32, u64, u32, u32);
};

struct XPlmi_Cmd {
	u32 SubsystemId;
	u32 IpiMask;
	u32 CmdId;
	u32 Len;
	u32 ProcessedLen;
	u32 PayloadLen;
	u32 *Payload;
	u32 Response[XPLMI_CMD_RESP_SIZE];
	int (*ResumeHandler)(XPlmi_Cmd * CmdPtr);
	u32 ResumeData[XPLMI_CMD_RESUME_DATALEN];
	u32 DeferredError;
	XPlmi_KeyHoleParams KeyHoleParams;
};

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
int XPlmi_CmdExecute(XPlmi_Cmd * CmdPtr);
int XPlmi_CmdResume(XPlmi_Cmd * CmdPtr);

/************************** Variable Definitions *****************************/

/*****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* end of XPLMI_CMD_H */
