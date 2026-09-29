#include "platform.h"

int8_t pattern_setup_dut0()
{
	uint8_t tx_data;
	uint8_t tx_buf[10];
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

	for(uint8_t i=0;i<27;i++)
	{
		xil_printf("dut0 efuse_read_data[%02d]: %02x\r\n", i, rx_buf[i+1]);
	}
	print("\r\n");

	if(rx_buf[1] == 0)
	{
		print("dut0 is new IC!\r\n\r\n");
		dut0.g_ft2_retest = 0;
	}
	else
	{
		print("dut0 is retest IC!\r\n\r\n");
		dut0.g_ft2_retest = 1;
	}

	//reset TPC machine
	tx_data = 0x01;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x03, 0x11, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_data = 0x00;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x03, 0x11, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

//	/* confirm ADC configuration */
//	//0x1300 default: 0001 0110
//	ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x00, 0x13, 1, rx_buf, 0);
//	if(ret != 0x00)	return -1;
//	xil_printf("dut0 0x1300: 0x%x\r\n", rx_buf[1]);
//
//	//0x1301 default: 0000 0000
//	ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x01, 0x13, 1, rx_buf, 0);
//	if(ret != 0x00)	return -1;
//	xil_printf("dut0 0x1301: 0x%x\r\n", rx_buf[1]);
//
//	//0x1302 default: 0010 0100
//	ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x02, 0x13, 1, rx_buf, 0);
//	if(ret != 0x00)	return -1;
//	xil_printf("dut0 0x1302: 0x%x\r\n", rx_buf[1]);
//
//	//0x1303 default: 0000 0110
//	ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x03, 0x13, 1, rx_buf, 0);
//	if(ret != 0x00)	return -1;
//	xil_printf("dut0 0x1303: 0x%x\r\n", rx_buf[1]);
//
//	//0x108 default: 0000 0000 0000 0000
//	ret = smbus_xfer_packet(READ_PHY, DUT_ADDR, 0x08, 0x01, 1, rx_buf, 0);
//	if(ret != 0x00)	return -1;
//	xil_printf("dut0 0x108: 0x%x\r\n", (rx_buf[2] << 8) | rx_buf[1]);

	dut0.g_pattern_timer = 0x5fff;
	dut0.g_ft2_pattern_num++;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);
	print("dut0 pattern_setup pass!\r\n\r\n\r\n");

	return 0;
}
