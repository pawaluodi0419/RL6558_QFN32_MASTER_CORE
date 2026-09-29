#include "platform.h"

int8_t pattern_rc_clock_dut0()
{
	uint8_t tx_data;
//	uint8_t tx_buf[10];
	uint8_t rx_buf[10];

	uint8_t timeout;
	int8_t ret;

	//relay control
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 21, 1);
	delay_ms(50);

	//choose gpio8 as 24M clock input
	tx_data = 0x80;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x31, 0x11, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(1);

	//start counting
	tx_data = 0xc0;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x31, 0x11, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	//polling counting done
	for(timeout=0;timeout<50;timeout++)
	{
		ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x31, 0x11, 1, rx_buf, 0);
		if(ret != 0x00)	return -1;

		uint8_t bit_status = (rx_buf[1] >> 5) & 0x01;
		if(bit_status)
		{
			break;
		}
		delay_ms(1);
	}

	if(timeout == 50)
	{
		print("dut0 pattern_rc_clock timeout!\r\n\r\n");
		return -1;
	}

	ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x32, 0x11, 1, rx_buf, 0);
	if(ret != 0x00)	return -1;
	uint8_t freq_cnt_low = rx_buf[1];

	ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x33, 0x11, 1, rx_buf, 0);
	if(ret != 0x00)	return -1;
	uint8_t freq_cnt_high = rx_buf[1];

	dut0.g_freq_cnt = (freq_cnt_high << 8) | freq_cnt_low;
	xil_printf("dut0 freq_cnt = %x\r\n", dut0.g_freq_cnt);

	if((dut0.g_freq_cnt < FREQ_CNT_MIN) || (dut0.g_freq_cnt > FREQ_CNT_MAX))
	{
		print("dut0 pattern_rc_clock fail!\r\n\r\n");
		return -1;
	}

	dut0.g_pattern_timer = 0x5fff;
	dut0.g_ft2_pattern_num++;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);
	print("dut0 pattern_rc_clock pass!\r\n\r\n\r\n");

	return 0;
}
