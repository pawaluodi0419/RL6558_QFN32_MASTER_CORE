/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include "platform.h"

void axi_tmr0_intrq_handle();
void xgpio_intrq_handle_dut0();
void axi_mas_core_intrq_handle();

DUT dut0;
uint8_t g_led_tg = 0;
uint8_t g_timer_flag = 0;
uint32_t g_rec_sla_1_data = 0;
uint32_t g_rec_sla_2_data = 0;
uint32_t g_rec_sla_3_data = 0;
uint32_t g_adc_tx1_dct_vol1 = 0;
uint32_t g_adc_rx1_dct_vol1 = 0;

int main()
{
    init_platform();

    print("FT2 start!\r\nFPGA Version:RTS5441E_FT_merge_first_release_2026070101\r\n");

	int8_t ret = pattern_initial_state_dut0();
    if(ret != 0x00)
    {
    	print("DUT0 run initial_state fail!\r\n");
    	return -1;
    }

    /* AXI GPIO configuration */
    //enable GPIO_0 global interrupt
    XGpio_WriteReg(DUT0_GPIO_0_ADDR, XGPIO_GIE_OFFSET, 0x80000000);
    //enable GPIO_0 channel 1 interrupt
    XGpio_WriteReg(DUT0_GPIO_0_ADDR, XGPIO_IER_OFFSET, XGPIO_IR_CH1_MASK);

    /* AXI timer configuration */
    //config TCSR0 as down counter, auto reload
    XTmrCtr_SetControlStatusReg(DUT0_TIMER_0_ADDR, 0, XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_DOWN_COUNT_MASK);
    //enable TCSR0 interrupt
    XTmrCtr_EnableIntr(DUT0_TIMER_0_ADDR, 0);
    //load TCSR0, 50,000,000 / 1000 - 2
    XTmrCtr_SetLoadReg(DUT0_TIMER_0_ADDR, 0, 49998);

    /* AXI master core configuration */
    //enable master core interrupt
    CORE2CORE_BRIDGE_WRITE_REG(DUT0_MAS_CORE_BASEADDR, 20, 0x07);

    //register GPIO_0 ISR
    XIntc_RegisterHandler(DUT0_INTC_ADDR,
                          XPAR_MB_DUT0_MICROBLAZE_0_AXI_INTC_MB_DUT0_AXI_GPIO_0_IP2INTC_IRPT_INTR,
                          (XInterruptHandler)xgpio_intrq_handle_dut0,
                          (void*)NULL);

    //register TCSR0 ISR
    XIntc_RegisterHandler(DUT0_INTC_ADDR,
                          XPAR_MB_DUT0_MICROBLAZE_0_AXI_INTC_MB_DUT0_AXI_TIMER_0_INTERRUPT_INTR,
                          (XInterruptHandler)axi_tmr0_intrq_handle,
                          (void*)NULL);

    //register master core ISR
    XIntc_RegisterHandler(DUT0_INTC_ADDR,
    					  XPAR_MB_DUT0_MICROBLAZE_0_AXI_INTC_MB_DUT0_CORE2CORE_BRIDGE_MAS_0_INTERRUPT_INTR,
                          (XInterruptHandler)axi_mas_core_intrq_handle,
                          (void*)NULL);

    //enable INTC
    XIntc_MasterEnable(DUT0_INTC_ADDR);
    //enable each interrupt in INTC
    XIntc_EnableIntr(DUT0_INTC_ADDR,
					 XPAR_MB_DUT0_AXI_GPIO_0_IP2INTC_IRPT_MASK |
					 XPAR_MB_DUT0_AXI_TIMER_0_INTERRUPT_MASK |
					 XPAR_MB_DUT0_CORE2CORE_BRIDGE_MAS_0_INTERRUPT_MASK);

    //start TCSR0 counting
    XTmrCtr_Enable(DUT0_TIMER_0_ADDR, 0);

    microblaze_enable_interrupts();

    ret = hub_slb_initial();
//    xgpio_write_bit(DUT0_GPIO_0_ADDR, 0, 22, 0);

    if(ret != 0x00)
    {
    	print("FPGA write HUB fail, don't enter FT2 test!\r\n\r\n");
		while(1);
    }
    else
    {
    	print("FPGA write HUB pass, wait for FT2 start!\r\n\r\n");
    }

	uint32_t dsp1_err_cnt;
	uint32_t dsp2_err_cnt;

	uint32_t timeout_cnt = 0;

    while(1)
    {
		if(dut0.g_ft2_start_ready == 0x11)
		{
			print("FT start signal start!\r\n\r\n");
			platform_initial();
		}

		if(dut0.g_ft2_start_ready == 1)
		{
			ret = 0;

			switch(dut0.g_ft2_pattern_num)
			{
				case 0x00:
				{
					if(xgpio_read_bit(DUT0_GPIO_0_ADDR, 0, 6) == 0)
					{
						ret = pattern_setup_dut0();
						break;
					}
					else
					{
						ret = pattern_efuse_check_dut0();
						break;
					}
				}
				case 0x01:
				{
					ret = pattern_rc_clock_dut0();
					break;
				}
				case 0x02:
				{
					ret = pattern_adc_dut0();
					break;
				}
				case 0x03:
				{
					ret = pattern_ldo3v3_dut0();
					break;
				}
				case 0x04:
				{
					ret = pattern_rp12k_dut0();
					break;
				}
				case 0x05:
				{
					ret = pattern_ccdet_dut0();
					break;
				}
				case 0x06:
				{
					ret = pattern_efuse_dut0();
					break;
				}
				case 0x07:
				{
					ret = pattern_mux_reverse_test_dut0();
					break;
				}
				case 0x08:
				{
					ret = pattern_mux_obverse_test_dut0();
					break;
				}
				default:
					break;
			}

			if(ret != 0x00)
			{
				xil_printf("dut0 ft2 pattern number = %x\r\n\r\n", dut0.g_ft2_pattern_num);
				dut0.g_result_fail = 1;

				ret = pattern_safe_state_dut0();
			    if(ret != 0x00)
			    {
			    	print("DUT0 run safe_state fail!\r\n");
			    	return -1;
			    }
			}
		}

		if((dut0.g_ft2_test_done == 1) || (dut0.g_ft2_start_ready == 0))
		{
			if(g_timer_flag)
			{
				xil_printf("FT2 test time: %d.%03d s\r\n\r\n", dut0.g_axitmr_cnt1 / 1000, dut0.g_axitmr_cnt1 % 1000);
				dut0.g_axitmr_cnt1 = 0;

				g_timer_flag = 0;
			}
		}

		if((dut0.g_result_fail == 1) || (dut0.g_ft2_start_ready == 0))
		{
			// ********** DUT0(master core) <-> DUT1(slave core) ********** //
			while(1)
			{
				if((g_rec_sla_1_data == CMD_FT2_NOT_START) ||
				   (g_rec_sla_1_data == CMD_FT2_TEST_FAIL) ||
				   (g_rec_sla_1_data == CMD_REVERSE_PLUG_DONE) ||
				   (g_rec_sla_1_data == CMD_OBVERSE_PLUG_DONE))
				{
					timeout_cnt = 0;
					break;
				}

				timeout_cnt++;
				delay_ms(10);

				if(timeout_cnt >= 500)
				{
					xil_printf("Error: Wait DUT1 timeout! g_rec_sla_1_data = 0x%x\r\n", g_rec_sla_1_data);

					timeout_cnt = 0;
					break;
				}
			}

			// ********** DUT0(master core) <-> DUT1(slave core) ********** //
			if(g_rec_sla_1_data == CMD_REVERSE_PLUG_DONE)
			{
				print("hub1 run dsp1 slb!\r\n");

				hub_slb_dsp1_start();
				delay_ms(200);
				hub_slb_dsp1_stop();

				hub_slb_dsp1_read_err_cnt(&dsp1_err_cnt);
			    hub_slb_dsp1_reset_err_cnt();

				xil_printf("hub1 dsp1_err_cnt = %d\r\n", dsp1_err_cnt);

				//tell DUT1 error count
			    master_core_write(DUT0_MAS_CORE_BASEADDR, 1, dsp1_err_cnt);
			    g_rec_sla_1_data = CMD_REVERSE_SLB_DONE;
			}
			else if(g_rec_sla_1_data == CMD_OBVERSE_PLUG_DONE)
			{
				print("hub1 run dsp2 slb!\r\n");

				hub_slb_dsp2_start();
				delay_ms(200);
				hub_slb_dsp2_stop();

				hub_slb_dsp2_read_err_cnt(&dsp2_err_cnt);
			    hub_slb_dsp2_reset_err_cnt();

				xil_printf("hub1 dsp2_err_cnt = %d\r\n", dsp2_err_cnt);

				//tell DUT1 error count
			    master_core_write(DUT0_MAS_CORE_BASEADDR, 1, dsp2_err_cnt);
			    g_rec_sla_1_data = CMD_OBVERSE_SLB_DONE;
			}
		}
    }

    cleanup_platform();

    return 0;
}
