/******************************************************************************
*
* Copyright (C) 2018-2019 Xilinx, Inc.  All rights reserved.
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
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*
*
******************************************************************************/

#include "xpm_domain_iso.h"
#include "xpm_regs.h"
#include "xpm_powerdomain.h"
#include "xpm_subsystem.h"
#include "xpm_pldomain.h"

/*TODO: Below data should come from topology */
XPm_Iso XPmDomainIso_List[XPM_NODEIDX_ISO_MAX] = {
	[XPM_NODEIDX_ISO_FPD_PL_TEST] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_FPD_PL_TEST),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_FPD_PL_TEST_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_FPD, PM_SUBSYS_PL },
	},
	[XPM_NODEIDX_ISO_FPD_PL] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_FPD_PL),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_FPD_PL_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_FPD, PM_SUBSYS_PL },
	},
	[XPM_NODEIDX_ISO_FPD_SOC] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_FPD_SOC),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_FPD_SOC_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_FPD, PM_POWER_NOC},
	},
	[XPM_NODEIDX_ISO_LPD_CPM_DFX] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_LPD_CPM_DFX),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_LPD_CPM_DFX_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_LPD, PM_POWER_CPM },
	},
	[XPM_NODEIDX_ISO_LPD_CPM] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_LPD_CPM),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_LPD_CPM_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_LPD, PM_POWER_CPM },
	},
	[XPM_NODEIDX_ISO_LPD_PL_TEST] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_LPD_PL_TEST),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_LPD_PL_TEST_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_LPD, PM_SUBSYS_PL },
	},
	[XPM_NODEIDX_ISO_LPD_PL] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_LPD_PL),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_LPD_PL_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_LPD, PM_SUBSYS_PL },
	},
	[XPM_NODEIDX_ISO_LPD_SOC] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_LPD_SOC),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_LPD_SOC_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_LPD, PM_POWER_NOC },
	},
	[XPM_NODEIDX_ISO_PMC_LPD_DFX] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PMC_LPD_DFX),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_PMC_LPD_DFX_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_PMC, PM_POWER_LPD },
	},
	[XPM_NODEIDX_ISO_PMC_LPD] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PMC_LPD),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_PMC_LPD_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_PMC, PM_POWER_LPD },
	},
	[XPM_NODEIDX_ISO_PMC_PL_CFRAME] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PMC_PL_CFRAME),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_PMC_PL_CFRAME_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_PMC, PM_SUBSYS_PL },
	},
	[XPM_NODEIDX_ISO_PMC_PL_TEST] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PMC_PL_TEST),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_PMC_PL_TEST_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_PMC, PM_SUBSYS_PL },
	},
	[XPM_NODEIDX_ISO_PMC_PL] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PMC_PL),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_PMC_PL_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_PMC, PM_SUBSYS_PL },
	},
	[XPM_NODEIDX_ISO_PMC_SOC_NPI] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PMC_SOC_NPI),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_PMC_SOC_NPI_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_PMC, PM_POWER_NOC },
	},
	[XPM_NODEIDX_ISO_PMC_SOC] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PMC_SOC),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_PMC_SOC_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_PMC, PM_POWER_NOC },
	},
	[XPM_NODEIDX_ISO_PL_SOC] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PL_SOC),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_PL_SOC_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_NOC },
	},
	[XPM_NODEIDX_ISO_VCCAUX_SOC] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_VCCAUX_SOC),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_VCCAUX_SOC_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_POWER_PMC, PM_POWER_NOC },
	},
	[XPM_NODEIDX_ISO_VCCRAM_SOC] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_VCCRAM_SOC),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_VCCRAM_SOC_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_NOC },
	},
	[XPM_NODEIDX_ISO_VCCAUX_VCCRAM] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_VCCAUX_VCCRAM),
		.Node.BaseAddress = PMC_GLOBAL_DOMAIN_ISO_CONTROL,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PMC_GLOBAL_DOMAIN_ISO_CNTRL_VCCAUX_VCCRAM_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_NOC },
	},
	[XPM_NODEIDX_ISO_PL_CPM_PCIEA0_ATTR] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PL_CPM_PCIEA0_ATTR),
		.Node.BaseAddress = PCIEA_ATTRIB_0_FABRICEN,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PCIEA_ATTRIB_0_FABRICEN_ATTR_SHIFT),
		.Polarity = PM_ACTIVE_LOW,
		.DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_CPM },
	},
	[XPM_NODEIDX_ISO_PL_CPM_PCIEA1_ATTR] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PL_CPM_PCIEA1_ATTR),
		.Node.BaseAddress = PCIEA_ATTRIB_1_FABRICEN,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(PCIEA_ATTRIB_1_FABRICEN_ATTR_SHIFT),
		.Polarity = PM_ACTIVE_LOW,
		.DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_CPM },
	},
	[XPM_NODEIDX_ISO_PL_CPM_RST_CPI0] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PL_CPM_RST_CPI0),
		.Node.BaseAddress = CPM_CRCPM_RST_CPI0,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(CPM_CRCPM_RST_CPI0_RESET_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_CPM },
	},
	[XPM_NODEIDX_ISO_PL_CPM_RST_CPI1] = {
		.Node.Id = ISOID(XPM_NODEIDX_ISO_PL_CPM_RST_CPI1),
		.Node.BaseAddress = CPM_CRCPM_RST_CPI1,
		.Node.State = PM_ISOLATION_ON,
		.Mask = BIT(CPM_CRCPM_RST_CPI1_RESET_SHIFT),
		.Polarity = PM_ACTIVE_HIGH,
		.DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_CPM },
	},
        [XPM_NODEIDX_ISO_GEM_TSU_CLK] = {
                .Node.Id = ISOID(XPM_NODEIDX_ISO_GEM_TSU_CLK),
                .Node.BaseAddress = CRL_RCLK_CTRL,
                .Node.State = PM_ISOLATION_ON,
                .Mask = CRL_RCLK_CTRL_CLKACT_GEM_TSU_MASK,
                .Polarity = PM_ACTIVE_LOW,
                .DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_LPD },
        },
        [XPM_NODEIDX_ISO_GEM0_TXRX_CLK] = {
                .Node.Id = ISOID(XPM_NODEIDX_ISO_GEM0_TXRX_CLK),
                .Node.BaseAddress = CRL_RCLK_CTRL,
                .Node.State = PM_ISOLATION_ON,
                .Mask = CRL_RCLK_CTRL_CLKACT_GEM0_TXRX_MASK,
                .Polarity = PM_ACTIVE_LOW,
                .DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_LPD },
        },
        [XPM_NODEIDX_ISO_GEM1_TXRX_CLK] = {
                .Node.Id = ISOID(XPM_NODEIDX_ISO_GEM1_TXRX_CLK),
                .Node.BaseAddress = CRL_RCLK_CTRL,
                .Node.State = PM_ISOLATION_ON,
                .Mask = CRL_RCLK_CTRL_CLKACT_GEM1_TXRX_MASK,
                .Polarity = PM_ACTIVE_LOW,
                .DependencyNodeHandles = { PM_SUBSYS_PL, PM_POWER_LPD },
        },
};

