;******************************************************************************
;
; Copyright (C) 2009 - 2015 Xilinx, Inc.  All rights reserved.
;
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; Use of the Software is limited solely to applications:
; (a) running on a Xilinx device, or
; (b) that interact with a Xilinx device through a bus or interconnect.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
; XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
; WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
; OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.
;
; Except as contained in this notice, the name of the Xilinx shall not be used
; in advertising or otherwise to promote the sale, use or other dealings in
; this Software without prior written authorization from Xilinx.
;
;*****************************************************************************
;****************************************************************************
;**
; @file translation_table.s
;
; This file contains the initialization for the MMU table in RAM
; needed by the Cortex A9 processor
;
; <pre>
; MODIFICATION HISTORY:
;
; Ver   Who  Date     Changes
; ----- ---- -------- ---------------------------------------------------
; 1.00a ecm  10/20/09 Initial version
; 3.07a sgd  07/05/12 Configuring device address spaces as shareable device
;		       instead of strongly-ordered.
; 4.2	pkp  09/02/14 modified translation table entries according to address map
; 4.2	pkp  09/11/14 modified translation table entries to resolve compilation
;		      error for solving CR#822897
; 6.1	pkp  07/11/16 Corrected comments for memory attributes
; </pre>
;
; @note
;
; None.
;
;****************************************************************************
	EXPORT  MMUTable

;ARMCC	AREA |.mmu_tbl|,CODE,ALIGN=14
;        RSEG mmu_tbl:CODE:ROOT (14)
	SECTION .mmu_tbl:CODE:ROOT(14)

MMUTable
	; Each table entry occupies one 32-bit word and there are
	; 4096 entries, so the entire table takes up 16KB.
	; Each entry covers a 1MB section.


; 0x00000000 - 0x3ffffff (DDR Cacheable)
count   SETA  0
sect    SETA  0
  REPT  0x400
  DCD	sect + 0x15de6		; S=1, TEX=b101 AP=b11, Domain=b1111, C=b0, B=b1
sect    SETA  sect+0x100000
count   SETA  count+1
  ENDR

; 0x40000000 - 0x7fffffff (GpAxi0)
count   SETA  0
   REPT 0x400
   DCD	sect + 0xc02		; S=b0 TEX=b000 AP=b11, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0x80000000 - 0xbfffffff (GpAxi1)
count   SETA  0
   REPT 0x400
   DCD	sect + 0xc02		; S=b0 TEX=b000 AP=b11, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xc0000000 - 0xdfffffff (undef)
count   SETA  0
   REPT 0x200
   DCD	sect 			; S=0, TEX=b000 AP=b00, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xe0000000 - 0xe02fffff (IOP dev)
count   SETA  0
   REPT 0x3
   DCD	sect + 0xc06		; S=0, TEX=b010 AP=b11, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

 ;  0xe0300000 - 0xe0ffffff (undef/reserved)
count   SETA  0
    REPT 0xD
    DCD	sect		;  S=0, TEX=b000 AP=b00, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xe1000000 - 0xe1ffffff (NAND)
count   SETA  0
   REPT 0x10
   DCD	sect + 0xc06		; S=0, TEX=b010 AP=b11, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xe2000000 - 0xe3ffffff (NOR)
count   SETA  0
   REPT 0x20
   DCD	sect + 0xc06		; S=0, TEX=b010 AP=b11, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xe4000000 - 0xe5ffffff (SRAM)
count   SETA  0
   REPT 0x20
   DCD	sect + 0xc0e		; S=b0 TEX=b000 AP=b11, Domain=b0, C=b1, B=b1
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xe6000000 - 0xf7ffffff (reserved)
count   SETA  0
   REPT 0x0120
   DCD	sect 			; S=0, TEX=b000 AP=b00, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xf8000c00 to 0xf8000fff, 0xf8010000 to 0xf88fffff and
; 0xf8f03000 to 0xf8ffffff are reserved  but due to granual size of
; 1MB, it is not possible to define separate regions for them

; 0xf8000000 - 0xf8ffffff (APB device regs)
count   SETA  0
   REPT 0x10
   DCD	sect + 0xc06		; S=0, TEX=b010 AP=b11, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xf9000000 - 0xfbffffff (reserved)
count   SETA  0
   REPT 0x30
   DCD	sect 			; S=0, TEX=b000 AP=b00, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xfc000000 - 0xfdffffff (QSPI)
count   SETA  0
   REPT 0x20
   DCD	sect + 0xc0a		;  S=b0 TEX=b000 AP=b11, Domain=b0, C=b1, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xfe000000 - 0xffefffff (reserved)
count   SETA  0
   REPT 0x1F
   DCD	sect 			; S=0, TEX=b000 AP=b00, Domain=b0, C=b0, B=b0
sect    SETA  sect+0x100000
count   SETA  count+1
   ENDR

; 0xfff00000 to 0xfffb0000 is reserved but due to granual size of
; 1MB, it is not possible to define separate region for  it

; 0xfff00000 to 0xfffb0000 (OCM)
count   SETA  0
    DCD	sect + 0x4c0e		;  S=b0 TEX=b100 AP=b11, Domain=b0, C=b1, B=b1
sect    SETA  sect+0x100000

   END
