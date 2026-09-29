#include "platform.h"

int8_t pattern_adc_dut0()
{
//	uint8_t tx_data;
//	uint8_t tx_buf[10];
//	uint8_t rx_buf[10];

	uint16_t adc_dout_0v;
	uint16_t adc_dout_1v;
	uint16_t adc_dout_0p25v;

//	uint32_t adc_fs_vol;

//	int8_t ret;

	//relay control
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 13, 0);
	delay_ms(50);

	adc_dout_0v = adc_dout_read(0);

	if(adc_dout_0v > 8)	return -1;

	//relay control
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 2, 1);
	delay_ms(50);

	//DAC output 1V
	dac7678_set_voltage_mv(DUT0_IIC_ADDR, DAC_ADDR, VMON_VOL_DAC_CH, 1000);
	delay_ms(10);

	adc_dout_1v = adc_dout_read(0);

	//DAC output 0.25V
	dac7678_set_voltage_mv(DUT0_IIC_ADDR, DAC_ADDR, VMON_VOL_DAC_CH, 250);
	delay_ms(10);

	adc_dout_0p25v = adc_dout_read(0);

	if(adc_dout_1v <= adc_dout_0p25v)	return -1;

	//calculate a/b
	uint32_t adc_ratiob_temp0 = ADC_0P25V_REF * adc_dout_1v;
	uint32_t adc_ratiob_temp1 = ADC_1V_REF * adc_dout_0p25v;

	dut0.g_adc_a = (ADC_1V_REF - ADC_0P25V_REF) * 1000 / (adc_dout_1v - adc_dout_0p25v);	//a * 1000
	xil_printf("dut0 adc_a = %x\r\n", dut0.g_adc_a);

	if((dut0.g_adc_a < ADC_A_MIN) || (dut0.g_adc_a > ADC_A_MAX))
	{
		print("dut0 adc_a out of range!\r\n\r\n");
		return -1;
	}

	if(adc_ratiob_temp0 >= adc_ratiob_temp1)
	{
		dut0.g_adc_b_offset = (adc_ratiob_temp0 - adc_ratiob_temp1) / (adc_dout_1v - adc_dout_0p25v);
		dut0.g_adc_b_signbit = 0;	//b: +
	}
	else
	{
		dut0.g_adc_b_offset = (adc_ratiob_temp1 - adc_ratiob_temp0) / (adc_dout_1v - adc_dout_0p25v);
		dut0.g_adc_b_signbit = 1;	//b: -
	}
	xil_printf("dut0 adc_b_signbit = %x, adc_b_offset = %x\r\n", dut0.g_adc_b_signbit, dut0.g_adc_b_offset);

	if((dut0.g_adc_b_signbit == 0) && (dut0.g_adc_b_offset > ADC_B_MAX))
	{
		print("dut0 adc_b out of range!\r\n");
		return -1;
	}

	if((dut0.g_adc_b_signbit == 1) && (dut0.g_adc_b_offset > ADC_B_MIN))
	{
		print("dut0 adc_b out of range!\r\n");
		return -1;
	}

	dut0.g_pattern_timer = 0x5fff;
	dut0.g_ft2_pattern_num++;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);
	print("dut0 pattern_adc pass!\r\n\r\n\r\n");

	return 0;
}
