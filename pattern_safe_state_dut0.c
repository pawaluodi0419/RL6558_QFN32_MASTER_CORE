#include "platform.h"

int8_t pattern_safe_state_dut0()
{
//	uint8_t xgpio_data[8];
//
//	xgpio_data[0] = 0x08;
//	xgpio_data[1] = 0x40;
//	xgpio_data[2] = 0x40;
//	xgpio_data[3] = 0x80;
//	xgpio_data[4] = 0x40|dut0.g_ft2_pattern_num;
//	xgpio_data[5] = 0x00;
//	xgpio_data[6] = 0x00;
//	xgpio_data[7] = 0x00;
//	xgpio_write_word(DUT0_GPIO_0_ADDR, 0, xgpio_data);

	dac7678_set_voltage_mv(DUT0_IIC_ADDR, DAC_ADDR, CC1_VOL_DAC_CH, 0);
	dac7678_set_voltage_mv(DUT0_IIC_ADDR, DAC_ADDR, CC2_VOL_DAC_CH, 0);
	dac7678_set_voltage_mv(DUT0_IIC_ADDR, DAC_ADDR, VMON_VOL_DAC_CH, 0);

	dut0.g_gpio_shadow_state[0] = 0x00404008 | (dut0.g_ft2_pattern_num << 16);

	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 23, 1);
	delay_ms(1000);

	//write EOT high
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 1, 1);

	dut0.g_ft2_start_ready = 0;
	dut0.g_ft2_test_done = 1;
	dut0.g_pattern_timer = 0x5fff;

	g_timer_flag = 1;
	g_adc_tx1_dct_vol1 = 0;
	g_adc_rx1_dct_vol1 = 0;

	for(uint8_t i=32;i<=40;i=i+4)
	{
		xil_printf("dut0_pattern_code_capture_reg[%02d] = 0x%x\r\n", i, INF_CHECK_READ_REG(DUT0_INF_CHECK_ADDR, i));
	}

	xil_printf("dut0_alarm_reg = 0x%x\r\n", INF_CHECK_READ_REG(DUT0_INF_CHECK_ADDR, 64));

	for(uint8_t i=0;i<=10;i++)
	{
		INF_CHECK_WRITE_REG(DUT0_INF_CHECK_ADDR, 72, i);
		xil_printf("dut0_pattern_counter_reg[%02d] = %d\r\n", i, INF_CHECK_READ_REG(DUT0_INF_CHECK_ADDR, 76));
	}

	xil_printf("dut0_end_counter_reg = %d\r\n\r\n", INF_CHECK_READ_REG(DUT0_INF_CHECK_ADDR, 80));

	return 0;
}
