
################################################################
# This is a generated script based on design: design_1
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2015.3
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   puts "ERROR: This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7z020clg484-1
#    set_property BOARD_PART em.avnet.com:zed:part0:1.3 [current_project]

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
   puts "ERROR: Please open or create a project!"
   return 1
}



# CHANGE DESIGN NAME HERE
set design_name design_1

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "ERROR: Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      puts "INFO: Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   puts "INFO: Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   puts "INFO: Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   puts "INFO: Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

puts "INFO: Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   puts $errMsg
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set DDR [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddrx_rtl:1.0 DDR ]
  set FIXED_IO [ create_bd_intf_port -mode Master -vlnv xilinx.com:display_processing_system7:fixedio_rtl:1.0 FIXED_IO ]

  # Create ports

  # Create instance: atg_acp, and set properties
  set atg_acp [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_traffic_gen:2.0 atg_acp ]
  set_property -dict [ list CONFIG.C_M_AXI_DATA_WIDTH {64}  ] $atg_acp

  # Create instance: atg_gp0, and set properties
  set atg_gp0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_traffic_gen:2.0 atg_gp0 ]

  # Create instance: atg_hp0, and set properties
  set atg_hp0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_traffic_gen:2.0 atg_hp0 ]
  set_property -dict [ list CONFIG.C_M_AXI_DATA_WIDTH {64}  ] $atg_hp0

  # Create instance: atg_hp1, and set properties
  set atg_hp1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_traffic_gen:2.0 atg_hp1 ]
  set_property -dict [ list CONFIG.C_M_AXI_DATA_WIDTH {64}  ] $atg_hp1

  # Create instance: atg_hp2, and set properties
  set atg_hp2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_traffic_gen:2.0 atg_hp2 ]
  set_property -dict [ list CONFIG.C_M_AXI_DATA_WIDTH {64}  ] $atg_hp2

  # Create instance: atg_hp3, and set properties
  set atg_hp3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_traffic_gen:2.0 atg_hp3 ]
  set_property -dict [ list CONFIG.C_M_AXI_DATA_WIDTH {64}  ] $atg_hp3

  # Create instance: axi_gpio_0, and set properties
  set axi_gpio_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_0 ]
  set_property -dict [ list CONFIG.C_ALL_OUTPUTS {1} CONFIG.C_GPIO_WIDTH {1}  ] $axi_gpio_0

  # Create instance: axi_mem_intercon, and set properties
  set axi_mem_intercon [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_mem_intercon ]
  set_property -dict [ list CONFIG.NUM_MI {1}  ] $axi_mem_intercon

  # Create instance: axi_mem_intercon_1, and set properties
  set axi_mem_intercon_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_mem_intercon_1 ]
  set_property -dict [ list CONFIG.NUM_MI {1}  ] $axi_mem_intercon_1

  # Create instance: axi_mem_intercon_2, and set properties
  set axi_mem_intercon_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_mem_intercon_2 ]
  set_property -dict [ list CONFIG.NUM_MI {1}  ] $axi_mem_intercon_2

  # Create instance: axi_mem_intercon_3, and set properties
  set axi_mem_intercon_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_mem_intercon_3 ]
  set_property -dict [ list CONFIG.NUM_MI {1}  ] $axi_mem_intercon_3

  # Create instance: axi_mem_intercon_4, and set properties
  set axi_mem_intercon_4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_mem_intercon_4 ]
  set_property -dict [ list CONFIG.NUM_MI {1}  ] $axi_mem_intercon_4

  # Create instance: axi_mem_intercon_5, and set properties
  set axi_mem_intercon_5 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_mem_intercon_5 ]
  set_property -dict [ list CONFIG.NUM_MI {1}  ] $axi_mem_intercon_5

  # Create instance: axi_perf_mon_0, and set properties
  set axi_perf_mon_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_perf_mon:5.0 axi_perf_mon_0 ]
  set_property -dict [ list CONFIG.C_ENABLE_ADVANCED {0} CONFIG.C_ENABLE_EVENT_COUNT {0} CONFIG.C_ENABLE_PROFILE {1} CONFIG.C_ENABLE_TRACE {1} CONFIG.C_NUM_MONITOR_SLOTS {6} CONFIG.ENABLE_EXT_EVENTS {1} CONFIG.ENABLE_EXT_TRIGGERS {1}  ] $axi_perf_mon_0

  # Create instance: processing_system7_0, and set properties
  set processing_system7_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0 ]
  set_property -dict [ list CONFIG.PCW_QSPI_GRP_SINGLE_SS_ENABLE {1} CONFIG.PCW_USE_S_AXI_ACP {1} CONFIG.PCW_USE_S_AXI_GP0 {1} CONFIG.PCW_USE_S_AXI_HP0 {1} CONFIG.PCW_USE_S_AXI_HP1 {1} CONFIG.PCW_USE_S_AXI_HP2 {1} CONFIG.PCW_USE_S_AXI_HP3 {1} CONFIG.preset {ZedBoard}  ] $processing_system7_0

  # Create instance: processing_system7_0_axi_periph, and set properties
  set processing_system7_0_axi_periph [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 processing_system7_0_axi_periph ]
  set_property -dict [ list CONFIG.NUM_MI {8}  ] $processing_system7_0_axi_periph

  # Create interface connections
  connect_bd_intf_net -intf_net atg_acp_M_AXI [get_bd_intf_pins atg_acp/M_AXI] [get_bd_intf_pins axi_mem_intercon/S00_AXI]
