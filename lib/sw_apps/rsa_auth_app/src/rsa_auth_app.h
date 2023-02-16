/******************************************************************************
* Copyright (c) 2014 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file rsa_auth_app.h
* 	This file is the header to the SW app used to authenticate a
* 	user application and contains the necessary definitions and prototypes.
*
* @note
*
* None.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who Date     Changes
* ----- --- -------- -----------------------------------------------
* 1.0   hk  27/01/14 First release
*
*</pre>
*
******************************************************************************/
#ifndef ___RSAEXHEADER_H___
#define ___RSAEXHEADER_H___

#ifdef __cplusplus
extern "C" {
#endif
/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xil_types.h"
#include "xil_assert.h"
#include "xil_io.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "xilrsa.h"

/************************** Constant Definitions *****************************/

/*
 * User should provide the following three parameters
 * APPLICATION_START_ADDR - Start address of the application to be validated
 * APP_PARTITION_SIZE - Length(in bytes) of the complete partition
 *                      should be provided.
 * CERTIFICATE_START_ADDR - Authentication certificate start address.
 *                          This should point to the Authentication header.
 * The application and authentication certificate are assumed to be at
 * contiguous memory locations.
 *
 *
 * APPLICATION_START_ADDR>-----------------------------------------------------
 * 			APPLICATION (with padding if any)
 * CERTIFICATE_START_ADDR>-----------------------------------------------------
 * 			AUTHENTICATION HEADER (With padding to 512bit boundary)
 * 			-------------------------------------------------------
 * 			PPK (With padding to 512 bit boundary)
 * 			-------------------------------------------------------
 * 			SPK (With padding to 512 bit boundary)
 * 			-------------------------------------------------------
 * 			SPK SIGNATURE (With padding to 512 bit boundary)
 * 			-------------------------------------------------------
 * 			APPLICATION SIGNATURE (With padding to 512bit boundary)
 * 			-------------------------------------------------------
 *
 * APP_PARTITION_SIZE is the complete size of the above mentioned partition
 * in bytes.
 *
 */

#define APPLICATION_START_ADDR	0x0

#define PARTITION_SIZE	0x0

#define CERTIFICATE_START_ADDR	0x0

/*
 * RSA certificate related definitions
 */
#define RSA_PPK_MODULAR_SIZE		256
#define RSA_PPK_MODULAR_EXT_SIZE	256
#define RSA_PPK_EXPO_SIZE		64
#define RSA_SPK_MODULAR_SIZE		256
#define RSA_SPK_MODULAR_EXT_SIZE	256
#define RSA_SPK_EXPO_SIZE		64
#define RSA_SPK_SIGNATURE_SIZE		256
#define RSA_PARTITION_SIGNATURE_SIZE	256
#define RSA_SIGNATURE_SIZE		0x6C0 	/* Signature size in bytes */
#define RSA_HEADER_SIZE			4 /* Signature header size in bytes */
#define RSA_MAGIC_WORD_SIZE		60	/* Magic word size in bytes */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Global Function Prototypes ***********************/

int AuthenticateApp(void);

/************************** Variable Definitions *****************************/

#ifdef __cplusplus
}
#endif

#endif /* ___RSAEXHEADER_H___ */
