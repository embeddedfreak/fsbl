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

#include "xpm_psm_api.h"
#include "xpm_core.h"
#include "xpm_psm.h"

XStatus XPmCore_Init(XPm_Core *Core, u32 Id, XPm_Power *Power,
		     XPm_ClockNode *Clock, XPm_ResetNode *Reset, u8 IpiCh,
		     struct XPm_CoreOps *Ops)
{
	XStatus Status = XST_FAILURE;

	Status = XPmDevice_Init(&Core->Device, Id, 0, Power, Clock, Reset);
	if (XST_SUCCESS != Status) {
		goto done;
	}

	Core->DebugMode = 0;
	Core->ImageId = 0;
	Core->Ipi = IpiCh;
	Core->CoreOps = Ops;

done:
	return Status;
}

static XStatus XPmCore_Sleep(XPm_Core *Core)
{
	XStatus Status = XST_FAILURE;
	XPm_ResetHandle *RstHandle, *DeviceHandle;
	XPm_ResetNode *Reset;

	/*
	 * If parent is on, then only send sleep request
	 */
	if ((Core->Device.Power->Parent->Node.State == XPM_POWER_STATE_ON) &&
	    (XPM_NODETYPE_DEV_CORE_RPU != NODETYPE(Core->Device.Node.Id))) {
		/*
		 * Power down the core
		 */
		Status = XPm_DirectPwrDwn(Core->Device.Node.Id);
		if (XST_SUCCESS != Status) {
			goto done;
		}
	} else {
		Status = XST_SUCCESS;
		goto done;
	}

	if (NULL != Core->Device.ClkHandles) {
		Status = XPmClock_Release(Core->Device.ClkHandles);
		if (XST_SUCCESS != Status) {
			goto done;
		}
	}

	RstHandle = Core->Device.RstHandles;
	while (NULL != RstHandle) {
		Reset = RstHandle->Reset;
		DeviceHandle = Reset->RstHandles;
		while (NULL != DeviceHandle) {
			if (XPM_DEVSTATE_RUNNING ==
			    DeviceHandle->Device->Node.State) {
				break;
			}
			DeviceHandle = DeviceHandle->NextDevice;
		}
		if (NULL == DeviceHandle) {
			Reset->Ops->SetState(Reset, PM_RESET_ACTION_ASSERT);
		}
		RstHandle = RstHandle->NextReset;
	}

done:
	return Status;
}

XStatus XPmCore_WakeUp(XPm_Core *Core)
{
	XStatus Status = XST_FAILURE;
	XPm_Power *PwrNode;

	DISABLE_WAKE(Core->SleepMask);

	if ((XPM_DEVSTATE_RUNNING != Core->Device.Node.State) &&
	    (NULL != Core->Device.Power)) {
		PwrNode = Core->Device.Power;
		Status = PwrNode->HandleEvent(&PwrNode->Node, XPM_POWER_EVENT_PWR_UP);
		if (XST_SUCCESS != Status) {
			goto done;
		}
	}

	if (NULL != Core->CoreOps && NULL != Core->CoreOps->RestoreResumeAddr) {
		Status = Core->CoreOps->RestoreResumeAddr(Core);
		if (XST_SUCCESS != Status) {
			goto done;
		}
	}

	if (XPM_DEVSTATE_RUNNING != Core->Device.Node.State) {
		if (NULL != Core->Device.ClkHandles) {
			XPmClock_Request(Core->Device.ClkHandles);
		}
		Status = XPm_DirectPwrUp(Core->Device.Node.Id);
	}

done:
	return Status;
}

XStatus XPmCore_PwrDwn(XPm_Core *Core)
{
	XStatus Status = XST_FAILURE;
	XPm_Power *PwrNode;

	if (XPM_DEVSTATE_UNUSED == Core->Device.Node.State) {
		Status = XST_SUCCESS;
		goto done;
	}

	if (XPM_DEVSTATE_SUSPENDING == Core->Device.Node.State) {
		DISABLE_WFI(Core->SleepMask);
	}

	Status = XPmCore_Sleep(Core);
	if(Status != XST_SUCCESS) {
		goto done;
	}

	if (NULL != Core->Device.Power) {
		PwrNode = Core->Device.Power;
		Status = PwrNode->HandleEvent(&PwrNode->Node, XPM_POWER_EVENT_PWR_DOWN);
		if (XST_SUCCESS != Status) {
			goto done;
		}
	}

	if (XPM_DEVSTATE_SUSPENDING == Core->Device.Node.State) {
		ENABLE_WAKE(Core->SleepMask);
	}

	Core->Device.Node.State = XPM_DEVSTATE_UNUSED;

done:
	return Status;
}
