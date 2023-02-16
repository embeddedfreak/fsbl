/******************************************************************************
* Copyright (c) 2018 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xloader_qspi.h
*
* This is the header file which contains qspi declarations for the PLM.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   02/21/2018 Initial release
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XLOADER_QSPI_H
#define XLOADER_QSPI_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xplmi_hw.h"
#include "xplmi_status.h"
#ifdef XLOADER_QSPI
#include "xqspipsu.h"
#include "xplmi_debug.h"

/************************** Constant Definitions *****************************/
/*
 * The following constants define the commands which may be sent to the FLASH
 * device.
 */
#define XLOADER_READ_ID_CMD			(0x9FU)
#define XLOADER_FAST_READ_CMD_24BIT		(0x0BU)
#define	XLOADER_DUAL_READ_CMD_24BIT		(0x3BU)
#define XLOADER_QUAD_READ_CMD_24BIT		(0x6BU)
#define XLOADER_FAST_READ_CMD_32BIT		(0x0CU)
#define XLOADER_DUAL_READ_CMD_32BIT		(0x3CU)
#define XLOADER_QUAD_READ_CMD_32BIT		(0x6CU)

#define XLOADER_WRITE_ENABLE_CMD	(0x06U)
#define XLOADER_BANK_REG_RD_CMD		(0x16U)
#define XLOADER_BANK_REG_WR_CMD		(0x17U)
/* Bank register is called Extended Addr Reg in Micron */
#define XLOADER_EXTADD_REG_RD_CMD	(0xC8U)
#define XLOADER_EXTADD_REG_WR_CMD	(0xC5U)

#define XLOADER_COMMAND_OFST	(0U) /* FLASH instruction */
#define XLOADER_ADDR_1_OFST	(1U) /* MSB byte of address to read or write */
#define XLOADER_ADDR_2_OFST	(2U) /* Middle byte of address to read or write */
#define XLOADER_ADDR_3_OFST	(3U) /* Middle byte of address to read or write */
#define XLOADER_ADDR_4_OFST	(4U) /* LSB byte of address to read or write */
#define XLOADER_DATA_OFST	(4U) /* Start of Data for Read/Write */
#define XLOADER_DUMMY_OFST	(4U) /* Dummy byte offset for fast, dual and quad
				     reads */
#define XLOADER_DUMMY_SIZE	(1U) /* Number of dummy bytes for fast, dual and
				     quad reads */
#define XLOADER_DUMMY_CLOCKS	(8U) /* Number of dummy bytes for fast, dual and
				     quad reads */
#define XLOADER_RD_ID_SIZE	(4U) /* Read ID command + 3 bytes ID response */
#define XLOADER_BANK_SEL_SIZE	(2U) /* BRWR or EARWR command + 1 byte bank value */
#define XLOADER_WRITE_ENABLE_CMD_SIZE	(1U) /* WE command */

/*
 * The following constants specify the extra bytes which are sent to the
 * FLASH on the QSPI interface, that are not data, but control information
 * which includes the command and address
 */
#define XLOADER_OVERHEAD_SIZE	(4U)

/*
 * Max limit of single DMA transfer is 512MB
 */
#define XLOADER_DMA_DATA_TRAN_SIZE	(0x20000000U)

/*
 * The following defines are for dual flash interface.
 */
#define XLOADER_LQSPI_CR_FAST_QUAD_READ		(0x0000006BU) /* Fast Quad Read output */
#define XLOADER_LQSPI_CR_1_DUMMY_BYTE		(0x00000100U) /* 1 Dummy Byte between
						     address and return data */

#define XLOADER_SINGLE_QSPI_IO_CONFIG_QUAD_READ	(LQSPI_CR_1_DUMMY_BYTE | \
	LQSPI_CR_FAST_QUAD_READ)

#define XLOADER_DUAL_QSPI_PARALLEL_IO_CONFIG_QUAD_READ	\
	(XQSPIPS_LQSPI_CR_TWO_MEM_MASK | XQspiPsu_LQSPI_CR_SEP_BUS_MASK | \
	LQSPI_CR_1_DUMMY_BYTE | LQSPI_CR_FAST_QUAD_READ)

#define XLOADER_DUAL_QSPI_STACK_IO_CONFIG_READ	(XQSPIPS_LQSPI_CR_TWO_MEM_MASK \
	| LQSPI_CR_1_DUMMY_BYTE | LQSPI_CR_FAST_QUAD_READ)

/*
 * Flash connection type as defined in Vivado
 */
#define XLOADER_FLASH_SIZE_16MB			(0x1000000U)
#define XLOADER_BANKSIZE			(XLOADER_FLASH_SIZE_16MB)
/*
 * Bank mask
 */
