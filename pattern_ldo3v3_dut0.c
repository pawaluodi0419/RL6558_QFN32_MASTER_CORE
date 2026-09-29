#include "platform.h"

int8_t pattern_ldo3v3_dut0()
{
//	uint8_t tx_data;
	uint8_t tx_buf[10];
	uint8_t rx_buf[10];

	uint16_t best_vol = 0;
	uint16_t min_diff = 0xFFFF;

	int8_t ret;

	for(uint8_t i=0;i<4;i++)
	{
		ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x19, 0x01, 2, rx_buf, 0);
		if(ret != 0x00)	return -1;

		uint16_t reg_val  = (rx_buf[2] << 8) | rx_buf[1];
		reg_val &= ~(0x30);
		reg_val |= (i << 4);

		tx_buf[0] = reg_val & 0xFF;
        tx_buf[1] = reg_val >> 8;
		ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x19, 0x01, 0, tx_buf, 2);
		if(ret != 0x00)	return -1;

		delay_ms(1);

		uint16_t ldo3v3_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, LDO3V3_VOL_ADC_CH, 10);
		xil_printf("dut0 ldo3v3_adc_data = %x, i = %d\r\n", ldo3v3_adc_data, i);

		uint16_t diff = abs((int)ldo3v3_adc_data - (int)LDO3V3_REF);

		if (diff < min_diff)
		{
			min_diff = diff;
			dut0.g_ldo3v3_offset = i;
			best_vol = ldo3v3_adc_data;
		}
	}
	xil_printf("dut0 ldo3v3_best_offset = %x\r\n", dut0.g_ldo3v3_offset);

	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x19, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	uint16_t final_reg_val  = (rx_buf[2] << 8) | rx_buf[1];
	final_reg_val &= ~(0x30);
	final_reg_val |= (dut0.g_ldo3v3_offset << 4);

	tx_buf[0] = final_reg_val & 0xFF;
    tx_buf[1] = final_reg_val >> 8;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x19, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	if ((best_vol < LDO3V3_MIN) || (best_vol > LDO3V3_MAX))
	{
		print("dut0 pattern_ldo3v3 fail!\r\n\r\n");
		return -1;
	}

	dut0.g_pattern_timer = 0x5fff;
	dut0.g_ft2_pattern_num++;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);
	print("dut0 pattern_ldo3v3 pass!\r\n\r\n\r\n");

	return 0;
}