static XStatus XPmDomainIso_CheckDependencies(u32 IsoIdx)
{
	XStatus Status = XST_SUCCESS;
	u32 i=0, NodeId, Value;
	XPm_PowerDomain *PwrDomainNode;
	XPm_Subsystem *Subsystem;
	XPm_PlDomain *Pld;

	for( i=0; i<2; i++) {
		NodeId = XPmDomainIso_List[IsoIdx].DependencyNodeHandles[i];
		if (NODECLASS(NodeId) == XPM_NODECLASS_POWER) {
			PwrDomainNode = (XPm_PowerDomain *) XPmPower_GetById(NodeId);
			if ((NULL != PwrDomainNode) &&
			    (PwrDomainNode->Power.Node.State != XPM_POWER_STATE_ON)  &&
			    (PwrDomainNode->Power.Node.State != XPM_POWER_STATE_INITIALIZING)) {
				Status = XST_FAILURE;
				goto done;
			}
		} else if (NodeId == PM_SUBSYS_PL) {
			 Subsystem = XPmSubsystem_GetById(NodeId);

			 if(NULL == Subsystem) {
				Status = XPM_INVALID_SUBSYSID;
				goto done;
			 }

			 if(Subsystem->State != ONLINE) {
				 Pld = (XPm_PlDomain *)XPmPower_GetById(PM_POWER_PLD);
				 if (NULL == Pld) {
					 Status = XST_FAILURE;
					 goto done;
				 }

				 /* Right now as we don't have
				  * init finish for PLD, we decide PLD status based on
				  EOS bit */
				 PmIn32(Pld->CfuApbBaseAddr + CFU_APB_CFU_FGCR_OFFSET, Value);
				 if (CFU_APB_CFU_FGCR_EOS_MASK == (Value & CFU_APB_CFU_FGCR_EOS_MASK)) {
					 XPmSubsystem_SetState(PM_SUBSYS_PL, ONLINE);
					 Status = XST_SUCCESS;
				 } else {
					 Status = XST_FAILURE;
					 goto done;
				}
			}
		} else {
			Status = XST_FAILURE;
			goto done;
		}
	}
done:
	return Status;
}

