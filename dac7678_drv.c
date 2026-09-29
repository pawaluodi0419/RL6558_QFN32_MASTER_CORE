#include "platform.h"

void dac7678_set_voltage_mv(uint32_t i2c_fpga_baseaddr, uint8_t slave_addr, uint8_t ch_val, uint32_t vol_val)
{
	uint8_t writedata_buf[3];
	uint32_t vol_val_temp;

	writedata_buf[0] = (0x00 | ch_val);							//CA Byte

	vol_val_temp = ((vol_val * 4096) / 3300);
	writedata_buf[1] = (uint8_t)(vol_val_temp >> 4);			//MSDB
	writedata_buf[2] = (uint8_t)((vol_val_temp & 0x0F) << 4);	//LSDB

	XIic_DynInit(i2c_fpga_baseaddr);
	delay_us(10);
	XIic_Send(i2c_fpga_baseaddr, slave_addr, writedata_buf, 3, XIIC_STOP);
	delay_us(10);
}
