/******************************************************************************
* Copyright (C) 2018 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
 *****************************************************************************/

/*****************************************************************************/
/**
 *
 * @file si570drv.h
 *
 * This file contains definitions for low-level driver functions for
 * controlling the SiliconLabs Si570 clock generator as mounted on the ZCU106
 * demo board.
 * The user should refer to the hardware device specification for more details
 * of the device operation.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date        Changes
 * ----- --- ----------   -----------------------------------------------
 * 1.00	 ssh 07/05/2018	  Initial release
 * </pre>
 *
 ******************************************************************************/

#ifndef SI570DRV_H_
#define SI570DRV_H_
#include "xil_types.h"

/******************************************************************************
 * Defines independent on the specific board design. Should not be changed.
 *****************************************************************************/

/**
 * Debug output enable. Set to TRUE to enable debug prints,
 * to FALSE to disable debug prints.
 */
#define SI570_DEBUG FALSE

/**
 * The following constants are error codes generated by the functions in
 * this driver.
 */
#define SI570_SUCCESS      0 /**< Operation was successful */
#define SI570_ERR_IIC     -1 /**< IIC error occurred */
#define SI570_ERR_FREQ    -2 /**< Could not calculate frequency setting */
#define SI570_ERR_PARM    -3 /**< Invalid parameter */

#define FREQ_SI570_148_5_MHz	(148500000)
#define FREQ_SI570_148_35_MHz	(148350000)

#endif /* SI570DRV_H_ */