#define XLOADER_BANKMASK		(0xFFFFFFFFU & ~(XLOADER_BANKSIZE - 1U))

/*
 * Identification of Flash
 * Micron:
 * Byte 0 is Manufacturer ID;
 * Byte 1 is first byte of Device ID - 0xBB or 0xBA
 * Byte 2 is second byte of Device ID describes flash size:
 * 128Mbit : 0x18; 256Mbit : 0x19; 512Mbit : 0x20
 * Spansion:
 * Byte 0 is Manufacturer ID;
 * Byte 1 is Device ID - Memory Interface type - 0x20 or 0x02
 * Byte 2 is second byte of Device ID describes flash size:
 * 128Mbit : 0x18; 256Mbit : 0x19; 512Mbit : 0x20
 */
#define XLOADER_MICRON_ID		(0x20U)
#define XLOADER_SPANSION_ID		(0x01U)
#define XLOADER_WINBOND_ID		(0xEFU)
#define XLOADER_MACRONIX_ID		(0xC2U)
#define XLOADER_ISSI_ID			(0x9DU)

#define XLOADER_FLASH_SIZE_ID_64M		(0x17U)
#define XLOADER_FLASH_SIZE_ID_128M		(0x18U)
#define XLOADER_FLASH_SIZE_ID_256M		(0x19U)
#define XLOADER_FLASH_SIZE_ID_512M		(0x20U)
#define XLOADER_FLASH_SIZE_ID_1G		(0x21U)
#define XLOADER_FLASH_SIZE_ID_2G		(0x22U)
/* Macronix size constants are different for 512M and 1G */
#define XLOADER_MACRONIX_FLASH_SIZE_ID_512M		(0x1AU)
#define XLOADER_MACRONIX_FLASH_SIZE_ID_1G		(0x1BU)
#define XLOADER_MACRONIX_FALSH_1_8_V_SIZE_ID_512M       (0x3AU)
#define XLOADER_MACRONIX_FALSH_1_8_V_SIZE_ID_1G         (0x3BU)
#define XLOADER_MACRONIX_FALSH_1_8_V_SIZE_ID_2G		(0x3CU)
/*
 * Size in bytes
 */
#define XLOADER_FLASH_SIZE_64M			(0x0800000U)
#define XLOADER_FLASH_SIZE_128M			(0x1000000U)
#define XLOADER_FLASH_SIZE_256M			(0x2000000U)
#define XLOADER_FLASH_SIZE_512M			(0x4000000U)
#define XLOADER_FLASH_SIZE_1G			(0x8000000U)
#define XLOADER_FLASH_SIZE_2G			(0x10000000U)

/* TODO change to QSPI driver API */
#define XLOADER_QSPIDMA_DST_CTRL	(0xF103080CU)

/*Qspi width detection macros*/
#define XLOADER_QSPI_BUSWIDTH_DETECT_VALUE	(0xAA995566U)
#define XLOADER_QSPI_BUSWIDTH_PDI_OFFSET	(0x10U)
#define XLOADER_QSPI_BUSWIDTH_LENGTH		(0x10U)
#define XLOADER_QSPI_BUSWIDTH_ONE		(0U)
#define XLOADER_QSPI_BUSWIDTH_TWO		(1U)
#define XLOADER_QSPI_BUSWIDTH_FOUR		(2U)

#define XLOADER_READ_ID_CMD_TX_BYTE_CNT		(1U)
#define XLOADER_READ_ID_CMD_RX_BYTE_CNT		(4U)
#define XLOADER_QSPI24_COPY_DISCARD_BYTE_CNT	(4U)
#define XLOADER_QSPI32_COPY_DISCARD_BYTE_CNT	(5U)
#define XLOADER_QSPI_WRITE_ENABLE_CMD_BYTE_CNT	(1U)
#define XLOADER_EXTADD_REG_WR_CMD_BYTE_CNT	(2U)
#define XLOADER_EXTADD_REG_RD_CMD_BYTE_CNT	(1U)
#define XLOADER_BANK_REG_WR_CMD_BYTE_CNT	(2U)
#define XLOADER_BANK_REG_RD_CMD_BYTE_CNT	(1U)

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
int XLoader_QspiInit(u32 DeviceFlags);
int XLoader_QspiCopy(u32 SrcAddr, u64 DestAddress, u32 Length, u32 Flags);
int XLoader_QspiGetBusWidth(u32 ImageOffsetAddress);

/************************** Variable Definitions *****************************/

#endif /* end of XLOADER_QSPI */

#ifdef __cplusplus
}
#endif

#endif  /* XLOADER_QSPI_H */
