#include "platform.h"

int8_t pattern_rp12k_dut0()
{
	uint8_t tx_data;
	uint8_t tx_buf[10];
	uint8_t rx_buf[10];

	int8_t ret;

	//relay control
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 5, 1);
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 8, 1);
	delay_ms(50);

	tx_data = 0x0e;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x22, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	uint16_t cc1_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC1_VOL_ADC_CH, 10);
	xil_printf("dut0 cc1_adc_data = %x\r\n", cc1_adc_data);

	if(cc1_adc_data < VCON_SW_ON_VOL)
	{
		return -1;
	}

	tx_data = 0x06;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x22, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	cc1_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC1_VOL_ADC_CH, 10);
	xil_printf("dut0 cc1_adc_data = %x\r\n", cc1_adc_data);

	if(cc1_adc_data > VCON_SW_OFF_VOL)
	{
		return -1;
	}

	tx_data = 0x0e;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x23, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	uint16_t cc2_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC2_VOL_ADC_CH, 10);
	xil_printf("dut0 cc2_adc_data = %x\r\n", cc2_adc_data);

	if(cc2_adc_data < VCON_SW_ON_VOL)
	{
		return -1;
	}

	tx_data = 0x06;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x23, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	cc2_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC2_VOL_ADC_CH, 10);
	xil_printf("dut0 cc2_adc_data = %x\r\n", cc2_adc_data);

	if(cc2_adc_data > VCON_SW_OFF_VOL)
	{
		return -1;
	}

	//relay control
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 5, 0);
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 8, 0);
	delay_ms(50);

	uint16_t ldo3v3_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, LDO3V3_VOL_ADC_CH, 10);
	xil_printf("dut0 ldo3v3_adc_data = %x\r\n", ldo3v3_adc_data);

	uint16_t rp12k_vref = (51.0 / (120.0 * 1.00 + 51.0)) * ldo3v3_adc_data * 2;
	uint16_t rp12k_min  = (51.0 / (120.0 * 1.05 + 51.0)) * ldo3v3_adc_data * 2;
	uint16_t rp12k_max  = (51.0 / (120.0 * 0.95 + 51.0)) * ldo3v3_adc_data * 2;

//	uint16_t rp36k_vref = (51.0 / (360.0 * 1.000 + 51.0)) * ldo3v3_adc_data * 2;
	uint16_t rp36k_min  = (51.0 / (360.0 * 1.085 + 51.0)) * ldo3v3_adc_data * 2;
	uint16_t rp36k_max  = (51.0 / (360.0 * 0.915 + 51.0)) * ldo3v3_adc_data * 2;