connect_bd_intf_net -intf_net [get_bd_intf_nets atg_acp_M_AXI] [get_bd_intf_pins atg_acp/M_AXI] [get_bd_intf_pins axi_perf_mon_0/SLOT_4_AXI]
  connect_bd_intf_net -intf_net atg_gp0_M_AXI [get_bd_intf_pins atg_gp0/M_AXI] [get_bd_intf_pins axi_mem_intercon_1/S00_AXI]
connect_bd_intf_net -intf_net [get_bd_intf_nets atg_gp0_M_AXI] [get_bd_intf_pins atg_gp0/M_AXI] [get_bd_intf_pins axi_perf_mon_0/SLOT_5_AXI]
  connect_bd_intf_net -intf_net atg_hp0_M_AXI [get_bd_intf_pins atg_hp0/M_AXI] [get_bd_intf_pins axi_mem_intercon_2/S00_AXI]
connect_bd_intf_net -intf_net [get_bd_intf_nets atg_hp0_M_AXI] [get_bd_intf_pins atg_hp0/M_AXI] [get_bd_intf_pins axi_perf_mon_0/SLOT_0_AXI]
  connect_bd_intf_net -intf_net atg_hp1_M_AXI [get_bd_intf_pins atg_hp1/M_AXI] [get_bd_intf_pins axi_mem_intercon_3/S00_AXI]
connect_bd_intf_net -intf_net [get_bd_intf_nets atg_hp1_M_AXI] [get_bd_intf_pins atg_hp1/M_AXI] [get_bd_intf_pins axi_perf_mon_0/SLOT_1_AXI]
  connect_bd_intf_net -intf_net atg_hp2_M_AXI [get_bd_intf_pins atg_hp2/M_AXI] [get_bd_intf_pins axi_mem_intercon_4/S00_AXI]
connect_bd_intf_net -intf_net [get_bd_intf_nets atg_hp2_M_AXI] [get_bd_intf_pins atg_hp2/M_AXI] [get_bd_intf_pins axi_perf_mon_0/SLOT_2_AXI]
  connect_bd_intf_net -intf_net atg_hp3_M_AXI [get_bd_intf_pins atg_hp3/M_AXI] [get_bd_intf_pins axi_mem_intercon_5/S00_AXI]
