#include "platform.h"

//use mode 2(command mode, don't need to toggle CONVST pin)
uint16_t ad7994_readcvsdata(uint32_t i2c_fpga_baseaddr, uint8_t slave_addr, uint8_t ch_val, uint8_t avg_points)
{
	uint8_t writedata_buf[5] = {0};
	uint8_t readdata_buf[5] = {0};
	uint32_t adc_cvsdata_sum = 0;

	writedata_buf[0] = 1 << (ch_val + 3);	//Address Pointer Byte

	XIic_DynInit(i2c_fpga_baseaddr);
	delay_us(10);
	//read and discard the first conversion data
	XIic_Send(i2c_fpga_baseaddr, slave_addr, writedata_buf, 1, XIIC_REPEATED_START);
	delay_us(10);
	XIic_Recv(i2c_fpga_baseaddr, slave_addr, readdata_buf, 2, XIIC_STOP);

	for(uint8_t i=0;i<avg_points;i++)
	{
		XIic_Send(i2c_fpga_baseaddr, slave_addr, writedata_buf, 1, XIIC_REPEATED_START);
		delay_us(10);
		XIic_Recv(i2c_fpga_baseaddr, slave_addr, readdata_buf, 2, XIIC_STOP);
//		xil_printf("readdata_buf[0] =%x, readdata_buf[1] =%x\r\n", readdata_buf[0], readdata_buf[1]);

		adc_cvsdata_sum += (((readdata_buf[0] & 0x0F) << 8) | readdata_buf[1]);
	}

	return (uint16_t)(adc_cvsdata_sum / avg_points);
}
