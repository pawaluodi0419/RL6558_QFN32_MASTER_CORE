#include "platform.h"

int8_t pattern_mux_reverse_test_dut0()
{
	uint8_t tx_data;
	uint8_t tx_buf[10];
	uint8_t rx_buf[10];

	uint16_t adc_dout_dct_tx1;
	uint16_t adc_dout_dct_rx1;

	uint16_t adc_dout_dct_tx2;
	uint16_t adc_dout_dct_rx2;

//	uint32_t adc_tx1_dct_vol1;
//	uint32_t adc_rx1_dct_vol1;

	uint32_t adc_tx2_dct_vol1;
	uint32_t adc_rx2_dct_vol1;

//	uint32_t adc_tx1_dct_vol2;
//	uint32_t adc_rx1_dct_vol2;

	uint32_t adc_tx2_dct_vol2;
	uint32_t adc_rx2_dct_vol2;

	uint32_t dsp1_err_cnt;
	uint32_t dsp3_err_cnt;

	int8_t ret;

	uint32_t timeout_cnt = 0;

	//ADC configuration
	tx_data = 0x17;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_data = 0x03;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x03, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_data = 0x15;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_data = 0x24;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x02, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_data = 0x15;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x01;
    tx_buf[1] = 0x00;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x08, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_data = 0x88;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x01, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	//enable DCT TX/RX
	tx_buf[0] = 0x03;
    tx_buf[1] = 0x00;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x05, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	//turn on 10G MUX(obverse)
	tx_buf[0] = 0x80;
    tx_buf[1] = 0x09;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x02, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x80;
    tx_buf[1] = 0x09;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x03, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x00;
    tx_buf[1] = 0x82;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x04, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	delay_ms(10);

	//read TX1 DCT output
	tx_data = 0x75;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(10);

	adc_dout_dct_tx1 = adc_dout_read(3);

	if(dut0.g_adc_b_signbit == 0)
	{
		g_adc_tx1_dct_vol1 = dut0.g_adc_a * adc_dout_dct_tx1 + dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	else
	{
		g_adc_tx1_dct_vol1 = dut0.g_adc_a * adc_dout_dct_tx1 - dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	xil_printf("dut0 g_adc_tx1_dct_vol1 = %d\r\n", g_adc_tx1_dct_vol1);

	if(g_adc_tx1_dct_vol1 < DCT_OUTPUT_VOL)
	{
		print("dut0 g_adc_tx1_dct_vol1 < spec!\r\n\r\n");
		return -1;
	}

	//read RX1 DCT output
	tx_data = 0x35;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(10);

	adc_dout_dct_rx1 = adc_dout_read(3);

	if(dut0.g_adc_b_signbit == 0)
	{
		g_adc_rx1_dct_vol1 = dut0.g_adc_a * adc_dout_dct_rx1 + dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	else
	{
		g_adc_rx1_dct_vol1 = dut0.g_adc_a * adc_dout_dct_rx1 - dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	xil_printf("dut0 g_adc_rx1_dct_vol1 = %d\r\n", g_adc_rx1_dct_vol1);

	if(g_adc_rx1_dct_vol1 < DCT_OUTPUT_VOL)
	{
		print("dut0 g_adc_rx1_dct_vol1 < spec!\r\n\r\n");
		return -1;
	}

	//turn on 10G MUX(reverse)
	tx_buf[0] = 0x25;
    tx_buf[1] = 0x00;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x02, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x25;
    tx_buf[1] = 0x00;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x03, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x00;
    tx_buf[1] = 0x41;
	ret = smbus_xfer_packet(WRITE_PHY, DUT_ADDR, 0x04, 0x01, 0, tx_buf, 2);
	if(ret != 0x00)	return -1;

	delay_ms(10);

	//read TX2 DCT output
	tx_data = 0x55;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(10);

	adc_dout_dct_tx2 = adc_dout_read(3);

	if(dut0.g_adc_b_signbit == 0)
	{
		adc_tx2_dct_vol1 = dut0.g_adc_a * adc_dout_dct_tx2 + dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	else
	{
		adc_tx2_dct_vol1 = dut0.g_adc_a * adc_dout_dct_tx2 - dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	xil_printf("dut0 adc_tx2_dct_vol1 = %d\r\n", adc_tx2_dct_vol1);

	if(adc_tx2_dct_vol1 < DCT_OUTPUT_VOL)
	{
		print("dut0 adc_tx2_dct_vol1 < spec!\r\n\r\n");
		return -1;
	}

	//read RX2 DCT output
	tx_data = 0x15;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(10);

	adc_dout_dct_rx2 = adc_dout_read(3);

	if(dut0.g_adc_b_signbit == 0)
	{
		adc_rx2_dct_vol1 = dut0.g_adc_a * adc_dout_dct_rx2 + dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	else
	{
		adc_rx2_dct_vol1 = dut0.g_adc_a * adc_dout_dct_rx2 - dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	xil_printf("dut0 adc_rx2_dct_vol1 = %d\r\n", adc_rx2_dct_vol1);

	if(adc_rx2_dct_vol1 < DCT_OUTPUT_VOL)
	{
		print("dut0 adc_rx2_dct_vol1 < spec!\r\n\r\n");
		return -1;
	}

	delay_ms(3000);

	//read TX2 DCT output
	tx_data = 0x55;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(10);

	adc_dout_dct_tx2 = adc_dout_read(3);

	if(dut0.g_adc_b_signbit == 0)
	{
		adc_tx2_dct_vol2 = dut0.g_adc_a * adc_dout_dct_tx2 + dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	else
	{
		adc_tx2_dct_vol2 = dut0.g_adc_a * adc_dout_dct_tx2 - dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	xil_printf("dut0 adc_tx2_dct_vol2 = %d\r\n", adc_tx2_dct_vol2);

	if(adc_tx2_dct_vol2 < DCT_OUTPUT_VOL)
	{
		print("dut0 adc_tx2_dct_vol2 < spec!\r\n\r\n");
		return -1;
	}

	//read RX2 DCT output
	tx_data = 0x15;
	ret = smbus_xfer_packet(WRITE_MEM, DUT_ADDR, 0x00, 0x13, 1, &tx_data, 1);
	if(ret != 0x00)	return -1;

	delay_ms(10);

	adc_dout_dct_rx2 = adc_dout_read(3);

	if(dut0.g_adc_b_signbit == 0)
	{
		adc_rx2_dct_vol2 = dut0.g_adc_a * adc_dout_dct_rx2 + dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	else
	{
		adc_rx2_dct_vol2 = dut0.g_adc_a * adc_dout_dct_rx2 - dut0.g_adc_b_offset * 1000;	//mV *1000
	}
	xil_printf("dut0 adc_rx2_dct_vol2 = %d\r\n", adc_rx2_dct_vol2);

	if(adc_rx2_dct_vol2 < DCT_OUTPUT_VOL)
	{
		print("dut0 adc_rx2_dct_vol2 < spec!\r\n\r\n");
		return -1;
	}

	if(abs((int)adc_tx2_dct_vol1 - (int)adc_tx2_dct_vol2) > DCT_OUTPUT_DIFF)
	{
		print("dut0 tx2 dct output diff > spec!\r\n\r\n");
		return -1;
	}

	if(abs((int)adc_rx2_dct_vol1 - (int)adc_rx2_dct_vol2) > DCT_OUTPUT_DIFF)
	{
		print("dut0 rx2 dct output diff > spec!\r\n\r\n");
		return -1;
	}

	// ********** DUT0(master core) <-> DUT1(slave core) ********** //
	while(1)
	{
		if((g_rec_sla_1_data == CMD_FT2_NOT_START) ||
		   (g_rec_sla_1_data == CMD_FT2_TEST_FAIL) ||
		   (g_rec_sla_1_data == CMD_REVERSE_PLUG_DONE))
		{
			timeout_cnt = 0;
			break;
		}

		timeout_cnt++;
		delay_ms(10);

		if(timeout_cnt >= 500)
		{
			xil_printf("\r\nError: Wait DUT1 timeout! g_rec_sla_1_data = 0x%x\r\n", g_rec_sla_1_data);
			return -1;
		}
	}

	// ********** DUT0(master core) <-> DUT1(slave core) ********** //
	if((g_rec_sla_1_data == CMD_FT2_NOT_START) || (g_rec_sla_1_data == CMD_FT2_TEST_FAIL))
	{
		print("hub1 run dsp3 slb!\r\n");

		hub_slb_dsp3_start();
		delay_ms(200);
		hub_slb_dsp3_stop();

		hub_slb_dsp3_read_err_cnt(&dsp3_err_cnt);
		hub_slb_dsp3_reset_err_cnt();

		xil_printf("hub1 dsp3_err_cnt = %d\r\n", dsp3_err_cnt);
	}
	else if(g_rec_sla_1_data == CMD_REVERSE_PLUG_DONE)
	{
		print("hub1 run dsp1&dsp3 slb!\r\n");

		hub_slb_dsp1_start();
		hub_slb_dsp3_start();
		delay_ms(200);
		hub_slb_dsp1_stop();
		hub_slb_dsp3_stop();

		hub_slb_dsp1_read_err_cnt(&dsp1_err_cnt);
		hub_slb_dsp3_read_err_cnt(&dsp3_err_cnt);

		xil_printf("hub1 dsp1_err_cnt = %d\r\n", dsp1_err_cnt);
		xil_printf("hub1 dsp3_err_cnt = %d\r\n", dsp3_err_cnt);

		//tell DUT1 error count
	    ret = master_core_write(DUT0_MAS_CORE_BASEADDR, 1, dsp1_err_cnt);
	    if(ret != 0x00)	return -1;
	    g_rec_sla_1_data = CMD_REVERSE_SLB_DONE;

	    hub_slb_dsp1_reset_err_cnt();
	    hub_slb_dsp3_reset_err_cnt();
	}

	if(dsp3_err_cnt > SLB_ERR_CNT)
	{
		print("hub1 dsp3 slb error count > spec!\r\n\r\n");
		return -1;
	}

	dut0.g_pattern_timer = 0x5fff;
	dut0.g_ft2_pattern_num++;
	result_output_for_v50(DUT0_GPIO_0_ADDR, dut0.g_ft2_pattern_num);
	print("dut0 pattern_mux_reverse_test pass!\r\n\r\n\r\n");

	return 0;
}
