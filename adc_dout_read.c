#include "platform.h"

uint16_t adc_dout_read(uint8_t adc_ch)
{
	uint8_t rx_buf[10];

	uint8_t adc_dout_low;
	uint8_t adc_dout_high;
	uint16_t adc_dout;

	int8_t ret;

	ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x50 | (adc_ch * 2), 0x13, 1, rx_buf, 0);
	if(ret != 0x00)	return -1;
	adc_dout_low = rx_buf[1];

	ret = smbus_xfer_packet(READ_MEM, DUT_ADDR, 0x50 | (adc_ch * 2 + 1), 0x13, 1, rx_buf, 0);
	if(ret != 0x00)	return -1;
	adc_dout_high = rx_buf[1];

	xil_printf("dut0 adc_dout_high = %x, adc_dout_low = %x\r\n", adc_dout_high, adc_dout_low);
	adc_dout = (adc_dout_high << 2) | (adc_dout_low & 0x03);

	return adc_dout;
}