connect_bd_intf_net -intf_net [get_bd_intf_nets atg_hp3_M_AXI] [get_bd_intf_pins atg_hp3/M_AXI] [get_bd_intf_pins axi_perf_mon_0/SLOT_3_AXI]
  connect_bd_intf_net -intf_net axi_mem_intercon_1_M00_AXI [get_bd_intf_pins axi_mem_intercon_1/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_GP0]
  connect_bd_intf_net -intf_net axi_mem_intercon_2_M00_AXI [get_bd_intf_pins axi_mem_intercon_2/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_HP0]
  connect_bd_intf_net -intf_net axi_mem_intercon_3_M00_AXI [get_bd_intf_pins axi_mem_intercon_3/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_HP1]
  connect_bd_intf_net -intf_net axi_mem_intercon_4_M00_AXI [get_bd_intf_pins axi_mem_intercon_4/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_HP2]
  connect_bd_intf_net -intf_net axi_mem_intercon_5_M00_AXI [get_bd_intf_pins axi_mem_intercon_5/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_HP3]
  connect_bd_intf_net -intf_net axi_mem_intercon_M00_AXI [get_bd_intf_pins axi_mem_intercon/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_ACP]
  connect_bd_intf_net -intf_net processing_system7_0_DDR [get_bd_intf_ports DDR] [get_bd_intf_pins processing_system7_0/DDR]
  connect_bd_intf_net -intf_net processing_system7_0_FIXED_IO [get_bd_intf_ports FIXED_IO] [get_bd_intf_pins processing_system7_0/FIXED_IO]
  connect_bd_intf_net -intf_net processing_system7_0_M_AXI_GP0 [get_bd_intf_pins processing_system7_0/M_AXI_GP0] [get_bd_intf_pins processing_system7_0_axi_periph/S00_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M00_AXI [get_bd_intf_pins atg_acp/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M00_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M01_AXI [get_bd_intf_pins atg_hp0/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M01_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M02_AXI [get_bd_intf_pins atg_hp1/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M02_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M03_AXI [get_bd_intf_pins atg_hp2/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M03_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M04_AXI [get_bd_intf_pins atg_hp3/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M04_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M05_AXI [get_bd_intf_pins atg_gp0/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M05_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M06_AXI [get_bd_intf_pins axi_perf_mon_0/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M06_AXI]
  connect_bd_intf_net -intf_net processing_system7_0_axi_periph_M07_AXI [get_bd_intf_pins axi_gpio_0/S_AXI] [get_bd_intf_pins processing_system7_0_axi_periph/M07_AXI]

  # Create port connections
  connect_bd_net -net axi_gpio_0_gpio_io_o [get_bd_pins atg_acp/core_ext_start] [get_bd_pins atg_gp0/core_ext_start] [get_bd_pins atg_hp0/core_ext_start] [get_bd_pins atg_hp1/core_ext_start] [get_bd_pins atg_hp2/core_ext_start] [get_bd_pins atg_hp3/core_ext_start] [get_bd_pins axi_gpio_0/gpio_io_o]
  connect_bd_net -net processing_system7_0_FCLK_CLK0 [get_bd_pins atg_acp/s_axi_aclk] [get_bd_pins atg_gp0/s_axi_aclk] [get_bd_pins atg_hp0/s_axi_aclk] [get_bd_pins atg_hp1/s_axi_aclk] [get_bd_pins atg_hp2/s_axi_aclk] [get_bd_pins atg_hp3/s_axi_aclk] [get_bd_pins axi_gpio_0/s_axi_aclk] [get_bd_pins axi_mem_intercon/ACLK] [get_bd_pins axi_mem_intercon/M00_ACLK] [get_bd_pins axi_mem_intercon/S00_ACLK] [get_bd_pins axi_mem_intercon_1/ACLK] [get_bd_pins axi_mem_intercon_1/M00_ACLK] [get_bd_pins axi_mem_intercon_1/S00_ACLK] [get_bd_pins axi_mem_intercon_2/ACLK] [get_bd_pins axi_mem_intercon_2/M00_ACLK] [get_bd_pins axi_mem_intercon_2/S00_ACLK] [get_bd_pins axi_mem_intercon_3/ACLK] [get_bd_pins axi_mem_intercon_3/M00_ACLK] [get_bd_pins axi_mem_intercon_3/S00_ACLK] [get_bd_pins axi_mem_intercon_4/ACLK] [get_bd_pins axi_mem_intercon_4/M00_ACLK] [get_bd_pins axi_mem_intercon_4/S00_ACLK] [get_bd_pins axi_mem_intercon_5/ACLK] [get_bd_pins axi_mem_intercon_5/M00_ACLK] [get_bd_pins axi_mem_intercon_5/S00_ACLK] [get_bd_pins axi_perf_mon_0/core_aclk] [get_bd_pins axi_perf_mon_0/m_axis_aclk] [get_bd_pins axi_perf_mon_0/s_axi_aclk] [get_bd_pins axi_perf_mon_0/slot_0_axi_aclk] [get_bd_pins axi_perf_mon_0/slot_1_axi_aclk] [get_bd_pins axi_perf_mon_0/slot_2_axi_aclk] [get_bd_pins axi_perf_mon_0/slot_3_axi_aclk] [get_bd_pins axi_perf_mon_0/slot_4_axi_aclk] [get_bd_pins axi_perf_mon_0/slot_5_axi_aclk] [get_bd_pins processing_system7_0/FCLK_CLK0] [get_bd_pins processing_system7_0/M_AXI_GP0_ACLK] [get_bd_pins processing_system7_0/S_AXI_ACP_ACLK] [get_bd_pins processing_system7_0/S_AXI_GP0_ACLK] [get_bd_pins processing_system7_0/S_AXI_HP0_ACLK] [get_bd_pins processing_system7_0/S_AXI_HP1_ACLK] [get_bd_pins processing_system7_0/S_AXI_HP2_ACLK] [get_bd_pins processing_system7_0/S_AXI_HP3_ACLK] [get_bd_pins processing_system7_0_axi_periph/ACLK] [get_bd_pins processing_system7_0_axi_periph/M00_ACLK] [get_bd_pins processing_system7_0_axi_periph/M01_ACLK] [get_bd_pins processing_system7_0_axi_periph/M02_ACLK] [get_bd_pins processing_system7_0_axi_periph/M03_ACLK] [get_bd_pins processing_system7_0_axi_periph/M04_ACLK] [get_bd_pins processing_system7_0_axi_periph/M05_ACLK] [get_bd_pins processing_system7_0_axi_periph/M06_ACLK] [get_bd_pins processing_system7_0_axi_periph/M07_ACLK] [get_bd_pins processing_system7_0_axi_periph/S00_ACLK]
  connect_bd_net -net rst_processing_system7_0_100M_peripheral_aresetn [get_bd_pins atg_acp/s_axi_aresetn] [get_bd_pins atg_gp0/s_axi_aresetn] [get_bd_pins atg_hp0/s_axi_aresetn] [get_bd_pins atg_hp1/s_axi_aresetn] [get_bd_pins atg_hp2/s_axi_aresetn] [get_bd_pins atg_hp3/s_axi_aresetn] [get_bd_pins axi_gpio_0/s_axi_aresetn] [get_bd_pins axi_mem_intercon/ARESETN] [get_bd_pins axi_mem_intercon/M00_ARESETN] [get_bd_pins axi_mem_intercon/S00_ARESETN] [get_bd_pins axi_mem_intercon_1/ARESETN] [get_bd_pins axi_mem_intercon_1/M00_ARESETN] [get_bd_pins axi_mem_intercon_1/S00_ARESETN] [get_bd_pins axi_mem_intercon_2/ARESETN] [get_bd_pins axi_mem_intercon_2/M00_ARESETN] [get_bd_pins axi_mem_intercon_2/S00_ARESETN] [get_bd_pins axi_mem_intercon_3/ARESETN] [get_bd_pins axi_mem_intercon_3/M00_ARESETN] [get_bd_pins axi_mem_intercon_3/S00_ARESETN] [get_bd_pins axi_mem_intercon_4/ARESETN] [get_bd_pins axi_mem_intercon_4/M00_ARESETN] [get_bd_pins axi_mem_intercon_4/S00_ARESETN] [get_bd_pins axi_mem_intercon_5/ARESETN] [get_bd_pins axi_mem_intercon_5/M00_ARESETN] [get_bd_pins axi_mem_intercon_5/S00_ARESETN] [get_bd_pins axi_perf_mon_0/core_aresetn] [get_bd_pins axi_perf_mon_0/m_axis_aresetn] [get_bd_pins axi_perf_mon_0/s_axi_aresetn] [get_bd_pins axi_perf_mon_0/slot_0_axi_aresetn] [get_bd_pins axi_perf_mon_0/slot_1_axi_aresetn] [get_bd_pins axi_perf_mon_0/slot_2_axi_aresetn] [get_bd_pins axi_perf_mon_0/slot_3_axi_aresetn] [get_bd_pins axi_perf_mon_0/slot_4_axi_aresetn] [get_bd_pins axi_perf_mon_0/slot_5_axi_aresetn] [get_bd_pins processing_system7_0/FCLK_RESET0_N] [get_bd_pins processing_system7_0_axi_periph/ARESETN] [get_bd_pins processing_system7_0_axi_periph/M00_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M01_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M02_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M03_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M04_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M05_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M06_ARESETN] [get_bd_pins processing_system7_0_axi_periph/M07_ARESETN] [get_bd_pins processing_system7_0_axi_periph/S00_ARESETN]

  # Create address segments
  create_bd_addr_seg -range 0x20000000 -offset 0x0 [get_bd_addr_spaces atg_acp/Data] [get_bd_addr_segs processing_system7_0/S_AXI_ACP/ACP_DDR_LOWOCM] SEG_processing_system7_0_ACP_DDR_LOWOCM
  create_bd_addr_seg -range 0x400000 -offset 0xE0000000 [get_bd_addr_spaces atg_acp/Data] [get_bd_addr_segs processing_system7_0/S_AXI_ACP/ACP_IOP] SEG_processing_system7_0_ACP_IOP
  create_bd_addr_seg -range 0x40000000 -offset 0x40000000 [get_bd_addr_spaces atg_acp/Data] [get_bd_addr_segs processing_system7_0/S_AXI_ACP/ACP_M_AXI_GP0] SEG_processing_system7_0_ACP_M_AXI_GP0
  create_bd_addr_seg -range 0x1000000 -offset 0xFC000000 [get_bd_addr_spaces atg_acp/Data] [get_bd_addr_segs processing_system7_0/S_AXI_ACP/ACP_QSPI_LINEAR] SEG_processing_system7_0_ACP_QSPI_LINEAR
  create_bd_addr_seg -range 0x20000000 -offset 0x0 [get_bd_addr_spaces atg_gp0/Data] [get_bd_addr_segs processing_system7_0/S_AXI_GP0/GP0_DDR_LOWOCM] SEG_processing_system7_0_GP0_DDR_LOWOCM
  create_bd_addr_seg -range 0x400000 -offset 0xE0000000 [get_bd_addr_spaces atg_gp0/Data] [get_bd_addr_segs processing_system7_0/S_AXI_GP0/GP0_IOP] SEG_processing_system7_0_GP0_IOP
  create_bd_addr_seg -range 0x40000000 -offset 0x40000000 [get_bd_addr_spaces atg_gp0/Data] [get_bd_addr_segs processing_system7_0/S_AXI_GP0/GP0_M_AXI_GP0] SEG_processing_system7_0_GP0_M_AXI_GP0
  create_bd_addr_seg -range 0x1000000 -offset 0xFC000000 [get_bd_addr_spaces atg_gp0/Data] [get_bd_addr_segs processing_system7_0/S_AXI_GP0/GP0_QSPI_LINEAR] SEG_processing_system7_0_GP0_QSPI_LINEAR
  create_bd_addr_seg -range 0x20000000 -offset 0x0 [get_bd_addr_spaces atg_hp0/Data] [get_bd_addr_segs processing_system7_0/S_AXI_HP0/HP0_DDR_LOWOCM] SEG_processing_system7_0_HP0_DDR_LOWOCM
  create_bd_addr_seg -range 0x20000000 -offset 0x0 [get_bd_addr_spaces atg_hp1/Data] [get_bd_addr_segs processing_system7_0/S_AXI_HP1/HP1_DDR_LOWOCM] SEG_processing_system7_0_HP1_DDR_LOWOCM
  create_bd_addr_seg -range 0x20000000 -offset 0x0 [get_bd_addr_spaces atg_hp2/Data] [get_bd_addr_segs processing_system7_0/S_AXI_HP2/HP2_DDR_LOWOCM] SEG_processing_system7_0_HP2_DDR_LOWOCM
  create_bd_addr_seg -range 0x20000000 -offset 0x0 [get_bd_addr_spaces atg_hp3/Data] [get_bd_addr_segs processing_system7_0/S_AXI_HP3/HP3_DDR_LOWOCM] SEG_processing_system7_0_HP3_DDR_LOWOCM
  create_bd_addr_seg -range 0x800000 -offset 0x44000000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs atg_acp/S_AXI/Reg0] SEG_atg_acp_Reg0
  create_bd_addr_seg -range 0x800000 -offset 0x45000000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs atg_gp0/S_AXI/Reg0] SEG_atg_gp0_Reg0
  create_bd_addr_seg -range 0x800000 -offset 0x40000000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs atg_hp0/S_AXI/Reg0] SEG_atg_hp0_Reg0
  create_bd_addr_seg -range 0x800000 -offset 0x41000000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs atg_hp1/S_AXI/Reg0] SEG_atg_hp1_Reg0
  create_bd_addr_seg -range 0x800000 -offset 0x42000000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs atg_hp2/S_AXI/Reg0] SEG_atg_hp2_Reg0
  create_bd_addr_seg -range 0x800000 -offset 0x43000000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs atg_hp3/S_AXI/Reg0] SEG_atg_hp3_Reg0
  create_bd_addr_seg -range 0x10000 -offset 0x47000000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_gpio_0/S_AXI/MYREG0] SEG_axi_gpio_0_MYREG0
  create_bd_addr_seg -range 0x800000 -offset 0x46000000 [get_bd_addr_spaces processing_system7_0/Data] [get_bd_addr_segs axi_perf_mon_0/S_AXI/Reg] SEG_axi_perf_mon_0_Reg

  # Perform GUI Layout
  regenerate_bd_layout -layout_string {
   guistr: "# # String gsaved with Nlview 6.5.5  2015-06-26 bk=1.3371 VDI=38 GEI=35 GUI=JA:1.8
#  -string -flagsOSRD
preplace port DDR -pg 1 -y 2380 -defaultsOSRD
preplace port FIXED_IO -pg 1 -y 2400 -defaultsOSRD
preplace inst atg_hp1 -pg 1 -lvl 2 -y 440 -defaultsOSRD
preplace inst atg_acp -pg 1 -lvl 2 -y 160 -defaultsOSRD
preplace inst atg_hp2 -pg 1 -lvl 2 -y 580 -defaultsOSRD
preplace inst atg_gp0 -pg 1 -lvl 2 -y 720 -defaultsOSRD
preplace inst axi_mem_intercon_1 -pg 1 -lvl 3 -y 1990 -defaultsOSRD
preplace inst atg_hp3 -pg 1 -lvl 2 -y 860 -defaultsOSRD
preplace inst axi_mem_intercon_2 -pg 1 -lvl 3 -y 2210 -defaultsOSRD
preplace inst axi_mem_intercon_3 -pg 1 -lvl 3 -y 1770 -defaultsOSRD
preplace inst axi_mem_intercon_4 -pg 1 -lvl 3 -y 2460 -defaultsOSRD
preplace inst axi_gpio_0 -pg 1 -lvl 2 -y 1030 -defaultsOSRD
preplace inst axi_mem_intercon_5 -pg 1 -lvl 3 -y 2680 -defaultsOSRD
preplace inst axi_mem_intercon -pg 1 -lvl 3 -y 1550 -defaultsOSRD
preplace inst processing_system7_0_axi_periph -pg 1 -lvl 1 -y 440 -defaultsOSRD
preplace inst processing_system7_0 -pg 1 -lvl 4 -y 2460 -defaultsOSRD
preplace inst axi_perf_mon_0 -pg 1 -lvl 3 -y 720 -defaultsOSRD
preplace inst atg_hp0 -pg 1 -lvl 2 -y 300 -defaultsOSRD
preplace netloc processing_system7_0_DDR 1 4 1 NJ
preplace netloc axi_mem_intercon_4_M00_AXI 1 3 1 N
preplace netloc processing_system7_0_axi_periph_M03_AXI 1 1 1 370
preplace netloc processing_system7_0_axi_periph_M00_AXI 1 1 1 320
preplace netloc processing_system7_0_axi_periph_M07_AXI 1 1 1 320
preplace netloc processing_system7_0_M_AXI_GP0 1 0 5 20 2330 NJ 2330 NJ 2330 NJ 2250 1510
preplace netloc axi_mem_intercon_1_M00_AXI 1 3 1 1050
preplace netloc processing_system7_0_axi_periph_M05_AXI 1 1 1 340
preplace netloc atg_hp0_M_AXI 1 2 1 660
preplace netloc atg_gp0_M_AXI 1 2 1 730
preplace netloc axi_mem_intercon_M00_AXI 1 3 1 1060
preplace netloc processing_system7_0_axi_periph_M02_AXI 1 1 1 N
preplace netloc atg_hp3_M_AXI 1 2 1 690
preplace netloc rst_processing_system7_0_100M_peripheral_aresetn 1 0 5 40 710 360 960 720 2340 NJ 2680 1500
preplace netloc processing_system7_0_axi_periph_M06_AXI 1 1 2 NJ 80 650
preplace netloc atg_hp1_M_AXI 1 2 1 710
preplace netloc atg_acp_M_AXI 1 2 1 670
preplace netloc axi_gpio_0_gpio_io_o 1 1 2 390 950 650
preplace netloc processing_system7_0_FIXED_IO 1 4 1 NJ
preplace netloc axi_mem_intercon_3_M00_AXI 1 3 1 1040
preplace netloc axi_mem_intercon_2_M00_AXI 1 3 1 1030
preplace netloc processing_system7_0_FCLK_CLK0 1 0 5 30 700 380 940 700 2800 1040 2670 1510
preplace netloc atg_hp2_M_AXI 1 2 1 680
preplace netloc processing_system7_0_axi_periph_M04_AXI 1 1 1 350
preplace netloc processing_system7_0_axi_periph_M01_AXI 1 1 1 370
preplace netloc axi_mem_intercon_5_M00_AXI 1 3 1 1010
levelinfo -pg 1 0 180 520 870 1280 1530 -top 0 -bot 2810
",
}

  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


