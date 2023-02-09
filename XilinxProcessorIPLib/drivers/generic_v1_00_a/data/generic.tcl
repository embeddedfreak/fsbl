###############################################################
# Copyright (c) 2004 Xilinx, Inc. All Rights Reserved.
# You may copy and modify these files for your own internal use solely with
# Xilinx programmable logic devices and  Xilinx EDK system or create IP
# modules solely for Xilinx programmable logic devices and Xilinx EDK system.
# No rights are granted to distribute any files unless they are distributed in
# Xilinx programmable logic devices. 
###############################################################
#uses "xillib_sw.tcl"

proc generate {drv_handle} {
    
    ::hsi::utils::define_addr_params $drv_handle "xparameters.h"
}
