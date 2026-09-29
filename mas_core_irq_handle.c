#include "platform.h"

void axi_mas_core_intrq_handle()
{
	print(">>>> enter mas_core int!\r\n");

	if(CORE2CORE_BRIDGE_READ_REG(DUT0_MAS_CORE_BASEADDR, 24) & 0x01)
	{
		g_rec_sla_1_data = CORE2CORE_BRIDGE_READ_REG(DUT0_MAS_CORE_BASEADDR, 0);
		xil_printf(">>>> master get slave_1 data = 0x%x\r\n", g_rec_sla_1_data);

		//clear int
		CORE2CORE_BRIDGE_WRITE_REG(DUT0_MAS_CORE_BASEADDR, 24, 1);
	}

	if((CORE2CORE_BRIDGE_READ_REG(DUT0_MAS_CORE_BASEADDR, 24) >> 1) & 0x01)
	{
		g_rec_sla_2_data = CORE2CORE_BRIDGE_READ_REG(DUT0_MAS_CORE_BASEADDR, 4);
		xil_printf(">>>> master get slave_2 data = 0x%x\r\n", g_rec_sla_2_data);

		//clear int
		CORE2CORE_BRIDGE_WRITE_REG(DUT0_MAS_CORE_BASEADDR, 24, (1 << 1));
	}

	if((CORE2CORE_BRIDGE_READ_REG(DUT0_MAS_CORE_BASEADDR, 24) >> 2) & 0x01)
	{
		g_rec_sla_3_data = CORE2CORE_BRIDGE_READ_REG(DUT0_MAS_CORE_BASEADDR, 8);
		xil_printf(">>>> master get slave_3 data = 0x%x\r\n", g_rec_sla_3_data);

		//clear int
		CORE2CORE_BRIDGE_WRITE_REG(DUT0_MAS_CORE_BASEADDR, 24, (1 << 2));
	}
}
