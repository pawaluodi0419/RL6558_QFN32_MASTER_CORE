#include "platform.h"

int8_t pattern_efuse_check_dut0()
{
	uint8_t tx_data;
//	uint8_t tx_buf[10];
	uint8_t rx_buf[50];

	int8_t ret;

	//relay control
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 23, 0);
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 13, 1);
	delay_ms(50);
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 14, 0);
	delay_ms(50);

	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);

	ret = smbus_xfer_packet(GET_IC_STATUS, DUT_ADDR, 0x00, 0x00, 10, rx_buf, 0);
	if(ret != 0x00)	return -1;

	xil_printf("dut0 IC version: 0x%02x\r\n\r\n", rx_buf[2]);
	if((rx_buf[9] != 0x58) || (rx_buf[10] != 0x65))
	{
		print("dut0 is not RL6558!\r\n\r\n");
		return -1;
	}

	//enable efuse clock
	tx_data = 0x07;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x05, 0x11, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	//read efuse
	ret = smbus_xfer_packet(READ_EFUSE, DUT_ADDR, 0x00, 0x00, 27, rx_buf, 0);
	if(ret != 0x00)	return -1;

	uint8_t efuse_all_zero = 1;

	for(uint8_t i=0;i<27;i++)
	{
		if(rx_buf[i+1] != 0x00)
		{
			efuse_all_zero = 0;
		}
		xil_printf("dut0 efuse_read_data[%02d]: %02x\r\n", i, rx_buf[i+1]);
	}
	print("\r\n");

	if(efuse_all_zero)
	{
		print("dut0 efuse is all zero!\r\n\r\n");
		return -1;
	}

	print("dut0 efuse check pass!\r\n\r\n\r\n");

	dut0.g_ft2_pattern_num = 0x0e;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);

	dut0.g_eqa_pass_cnt++;
	xil_printf("dut0.g_eqa_test_cnt = %d, dut0.g_eqa_pass_cnt = %d\r\n\r\n", dut0.g_eqa_test_cnt, dut0.g_eqa_pass_cnt);

	pattern_safe_state_dut0();

	return 0;
}
