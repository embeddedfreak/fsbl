/******************************************************************************
* (c) Copyright 2010 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information
* of Xilinx, Inc. and is protected under U.S. and
* international copyright and other intellectual property
* laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any
* rights to the materials distributed herewith. Except as
* otherwise provided in a valid license issued to you by
* Xilinx, and to the maximum extent permitted by applicable
* law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
* WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
* AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
* INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
* (2) Xilinx shall not be liable (whether in contract or tort,
* including negligence, or under any other theory of
* liability) for any loss or damage of any kind or nature
* related to, arising under or in connection with these
* materials, including for any direct, or any indirect,
* special, incidental, or consequential loss or damage
* (including loss of data, profits, goodwill, or any type of
* loss or damage suffered as a result of any action brought
* by a third party) even if such damage or loss was
* reasonably foreseeable or Xilinx had been advised of the
* possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-
* safe, or for use in any application requiring fail-safe
* performance, such as life-support or safety devices or
* systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any
* other applications that could lead to death, personal
* injury, or severe property or environmental damage
* (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and
* liability of any use of Xilinx products in Critical
* Applications, subject only to applicable laws and
* regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
* PART OF THIS FILE AT ALL TIMES.
******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file example.c
 *
 * This file demonstrates how to use Xilinx Defective Pixel Correction (DPC)
 * driver of the Xilinx Defective Pixel Correction v3.0 core. This code does not 
 * cover the DPC v3.0 setup and any other configuration which might be
 * required to get the DPC device working properly.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 2.00a vc   3/1/11 First release
 * </pre>
 *
 * ***************************************************************************
 */

#include "dpc.h"
#include "xparameters.h"

/***************************************************************************/
// Defective Pixel Correction Register Reading Example
// This function provides an example of how to read the current configuration
// settings of the DPC core.
/***************************************************************************/
void report_dpc_settings(u32 BaseAddress) {
  
  u32 status;

  xil_printf("Defective Pixel Correction Core Configuration:\r\n");
  xil_printf(" DPC Enable Bit: %1d\r\n", DPC_ReadReg(BaseAddress, DPC_CONTROL) & DPC_CTL_EN_MASK);  
  xil_printf(" DPC Register Update Bit: %1d\r\n", (DPC_ReadReg(BaseAddress, DPC_CONTROL) & DPC_CTL_RUE_MASK) >> 1);	  
  xil_printf(" DPC Reset Bit: %1d\r\n", DPC_ReadReg(BaseAddress, DPC_CONTROL) & DPC_RST_RESET);	  
  xil_printf(" THRESH_TEMPORAL_VAR=%3x \r\n", DPC_ReadReg(BaseAddress, DPC_THRESH_TEMPORAL_VAR)); 
  xil_printf(" THRESH_SPATIAL_VAR=%3x \r\n", DPC_ReadReg(BaseAddress, DPC_THRESH_SPATIAL_VAR)); 
  xil_printf(" THRESH_PIXEL_AGE=%3x \r\n", DPC_ReadReg(BaseAddress, DPC_THRESH_PIXEL_AGE)); 
}  

/***************************************************************************/
// Defective Pixel Correction Register Update Example
//  This function provides an example of the process used to update
//  the threshold registers in the DPC core.
//  In most video systems, it is expected that this process would be executed 
//  in response to an interrupt connected to the VBlank video timing signal
//  or a timeout signal associated with a watchdog timer.
/***************************************************************************/
void DPC_Update_Example() {
  
	//Enable the DPC software enable    
	DPC_Enable(XPAR_DPC_0_BASEADDR);
	
	//Disable register updates.
	//This is the default operating mode for the DPC core, and allows
	//registers to be updated without effecting the core's behavior.
	DPC_RegUpdateDisable(XPAR_DPC_0_BASEADDR);
	
  //Set the filter strength
	DPC_WriteReg(XPAR_DPC_0_BASEADDR, DPC_THRESH_TEMPORAL_VAR, 0);
	DPC_WriteReg(XPAR_DPC_0_BASEADDR, DPC_THRESH_SPATIAL_VAR, 0);
	DPC_WriteReg(XPAR_DPC_0_BASEADDR, DPC_THRESH_PIXEL_AGE, 0);
   
   //Enable register updates.
	//This mode will cause the coefficient and offset registers internally
	//to the DPC core to automatically be updated on the next rising-edge
	//of VBlank.
	DPC_RegUpdateEnable(XPAR_DPC_0_BASEADDR);

}


/*****************************************************************************/
//
// This is the main function for the DPC example.
//
/*****************************************************************************/
int main(void)
{
    // Print the current settings for the DPC core
	  report_dpc_settings(XPAR_DPC_0_BASEADDR);
	 
    // Call the DPC example, specify the Device ID generated in xparameters.h
    DPC_Update_Example(XPAR_DPC_0_BASEADDR);
	 
	  return 0;
}