XStatus XPmDomainIso_Control(u32 IsoIdx, u32 Enable)
{
	XStatus Status = XST_SUCCESS;
	u32 Mask;

	if (IsoIdx >= XPM_NODEIDX_ISO_MAX)
	{
		Status = XST_INVALID_PARAM;
		goto done;
	}

	Mask = XPmDomainIso_List[IsoIdx].Mask;

	if(Enable == TRUE) {
		if(XPmDomainIso_List[IsoIdx].Polarity == PM_ACTIVE_HIGH)
			XPm_RMW32(XPmDomainIso_List[IsoIdx].Node.BaseAddress, Mask, Mask);
		else
			XPm_RMW32(XPmDomainIso_List[IsoIdx].Node.BaseAddress, Mask, 0);
		XPmDomainIso_List[IsoIdx].Node.State = PM_ISOLATION_ON;
	} else if(Enable == FALSE_IMMEDIATE) {
		if(XPmDomainIso_List[IsoIdx].Polarity == PM_ACTIVE_HIGH)
			XPm_RMW32(XPmDomainIso_List[IsoIdx].Node.BaseAddress, Mask, 0);
		else
			XPm_RMW32(XPmDomainIso_List[IsoIdx].Node.BaseAddress, Mask, Mask);
		XPmDomainIso_List[IsoIdx].Node.State = PM_ISOLATION_OFF;
	} else {
		Status = XPmDomainIso_CheckDependencies(IsoIdx);
		if(XST_SUCCESS != Status)
		{
			/* Mark it pending */
			XPmDomainIso_List[IsoIdx].Node.State = PM_ISOLATION_REMOVE_PENDING;
			Status = XST_SUCCESS;
			goto done;
		}

		if(XPmDomainIso_List[IsoIdx].Polarity == PM_ACTIVE_HIGH)
			XPm_RMW32(XPmDomainIso_List[IsoIdx].Node.BaseAddress, Mask, 0);
		else
			XPm_RMW32(XPmDomainIso_List[IsoIdx].Node.BaseAddress, Mask, Mask);
		XPmDomainIso_List[IsoIdx].Node.State = PM_ISOLATION_OFF;
	}
done:
	return Status;
}

XStatus XPmDomainIso_ProcessPending(u32 PowerDomainId)
{
	XStatus Status = XST_SUCCESS;
	u32 i;

	(void)PowerDomainId;

	for(i=0; i< ARRAY_SIZE(XPmDomainIso_List); i++)
	{
		if(XPmDomainIso_List[i].Node.State == PM_ISOLATION_REMOVE_PENDING)
		{
			Status = XPmDomainIso_Control(i, FALSE);
		}
	}
	return Status;
}
