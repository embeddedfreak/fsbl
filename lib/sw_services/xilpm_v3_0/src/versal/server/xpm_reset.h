/******************************************************************************
*
* Copyright (C) 2018-2020 Xilinx, Inc.  All rights reserved.
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
*
******************************************************************************/

#ifndef XPM_RESET_H_
#define XPM_RESET_H_

#include "xpm_node.h"
#include "xpm_common.h"
#include "xpm_subsystem.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_RESET_PARENTS	(3U)

/* All reset types */
typedef enum {
	XPM_RSTTYPE_POR,
	XPM_RSTTYPE_SYS,
	XPM_RSTTYPE_PERIPH,
	XPM_RSTTYPE_DBG,
}XPm_ResetType;


/* All reset Ops types */
typedef enum {
	XPM_RSTOPS_GENRERIC=1,
	XPM_RSTOPS_CUSTOM,
	XPM_RSTOPS_MAX,
}XPm_ResetOpsType;

typedef enum XPmResetActions XPm_ResetActions;
typedef struct XPm_ResetNode XPm_ResetNode;
typedef struct XPm_ResetHandle XPm_ResetHandle;

/**
 * xPmResetOps - Reset operations
 * @SetState	Assert or release reset line
 * @GetState	Get current status of reset line
 */
typedef struct XPmResetOps {
	XStatus (*const SetState)(XPm_ResetNode *Rst, const u32 Action);
	u32 (*const GetState)(XPm_ResetNode *Rst);
} XPm_ResetOps;


/**
 * XPm_ResetHandle - This models reset/device pair.
 */
struct XPm_ResetHandle {
	XPm_ResetNode *Reset; /**< Reset used by device */
	struct XPm_DeviceNode *Device; /**< Device which uses the reset */
	XPm_ResetHandle *NextReset; /**< Next handle of same device */
	XPm_ResetHandle *NextDevice; /**< Next handle of same reset */
};

/**
 * The reset class.	 This is the base class for all the reset nodes.
 */
struct XPm_ResetNode {
	XPm_Node Node;
	u16 Parents[MAX_RESET_PARENTS]; /**< List of Parent Reset Index */
	uint8_t Shift;
	uint8_t Width;
	XPm_ResetOps *Ops;
	XPm_ResetHandle *RstHandles; /**< Pointer to the reset/device pairs */
};

#define MAX_RESETS	XPM_NODEIDX_RST_MAX

#define XPM_RST_STATE_DEASSERTED 0U
#define XPM_RST_STATE_ASSERTED 1U

/************************** Function Prototypes ******************************/

XStatus XPmReset_AddNode(u32 Id, u32 ControlReg, u8 Shift, u8 Width, u8 ResetType, u8 NumParents, u32* Parents);
XPm_ResetNode* XPmReset_GetById(u32 ResetId);
XStatus XPmReset_AssertbyId(u32 ResetId, const u32 Action);
int XPmReset_CheckPermissions(XPm_Subsystem *Subsystem, u32 ResetId);
int XPmReset_SystemReset(void);

#ifdef __cplusplus
}
#endif

#endif /* XPM_RESET_H_ */
