/******************************************************************************
* Copyright (c) 2019 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/****************************************************************************/
/**
*
* @file xloader_usb.h
*
* This file contains declarations of the descriptor structures to be used
* in USB boot mode.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   bvikram  02/10/19 First release
*
* </pre>
*
*****************************************************************************/
#ifndef XLOADER_USB_H
#define XLOADER_USB_H

#ifdef __cplusplus
extern "C" {
#endif
#include "xplmi_hw.h"
#ifdef XLOADER_USB
#include "xusbpsu.h"

/************************** TypeDef Definitions *****************************/
struct dfu_if {
	struct Usb_DevData *InstancePtr;
	u8 curr_state;
	u8 next_state;
	u8 status;
	u8 got_reset;
	u32 current_inf;	/**< Current interface */
	u8 got_dnload_rqst;
	u32 total_transfers;
	u32 total_bytes_dnloaded;
	u32 total_bytes_uploaded;
	volatile u8 dfu_wait_for_interrupt;
	u8 is_dfu;
	u8 runtime_to_dfu;
};
/***************** Macros (Inline Functions) Definitions *********************/
/*
 * @brief	Request types
 */
#define XLOADER_REQ_TYPE_MASK		(0x60U)	/* Mask for request opcode */
#define XLOADER_CMD_STDREQ		(0x00U)	/* Standard Request */
#define XLOADER_CMD_CLASSREQ		(0x20U)	/* Class Request */

/*
 * @brief	Request Values
 */
#define XLOADER_REQ_GET_STATUS			(0x00U)
#define XLOADER_REQ_SET_FEATURE			(0x03U)
#define XLOADER_REQ_SET_ADDRESS			(0x05U)
#define XLOADER_REQ_GET_DESCRIPTOR		(0x06U)
#define XLOADER_REQ_GET_CONFIGURATION		(0x08U)
#define XLOADER_REQ_SET_CONFIGURATION		(0x09U)
#define XLOADER_REQ_SET_INTERFACE		(0x0BU)
#define XLOADER_REQ_SET_SEL			(0x30U)
#define XLOADER_ENDPOINT_NUMBER_MASK		(0x0FU)
#define XLOADER_ENDPOINT_DIR_MASK		(0x80U)
#define XLOADER_ENDPOINT_HALT			(0x00U)
#define XLOADER_ENDPOINT_SELF_PWRD_STATUS	(0x0100U)
#define XLOADER_USB_ENDPOINT_NUMBER_MASK	(0xFU)
#define XLOADER_USB_ENDPOINT_DIR_MASK		(0x80U)

/*
 * @brief	Descriptor Types
 */
#define XLOADER_TYPE_DEVICE_DESC		(0x01U)
#define XLOADER_TYPE_CONFIG_DESC		(0x02U)
#define XLOADER_TYPE_STRING_DESC		(0x03U)
#define XLOADER_TYPE_DEVICE_QUALIFIER		(0x06U)
#define XLOADER_TYPE_BOS_DESC			(u8)(0x0FU)

/*
 * @brief	Status type
 */
#define XLOADER_STATUS_MASK			(0x3U)
#define XLOADER_STATUS_DEVICE			(0x0U)
#define XLOADER_STATUS_INTERFACE		(0x1U)
#define XLOADER_STATUS_ENDPOINT			(0x2U)
#define XLOADER_DFU_STATUS_SIZE			(0x6U)

/************************** Function Prototypes **************************/
void XLoader_DfuInit(void);
void XLoader_DfuSetIntf(struct Usb_DevData* XLoader_UsbInstancePtr,
	SetupPacket *SetupData);
void XLoader_DfuClassReq(struct Usb_DevData* XLoader_UsbInstancePtr,
	SetupPacket *SetupData);
void XLoader_DfuReset(struct Usb_DevData* UsbInstancePtr);
u32 XLoader_Ch9SetupDevDescReply(struct Usb_DevData* XLoader_UsbInstancePtr,
	u8 *BufPtr, u32 BufferLen);
u32 XLoader_Ch9SetupCfgDescReply(struct Usb_DevData* XLoader_UsbInstancePtr,
	u8 *BufPtr, u32 BufferLen);
u32 XLoader_Ch9SetupStrDescReply(struct Usb_DevData* XLoader_UsbInstancePtr,
	u8 *BufPtr, u32 BufferLen, u8 Index);
u32 XLoader_Ch9SetupBosDescReply(struct Usb_DevData* XLoader_UsbInstancePtr,
	u8 *BufPtr, u32 BufferLen);
int XLoader_SetConfiguration(struct Usb_DevData* XLoader_UsbInstancePtr,
	SetupPacket *Ctrl);
void XLoader_DfuSetState(struct Usb_DevData* XLoader_UsbInstancePtr,
	u32 DfuState );
void XLoader_StdDevReq(struct Usb_DevData *InstancePtr,
	SetupPacket *SetupData);
void XLoader_Ch9Handler(struct Usb_DevData *InstancePtr,
	SetupPacket *SetupData);
int XLoader_UsbInit(u32 DeviceFlags);
int XLoader_UsbCopy(u32 SrcAddress, u64 DestAddress, u32 Length, u32 Flags);
int XLoader_UsbReqGetStatus(struct Usb_DevData *InstancePtr,
		SetupPacket *SetupData);
int XLoader_UsbReqGetDescriptor(struct Usb_DevData *InstancePtr,
	SetupPacket *SetupData);
int XLoader_UsbReqSetFeature(struct Usb_DevData *InstancePtr,
	SetupPacket *SetupData);

#endif/*XLOADER_USB*/

#ifdef __cplusplus
}
#endif

#endif /* XLOADER_USB_H */
