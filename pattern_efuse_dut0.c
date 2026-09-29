#include "platform.h"

int8_t pattern_efuse_dut0()
{
//	uint8_t tx_data;
//	uint8_t tx_buf[10];
	uint8_t rx_buf[50];

    efuse_data_t write_data;
    efuse_data_t read_data;

	int8_t ret;

    memset(write_data.bytes, 0, sizeof(write_data.bytes));
    memset(read_data.bytes, 0, sizeof(read_data.bytes));

	write_data.bits.efuse_data_valid = 1;
	write_data.bits.ldo_3v3_valid = 1;
	write_data.bits.rp12k_valid = 1;
	write_data.bits.cc_valid = 1;
	write_data.bits.adc_valid = 1;
	write_data.bits.efuse_tpp_valid = 1;
	write_data.bits.rc10us_timer_valid = 1;

	write_data.bits.ldo_3v3 = dut0.g_ldo3v3_offset;

	write_data.bits.rp_12k = dut0.g_rp12k_signbit << 5 | dut0.g_rp12k_offset;

	write_data.bits.adc_a = dut0.g_adc_a;

	write_data.bits.adc_b = dut0.g_adc_b_signbit << 7 | dut0.g_adc_b_offset;

	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x0F, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	write_data.bits.reg_cc_vref_cfg0 = (rx_buf[2] << 8) | rx_buf[1];

	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x10, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	write_data.bits.reg_cc_vref_cfg1 = (rx_buf[2] << 8) | rx_buf[1];

	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x11, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	write_data.bits.reg_cc_vref_cfg2 = (rx_buf[2] << 8) | rx_buf[1];

	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x12, 0x01, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;

	write_data.bits.reg_cc_vref_cfg3 = (rx_buf[2] << 8) | rx_buf[1];

	write_data.bits.efuse_tpp_l = (dut0.g_freq_cnt * 160) / 1600 - 1;

	write_data.bits.rc10us_timer_threshold = (dut0.g_freq_cnt * 80) / 1600 - 1;

	for(uint8_t i=0;i<27;i++)
	{
		xil_printf("dut0 efuse_write_data[%02d]: %02x\r\n", i, write_data.bytes[i]);
	}
	print("\r\n");

	if(dut0.g_ft2_retest == 0)
	{
		//write efuse
		ret = smbus_xfer_packet(WRITE_EFUSE, DUT_ADDR, 0x00, 0x00, 27, write_data.bytes, 27);
		if(ret != 0x00)	return -1;

		//read efuse
		ret = smbus_xfer_packet(READ_EFUSE, DUT_ADDR, 0x00, 0x00, 27, rx_buf, 0);
		if(ret != 0x00)	return -1;

		for(uint8_t i=0;i<27;i++)
		{
			read_data.bytes[i] = rx_buf[i+1];
			xil_printf("dut0 efuse_read_data[%02d]: %02x\r\n", i, read_data.bytes[i]);
		}
		print("\r\n");

		 if(memcmp(write_data.bytes, read_data.bytes, sizeof(write_data.bytes)) == 0)
		 {
			 print("dut0 efuse write/read compare pass!\r\n\r\n");
			 write_data.bits.efuse_rw_test_result = 1;

			 ret = smbus_xfer_packet(WRITE_EFUSE, DUT_ADDR, 0x00, 0x00, 27, write_data.bytes, 27);
			 if(ret != 0x00)	return -1;
		 }
		 else
		 {
			 print("dut0 efuse write/read compare fail!\r\n\r\n");
			 return -1;
		 }
	}
	else
	{
		//read efuse
		ret = smbus_xfer_packet(READ_EFUSE, DUT_ADDR, 0x00, 0x00, 27, rx_buf, 0);
		if(ret != 0x00)	return -1;

		for(uint8_t i=0;i<27;i++)
		{
			read_data.bytes[i] = rx_buf[i+1];
			xil_printf("dut0 efuse_read_data[%02d]: %02x\r\n", i, read_data.bytes[i]);
		}
		print("\r\n");

		//judge tolerance: adc_a
		if(abs((int)write_data.bits.adc_a - (int)read_data.bits.adc_a) > ADC_A_TOLERANCE)
		{
			print("dut0 adc_a tolerance judge fail!\r\n\r\n");
			return -1;
		}

		int write_adc_b_real;
		int read_adc_b_real;

		if(write_data.bits.adc_b >> 7)
		{
		    write_adc_b_real = -(write_data.bits.adc_b & 0x7F);
		}
		else
		{
		    write_adc_b_real = (write_data.bits.adc_b & 0x7F);
		}

		if(read_data.bits.adc_b >> 7)
		{
		    read_adc_b_real = -(read_data.bits.adc_b & 0x7F);
		}
		else
		{
		    read_adc_b_real = (read_data.bits.adc_b & 0x7F);
		}

		//judge tolerance: adc_b
		if(abs(write_adc_b_real - read_adc_b_real) > ADC_B_TOLERANCE)
		{
		    print("dut0 adc_b tolerance judge fail!\r\n\r\n");
		    return -1;
		}

		//judge tolerance: ldo3v3
		if(abs((int)write_data.bits.ldo_3v3 - (int)read_data.bits.ldo_3v3) > LDO3V3_TOLERANCE)
		{
			print("dut0 ldo_3v3 tolerance judge fail!\r\n\r\n");
			return -1;
		}

		int write_rp12k_real;
		int read_rp12k_real;

		if(write_data.bits.rp_12k >> 5)
		{
		    write_rp12k_real = -(write_data.bits.rp_12k & 0x1F);
		}
		else
		{
			write_rp12k_real = (write_data.bits.rp_12k & 0x1F);
		}

		if(read_data.bits.rp_12k >> 5)
		{
		    read_rp12k_real = -(read_data.bits.rp_12k & 0x1F);
		}
		else
		{
		    read_rp12k_real = (read_data.bits.rp_12k & 0x1F);
		}

		//judge tolerance: rp12k
		if(abs(write_rp12k_real - read_rp12k_real) > RP12K_TOLERANCE)
		{
		    print("dut0 rp12k tolerance judge fail!\r\n\r\n");
		    return -1;
		}

		//judge tolerance: ccdet
		if((abs((int)(write_data.bits.reg_cc_vref_cfg0 & 0x0F) - (int)(read_data.bits.reg_cc_vref_cfg0 & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg0 >> 4) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg0 >> 4) & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg0 >> 8) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg0 >> 8) & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg0 >> 12) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg0 >> 12) & 0x0F)) > CCDET_TOLERANCE) ||

		   (abs((int)(write_data.bits.reg_cc_vref_cfg1 & 0x0F) - (int)(read_data.bits.reg_cc_vref_cfg1 & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg1 >> 4) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg1 >> 4) & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg1 >> 8) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg1 >> 8) & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg1 >> 12) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg1 >> 12) & 0x0F)) > CCDET_TOLERANCE) ||

		   (abs((int)(write_data.bits.reg_cc_vref_cfg2 & 0x0F) - (int)(read_data.bits.reg_cc_vref_cfg2 & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg2 >> 4) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg2 >> 4) & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg2 >> 8) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg2 >> 8) & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg2 >> 12) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg2 >> 12) & 0x0F)) > CCDET_TOLERANCE) ||

		   (abs((int)(write_data.bits.reg_cc_vref_cfg3 & 0x0F) - (int)(read_data.bits.reg_cc_vref_cfg3 & 0x0F)) > CCDET_TOLERANCE) ||
		   (abs((int)((write_data.bits.reg_cc_vref_cfg3 >> 4) & 0x0F) - (int)((read_data.bits.reg_cc_vref_cfg3 >> 4) & 0x0F)) > CCDET_TOLERANCE))
		{
			print("dut0 ccdet tolerance judge fail!\r\n\r\n");
			return -1;
		}

	}

	dut0.g_pattern_timer = 0x5fff;
	dut0.g_ft2_pattern_num++;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);
	print("dut0 pattern_efuse pass!\r\n\r\n\r\n");

	return 0;
}
