/******************************************************************************
*
* Copyright (C) 2018-2019 Xilinx, Inc.  All rights reserved.
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

#ifndef XPM_SUBSYSTEM_H_
#define XPM_SUBSYSTEM_H_

#include "xpm_requirement.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	INVALID_SUBSYSID	-1U
#define SUBSYSTEMCLASS_MASK \
	((XPM_NODECLASS_SUBSYSTEM & NODE_CLASS_MASK_BITS) << NODE_CLASS_SHIFT)
#define ISVALIDSUBSYSTEM(id) \
	( (((id & SUBSYSTEMCLASS_MASK) == SUBSYSTEMCLASS_MASK) && \
	((id & NODE_INDEX_MASK_BITS) < XPM_NODEIDX_SUBSYS_MAX)) ? 1 : 0)

/**
 * Subsystem specific flags.
 */
#define SUBSYSTEM_INIT_FINALIZED		(1 << 0U)

/**
 * Subsystem creation states.
 */
typedef enum {
	OFFLINE,
	RESERVED,
	ONLINE,
	SUSPENDING,
	SUSPENDED,
	POWERED_OFF,
	MAX_STATE
} XPm_SubsysState;

typedef struct XPm_Requirement XPm_Requirement;
typedef struct XPm_Subsystem XPm_Subsystem;

/**
 * The subsystem class.
 */
struct XPm_Subsystem {
	u32 Id; /**< Subsystem ID */
	XPm_SubsysState State; /**< Subsystem state */
	u8 Flags; /**< Subsystem specific flags */
	u32 IpiMask;
	XPm_Requirement *Requirements;
		/**< Head of the requirement list for all devices. */
	void (*NotifyCb)(u32 SubsystemId, const u32 EventId);
};

/************************** Function Prototypes ******************************/

u32 XPmSubsystem_GetIPIMask(u32 SubsystemId);
u32 XPmSubsystem_GetSubSysIdByIpiMask(u32 IpiMask);
XStatus XPm_IsWakeAllowed(u32 SubsystemId, u32 NodeId);
XStatus XPm_IsAccessAllowed(u32 SubsystemId, u32 NodeId);
XStatus XPmSubsystem_SetState(const u32 SubsystemId, const u32 State);
XStatus XPmSubsystem_Add(u32 SubsystemId);
XStatus XPmSubsystem_Destroy(u32 SubsystemId);
XStatus XPmSubsystem_IsAllProcDwn(u32 SubsystemId);
XStatus XPm_IsForcePowerDownAllowed(u32 SubsystemId, u32 NodeId);
XStatus XPmSubsystem_ForceDownCleanup(u32 SubsystemId);
int XPmSubsystem_InitFinalize(const u32 SubsystemId);
int XPmSubsystem_Idle(u32 SubsystemId);
XPm_Subsystem *XPmSubsystem_GetById(u32 SubsystemId);
XPm_Subsystem *XPmSubsystem_GetByIndex(u32 SubsystemIndex);
XStatus XPmSubsystem_SetCurrent(u32 SubsystemId);
u32 XPmSubsystem_GetCurrent(void);
XStatus XPmSubsystem_Restart(u32 SubsystemId);
XStatus XPmSubsystem_GetStatus(const u32 SubsystemId, const u32 DeviceId,
			       XPm_DeviceStatus *const DeviceStatus);

#ifdef __cplusplus
}
#endif

#endif /* XPM_SUBSYSTEM_H_ */
