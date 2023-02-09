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
* @file xilpli.h
*
* This file contains declarations for image store functions.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   07/24/2018 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XILPLI_H
#define XILPLI_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xilpdi.h"
#include "xplmi_hw.h"
#include <xstatus.h>
#include "xplmi_debug.h"
#include "xilpli_ospi.h"
#include "xilpli_sd.h"
#include "xilpli_sbi.h"
#include "xilpli_qspi.h"
#include "xpm_device.h"
/************************** Constant Definitions *****************************/
#define XILPLI_SUCCESS		XST_SUCCESS
#define XPli_Printf		XPlmi_Printf
#define XILPLI_32BIT_MASK	(0xFFFFFFFFU)
#define PMC_LOCAL_BASEADDR	(0xF0000000U)

/* Boot Modes */
enum XILPLI_PDI_SRC {
	XILPLI_PDI_SRC_JTAG = (0x0U),
	XILPLI_PDI_SRC_QSPI24 = (0x1U),
	XILPLI_PDI_SRC_QSPI32 = (0x2U),
	XILPLI_PDI_SRC_SD0 =    (0x3U),
	XILPLI_PDI_SRC_SD1 =    (0x5U),
	XILPLI_PDI_SRC_EMMC =   (0x6U),
	XILPLI_PDI_SRC_USB =    (0x7U),
	XILPLI_PDI_SRC_OSPI =   (0x8U),
	XILPLI_PDI_SRC_SMAP =   (0xAU),
	XILPLI_PDI_SRC_SD1_LS = (0xEU),
	XILPLI_PDI_SRC_SBI_JTAG = (0x10U)
};

/* Error Codes */
#define XILPLI_ERR_MASK                         (0xFF00U)
#define XILPLI_ERR_MODULE_MASK                  (0xFFU)
#define XILPLI_UPDATE_ERR(XilPliErr, ModuleErr)          \
                ((XilPliErr&XILPLI_ERR_MASK) + \
                 (ModuleErr&XILPLI_ERR_MODULE_MASK))

#define XILPLI_UNSUPPORTED_BOOT_MODE	(0x200U)
/**************************** Type Definitions *******************************/

/**
 * This stores the handoff Address of the different cpu's
 */
typedef struct {
        u32 CpuSettings;
        u64 HandoffAddr;
} XilPli_HandoffParam;

typedef struct {
	u32 DeviceBaseAddr; /**< Flash device base address */
	int (*Init) (u32 DeviceFlags);
		/**< Function pointer for Device initialization code */
	XStatus (*Copy) (u32 SrcAddr, u64 DestAddress, u32 Length, u32 Flags);
		/**< Function pointer for device copy */
} XilPli_DeviceOps;


/**
 * This is PDI instance pointer. This stores all the information
 * required for PDI
 */
typedef struct {
	u32 PdiType; /**< Indicate PDI Type, full PDI, partial PDI */
	u32 PdiSrc; /**< Source of the PDI - Boot device, DDR */
	u64 PdiAddr; /**< Address where PDI is present in PDI Source */
	u32 PdiId; /**< Indicates the full PDI Id */
	XilPdi_MetaHdr MetaHdr; /**< Metaheader of the PDI */
	XStatus (*DeviceCopy) (u32, u64, u32, u32);
	u32 NoOfHandoffCpus; /**< Number of CPU's loader will handoff to */
        XilPli_HandoffParam HandoffParam[10];
	u32 EccStatus;
} XilPdi;

/**
 * This is Subsystem instance pointer. This stores all the information
 * required for Subsystem
 */
typedef struct {
	u32 SubsystemId; /**< Corresponding subsystem ID */
	XilPdi *PdiPtr; /**< PDI source for that Subsystem */
	u32 ImageId; /**< Corresponding Image ID in the PDI */
} XilSubsystem;

/***************** Macros (Inline Functions) Definitions *********************/
#define XPli_GetBootMode()	XPlmi_In32(CRP_BOOT_MODE_USER) & \
				CRP_BOOT_MODE_USER_BOOT_MODE_MASK


/************************** Function Prototypes ******************************/
#if 0
int XSubSys_Init(u32 * CdoBuf);
int XSubSys_LoadPdi(XilPdi* PdiPtr, u32 PdiSrc, u64 PdiAddr);
int XSubSys_CopyPdi(u32 PdiSrc, u64 SrcAddr, u64 DestAddr, u32 PdiLen);
int XSubSys_ReStart(u32 SubsysHd);
int XPli_LoadImage(XilPdi *PdiPtr, u32 ImageId);
int XPli_StartImage(XilPdi *PdiPtr, u32 ImageId);
#endif

int XPli_PdiInit(XilPdi* PdiPtr, u32 PdiSrc, u64 PdiAddr);
int XPli_LoadSubSystemPdi(XilPdi *PdiPtr);
int XPli_StartSubSystemPdi(XilPdi *PdiPtr);

/* functions defined in xilpli_prtn_load.c */
int XPli_PrtnLoad(XilPdi* PdiPtr, u32 PrtnNum);
#ifdef __cplusplus
}
#endif

#endif  /* XILPLI_H */