//	uint16_t rp4p7k_vref = (51.0 / (47.0 * 1.00 + 51.0)) * ldo3v3_adc_data * 2;
	uint16_t rp4p7k_min  = (51.0 / (47.0 * 1.05 + 51.0)) * ldo3v3_adc_data * 2;
	uint16_t rp4p7k_max  = (51.0 / (47.0 * 0.95 + 51.0)) * ldo3v3_adc_data * 2;

	uint16_t best_vol = 0;
	uint16_t min_diff = 0xFFFF;

	uint8_t start_gear = 15;
	uint8_t end_gear = 15;
	int8_t step = 1;

	tx_data = 0x46;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x22, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_data = 0x46;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x23, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x0C, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	uint16_t base_val = (rx_buf[2] << 8) | rx_buf[1];
	base_val &= ~(0x1F << 5);

	uint16_t reg_val = base_val | (15 << 5);

	tx_buf[0] = reg_val & 0xFF;
	tx_buf[1] = reg_val >> 8;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x0C, 0x01, 0, tx_buf, 2);
	if(ret != 0x00) return -1;

	delay_ms(1);

	cc1_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC1_VOL_ADC_CH, 10);

	if(cc1_adc_data > rp12k_vref)
	{
		dut0.g_rp12k_signbit = 0;
		start_gear = 15;
		end_gear = 31;
		step = 1;
	}
	else
	{
		dut0.g_rp12k_signbit = 1;
		start_gear = 15;
		end_gear = 0;
		step = -1;
	}

	for(int8_t i=start_gear;i!=(end_gear+step);i+=step)
	{
		reg_val = base_val | (i << 5);

		tx_buf[0] = reg_val & 0xFF;
		tx_buf[1] = reg_val >> 8;
		ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x0C, 0x01, 0, tx_buf, 2);
		if(ret != 0x00) return -1;

		delay_ms(1);

		cc1_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC1_VOL_ADC_CH, 10);
		xil_printf("dut0 cc1_adc_data = %x, i = %d\r\n", cc1_adc_data, i);

		uint16_t diff = abs((int)cc1_adc_data - (int)rp12k_vref);

		if(diff < min_diff)
		{
			min_diff = diff;
			if(dut0.g_rp12k_signbit == 0)
			{
				dut0.g_rp12k_offset = i - 15;
			}
			else
			{
				dut0.g_rp12k_offset = 15 - i;
			}
			best_vol = cc1_adc_data;
		}
	}
	xil_printf("dut0 rp12k_signbit = %x, rp12k_best_offset = %x\r\n", dut0.g_rp12k_signbit, dut0.g_rp12k_offset);

	if((best_vol < rp12k_min) || (best_vol > rp12k_max))
	{
		print("dut0 pattern_rp12k fail!\r\n\r\n");
		return -1;
	}

	//cc2 rp12k test
	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x0C, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	reg_val = (rx_buf[2] << 8) | rx_buf[1];
	reg_val &= ~0x3FF;
	if(dut0.g_rp12k_signbit == 0)
	{
		reg_val |= ((15 + dut0.g_rp12k_offset) << 5);
		reg_val |= (15 + dut0.g_rp12k_offset);
	}
	else
	{
		reg_val |= ((15 - dut0.g_rp12k_offset) << 5);
		reg_val |= (15 - dut0.g_rp12k_offset);
	}

	tx_buf[0] = reg_val & 0xFF;
    tx_buf[1] = reg_val >> 8;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x0C, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	cc2_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC2_VOL_ADC_CH, 10);
	if((cc2_adc_data < rp12k_min) || (cc2_adc_data > rp12k_max))
	{
		print("dut0 pattern_rp12k test fail!\r\n\r\n");
		return -1;
	}

	tx_data = 0x26;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x22, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_data = 0x26;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x23, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	//rp36k test
	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x0D, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	reg_val = (rx_buf[2] << 8) | rx_buf[1];
	reg_val &= ~0x3FF;
	if(dut0.g_rp12k_signbit == 0)
	{
		reg_val |= ((15 + dut0.g_rp12k_offset) << 5);
		reg_val |= (15 + dut0.g_rp12k_offset);
	}
	else
	{
		reg_val |= ((15 - dut0.g_rp12k_offset) << 5);
		reg_val |= (15 - dut0.g_rp12k_offset);
	}

	tx_buf[0] = reg_val & 0xFF;
    tx_buf[1] = reg_val >> 8;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x0D, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	cc1_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC1_VOL_ADC_CH, 10);
	cc2_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC2_VOL_ADC_CH, 10);
	if((cc1_adc_data < rp36k_min) || (cc1_adc_data > rp36k_max) || (cc2_adc_data < rp36k_min) || (cc2_adc_data > rp36k_max))
	{
		print("dut0 pattern_rp36k test fail!\r\n\r\n");
		return -1;
	}

	tx_data = 0x16;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x22, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_data = 0x16;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x23, 0x10, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	//rp4p7k test
	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x0E, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	reg_val = (rx_buf[2] << 8) | rx_buf[1];
	reg_val &= ~0x3FF;
	if(dut0.g_rp12k_signbit == 0)
	{
		reg_val |= ((15 + dut0.g_rp12k_offset) << 5);
		reg_val |= (15 + dut0.g_rp12k_offset);
	}
	else
	{
		reg_val |= ((15 - dut0.g_rp12k_offset) << 5);
		reg_val |= (15 - dut0.g_rp12k_offset);
	}

	tx_buf[0] = reg_val & 0xFF;
    tx_buf[1] = reg_val >> 8;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x0E, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	cc1_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC1_VOL_ADC_CH, 10);
	cc2_adc_data = ad7994_readcvsdata(DUT0_IIC_ADDR, ADC_ADDR, CC2_VOL_ADC_CH, 10);
	if((cc1_adc_data < rp4p7k_min) || (cc1_adc_data > rp4p7k_max) || (cc2_adc_data < rp4p7k_min) || (cc2_adc_data > rp4p7k_max))
	{
		print("dut0 pattern_rp4p7k test fail!\r\n\r\n");
		return -1;
	}

	dut0.g_pattern_timer = 0x5fff;
	dut0.g_ft2_pattern_num++;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);
	print("dut0 pattern_rp all pass!\r\n\r\n\r\n");

	return 0;
}
