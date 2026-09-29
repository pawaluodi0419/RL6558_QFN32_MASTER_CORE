#include "platform.h"

int8_t pattern_initial_state_dut0()
{
	uint8_t xgpio_data[8];

	xgpio_data[0] = 0x08;
	xgpio_data[1] = 0x40;
	xgpio_data[2] = 0x40;
	xgpio_data[3] = 0x80;
	xgpio_data[4] = 0xc0;	//bit22: 1(S0_LDO_3V3 on)
	xgpio_data[5] = 0x00;
	xgpio_data[6] = 0x00;
	xgpio_data[7] = 0x00;
	xgpio_write_word(DUT0_GPIO_0_ADDR, 0, xgpio_data);

	dut0.g_ft2_pattern_num = 0x1f;
	dut0.g_ft2_start_ready = 0;
	dut0.g_ft2_test_done = 1;
	dut0.g_result_fail = 0;
	dut0.g_pattern_timer = 0x5fff;
	dut0.g_axitmr_cnt0 = 0;
	dut0.g_axitmr_cnt1 = 0;
	dut0.g_test_cnt = 0;
	dut0.g_pass_cnt = 0;
	dut0.g_eqa_test_cnt = 0;
	dut0.g_eqa_pass_cnt = 0;
	dut0.g_gpio_shadow_state[0] = 0x00c04008;
	dut0.g_gpio_shadow_state[1] = 0;

	//FW version
	result_output_for_v50(DUT0_GPIO_0_ADDR, FT_FW_VER);

	GPI_DIS_WRITE_REG(DUT0_GPI_DIS_ADDR, 0 , 0x00008040);

    int8_t ret = master_core_write(DUT0_MAS_CORE_BASEADDR, 1, CMD_FT2_NOT_START);
    if(ret != 0x00)	return -1;

	return 0;
}
