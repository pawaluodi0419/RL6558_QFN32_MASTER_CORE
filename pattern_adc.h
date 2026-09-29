#ifndef	PATTERN_ADC_H_
#define	PATTERN_ADC_H_

#define ADC_1V_REF		1000
#define ADC_0P25V_REF	250

#define ADC_A_MAX		1300
#define ADC_A_MIN		1050

#define ADC_B_MAX		10
#define ADC_B_MIN		5

uint16_t adc_dout_read(uint8_t adc_ch);
int8_t pattern_adc_dut0();

#endif /* PATTERN_ADC_H_ */
