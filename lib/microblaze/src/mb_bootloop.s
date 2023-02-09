/************************************************************************
*
* Copyright (c) 2003 Xilinx, Inc.  All rights reserved.
*
* Xilinx, Inc.
* XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
* COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
* ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
* STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
* IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
* FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  
* XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
* THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
* ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
* FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
* AND FITNESS FOR A PARTICULAR PURPOSE.
* 
* File   : bootloop.s
* Company: Xilinx
*
* Summary:
*    The bootloop program keeps the processor when it comes out of reset 
* on powerup. This bootloop program is useful when the user program is
* in external memory and the user is in the debugging phase. On powerup, 
* external memory is not initialized and usually the debugger has to 
* download the program to external memory. Until then, the bootloop 
* program keeps the processor busy and prevents it from executing 
* instructions from uninitialized memory (which can cause unknown 
* behavior from which the debugger cannot stop the processor).
*
* $Id: mb_bootloop.s,v 1.1.10.6 2005/11/15 23:41:00 salindac Exp $
*
*********************************************************************/

.section ".boot","ax"

_boot:  bri 0