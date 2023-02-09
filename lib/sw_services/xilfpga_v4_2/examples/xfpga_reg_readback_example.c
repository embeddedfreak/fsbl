/******************************************************************************
 *
 * Copyright (C) 2017 - 2018 Xilinx, Inc.  All rights reserved.
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
 * XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
 *****************************************************************************/

/**
 * @file  xfpga_reg_readback_example.c
 *
 *
 * This example prints out the values of all the configuration registers in the
 * FPGA.
 *
 * This example assumes that there is a UART Device or STDIO Device in the
 * hardware system.
 *
 * @note		None.
 *
 * MODIFICATION HISTORY:
 *
 *<pre>
 * Ver   Who  Date     Changes
 * ----- ---- -------- ---------------------------------------------
 * 2.1   Nava  05/10/17  First Release
 * 4.2   Nava    30/05/18  Refactor the xilfpga library to support
 *                         different PL programming Interfaces.
 *</pre>
 ******************************************************************************/

/***************************** Include Files *********************************/

#include "xil_printf.h"
#include "xfpga_config.h"
#include "xilfpga.h"

/************************** Constant Definitions *****************************/

/*
 * Addresses of the Configuration Registers
 */
#define CRC		0	/* Status Register */
#define FAR		1	/* Frame Address Register */
#define FDRI		2	/* FDRI Register */
#define FDRO		3	/* FDRO Register */
#define CMD		4	/* Command Register */
#define CTL0		5	/* Control Register 0 */
#define MASK		6	/* MASK Register */
#define STAT		7	/* Status Register */
#define LOUT		8	/* LOUT Register */
#define COR0		9	/* Configuration Options Register 0 */
#define MFWR		10	/* MFWR Register */
#define CBC		11	/* CBC Register */
#define IDCODE		12	/* IDCODE Register */
#define AXSS		13	/* AXSS Register */
#define COR1		14	/* Configuration Options Register 1 */
#define WBSTAR		16	/* Warm Boot Start Address Register */
#define TIMER		17	/* Watchdog Timer Register */
#define BOOTSTS		22	/* Boot History Status Register */
#define CTL1		24	/* Control Register 1 */

/*
 * Mask For IDCODE
 */
#define IDCODE_MASK   0x0FFFFFFF

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

static int Xfpga_RegReadExample(void);
/************************** Variable Definitions *****************************/


/*****************************************************************************/
/**
 *
 * Main function to call the Xfpga Reg Read example.
 *
 * @param	None.
 *
 * @return
 *		- XST_SUCCESS if successful
 *		- XST_FAILURE if unsuccessful
 *
 * @note		None.
 *
 *****************************************************************************/
int main(void)
{
	int Status;

	xil_printf("Register Read back example\r\n");

	/*
	 * Call the example , specify the device ID that is generated in
	 * xparameters.h.
	 */
	Status = Xfpga_RegReadExample();
	if (Status != XST_SUCCESS) {
		xil_printf("Register Read back example Failed\r\n");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran Register Read back example\r\n");

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
 *
 * This function reads the configuration registers inside the FPGA.
 *
 * @param	DeviceId is the unique device id of the device.
 *
 * @return
 *		- XST_SUCCESS if successful
 *		- XST_FAILURE if unsuccessful
 *
 * @note		None.
 *
 *****************************************************************************/
static int Xfpga_RegReadExample(void)
{
	u32 CfgReg[64];

	xil_printf("Value of the Configuration Registers. \r\n\n");

	if (XFpga_GetPlConfigReg(CRC, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" CRC -> \t %x \t\r\n", CfgReg[0]);

	if (XFpga_GetPlConfigReg(FAR, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" FAR -> \t %x \t\r\n", CfgReg[0]);

	if (XFpga_GetPlConfigReg(FDRI, (UINTPTR)CfgReg) !=
		XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" FDRI -> \t %x \t\r\n", CfgReg[0]);

	if (XFpga_GetPlConfigReg(FDRO, (UINTPTR)CfgReg) !=
		XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" FDRO -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(CMD, (UINTPTR)CfgReg) !=
		XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" CMD -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(CTL0, (UINTPTR)CfgReg) !=
		XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" CTL0 -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(MASK, (UINTPTR)CfgReg) !=
		XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" MASK -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(STAT, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" STAT -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(LOUT, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" LOUT -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(COR0, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" COR0 -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(MFWR, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" MFWR -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(CBC, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" CBC -> \t %x \t\r\n",  CfgReg[0]);


	if (XFpga_GetPlConfigReg(IDCODE, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" IDCODE -> \t %x \t\r\n",  CfgReg[0] & IDCODE_MASK);


	if (XFpga_GetPlConfigReg(AXSS, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" AXSS -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(COR1, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" COR1 -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(WBSTAR, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" WBSTAR -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(TIMER, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" TIMER -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(BOOTSTS, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" BOOTSTS -> \t %x \t\r\n",  CfgReg[0]);

	if (XFpga_GetPlConfigReg(CTL1, (UINTPTR)CfgReg) != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf(" CTL1 -> \t %x \t\r\n",  CfgReg[0]);

	return XST_SUCCESS;
}
