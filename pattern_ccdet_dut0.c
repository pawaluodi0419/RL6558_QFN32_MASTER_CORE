#include "platform.h"

int8_t pattern_ccdet_dut0()
{
	int8_t ret;

	const ccdet_calib_config_t cc1_config_table[] = {
			{200, 0x55, 0x10F, 12 , 2},
			{400, 0xaa, 0x10F, 4 , 3},
			{660, 0x00, 0x110, 12 , 3},
			{800, 0xFF, 0x110, 4 , 3},
			{1230, 0x00, 0x111, 12 , 4},
			{1600, 0xAA, 0x111, 4 , 4},
			{2600, 0xFF, 0x112, 4 , 4},
	};

	const ccdet_calib_config_t cc2_config_table[] = {
			{200, 0x55, 0x10F, 8 , 5},
			{400, 0xaa, 0x10F, 0 , 6},
			{660, 0x00, 0x110, 8 , 6},
			{800, 0xFF, 0x110, 0 , 6},
			{1230, 0x00, 0x111, 8 , 7},
			{1600, 0xAA, 0x111, 0 , 7},
			{2600, 0xFF, 0x112, 0 , 7},
	};

	//relay control
	xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 3, 0);
	delay_ms(50);

	ret = ccdet_calib_dut0(cc1_config_table, 7, 1);
	if(ret != 0x00)
	{
		print("dut0 pattern_ccdet cc1 fail!\r\n\r\n");
		return -1;
	}

	ret = ccdet_calib_dut0(cc2_config_table, 7, 2);
	if(ret != 0x00)
	{
		print("dut0 pattern_ccdet cc2 fail!\r\n\r\n");
		return -1;
	}

	dut0.g_pattern_timer = 0x5fff;
	dut0.g_ft2_pattern_num++;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);
	print("dut0 pattern_ccdet pass!\r\n\r\n\r\n");

	return 0;
}
