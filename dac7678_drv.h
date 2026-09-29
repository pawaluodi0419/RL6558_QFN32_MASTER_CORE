#ifndef	DAC_7678_DRV_H_
#define DAC_7678_DRV_H_

#define	DAC_ADDR	0x48

#define	CC1_VOL_DAC_CH		0
#define	CC2_VOL_DAC_CH		1
#define	VMON_VOL_DAC_CH		2

void dac7678_set_voltage_mv(uint32_t i2c_fpga_baseaddr, uint8_t slave_addr, uint8_t ch_val, uint32_t vol_val);

#endif /* DAC7678_DRV_H_ */
