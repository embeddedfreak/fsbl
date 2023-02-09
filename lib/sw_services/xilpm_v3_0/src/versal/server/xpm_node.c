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

#include "xpm_defs.h"
#include "xpm_common.h"
#include "xpm_node.h"

void XPmNode_Init(XPm_Node *Node, u32 Id, u8 State, u32 BaseAddress)
{
	PmDbg("Node Init: Type=%d, Id=%d, State=%d, BaseAddress=0x%08X\n\r",
		NODETYPE(Id), Id, State, BaseAddress);

	Node->Id = Id;
	Node->State = State;
	Node->BaseAddress = BaseAddress;
	Node->Flags = 0;
	Node->LatencyMarg = XPM_MAX_LATENCY;
}
