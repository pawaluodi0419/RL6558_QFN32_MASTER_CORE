#ifndef AD7994_DRV_H_
#define AD7994_DRV_H_

#define	ADC_ADDR			0x21	//AS GND

#define	CC1_VOL_ADC_CH		1
#define	CC2_VOL_ADC_CH		2
#define	LDO3V3_VOL_ADC_CH	3

#define	AVG_NUM			10

uint16_t ad7994_readcvsdata(uint32_t i2c_fpga_baseaddr, uint8_t slave_addr, uint8_t ch_val, uint8_t avg_points);

#endif /* AD7994_DRV_H_ */
