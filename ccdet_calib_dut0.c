#include "platform.h"

int8_t ccdet_calib_dut0(const ccdet_calib_config_t *table, uint8_t table_size, uint8_t cc_id)
{
	uint8_t tx_data;
	uint8_t tx_buf[10];
	uint8_t rx_buf[10];

	int8_t ret;

	for(uint8_t i=0;i<table_size;i++)
	{
		tx_data = table[i].vref_sel;
		ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x20, 0x10, 1, &tx_data, 1);
		if(ret != 0x00)	return -1;

		if(cc_id == 1)
		{
			dac7678_set_voltage_mv(DUT0_IIC_ADDR, DAC_ADDR, CC1_VOL_DAC_CH, table[i].dac_data);
		}
		else
		{
			dac7678_set_voltage_mv(DUT0_IIC_ADDR, DAC_ADDR, CC2_VOL_DAC_CH, table[i].dac_data);
		}
		delay_ms(10);

		ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, (table[i].vref_reg) & 0xFF, (table[i].vref_reg) >> 8, 2, rx_buf, 0);
		if(ret != 0x00)	return -1;

		uint16_t base_val  = (rx_buf[2] << 8) | rx_buf[1];
		base_val &= ~(VREF_MASK << table[i].vref_shift);

		uint8_t low = 0;
		uint8_t high = 15;
		uint8_t best_gear = 16;

		while(low <= high)
		{
			uint8_t mid = low + (high - low) / 2;
			uint16_t reg_val = base_val | (mid << table[i].vref_shift);

			tx_buf[0] = reg_val & 0xFF;
	        tx_buf[1] = reg_val >> 8;
			ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, (table[i].vref_reg) & 0xFF, (table[i].vref_reg) >> 8, 0, tx_buf, 2);
			if(ret != 0x00)	return -1;

			delay_ms(1);

			ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x29, 0x10, 1, rx_buf, 0);
			if(ret != 0x00)	return -1;

			uint8_t bit_status = (rx_buf[1] >> table[i].check_bit) & 0x01;
			if(bit_status == 0)
			{
				best_gear = mid;

				if(mid == 0)	break;

				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}

		if(best_gear == 16 || best_gear == 0)	return -1;

		xil_printf("dut0 cc_id = %x, ccdet_best_offset = %x\r\n", cc_id, best_gear);

		uint16_t final_reg_val = base_val | (best_gear << table[i].vref_shift);

		tx_buf[0] = final_reg_val & 0xFF;
		tx_buf[1] = final_reg_val >> 8;
		ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, (table[i].vref_reg) & 0xFF, (table[i].vref_reg) >> 8, 0, tx_buf, 2);
		if(ret != 0x00)	return -1;
	}

	return 0;
}
