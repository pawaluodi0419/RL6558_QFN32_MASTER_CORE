/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

#ifndef __PLATFORM_H_
#define __PLATFORM_H_

#ifndef SDT
#include "platform_config.h"
#include "xparameters.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "xil_printf.h"

#include "xgpio.h"
#include "xgpio_l.h"
#include "xiic_l.h"
#include "xintc_l.h"
#include "xtmrctr.h"
#include "xtmrctr_l.h"
#include "xuartlite_l.h"
#include "mb_interface.h"

#include "gpio_drv.h"
#include "smbus_drv.h"
#include "timer_drv.h"
#include "master_core_drv.h"
#include "ad7994_drv.h"
#include "dac7678_drv.h"
#include "pattern_setup.h"
#include "pattern_rc_clock.h"
#include "pattern_adc.h"
#include "pattern_ldo3v3.h"
#include "pattern_rp12k.h"
#include "pattern_ccdet.h"
#include "pattern_efuse.h"
#include "pattern_mux_test.h"

#define	RESET_VECTOR_ADDRESS	0x00000000

typedef void (*reset_function_t)();

#define	DUT0_GPIO_0_ADDR	XPAR_MB_DUT0_AXI_GPIO_0_BASEADDR
#define	DUT0_GPI_DIS_ADDR 	XPAR_MB_DUT0_GPI_DIS_0_S00_AXI_BASEADDR
#define	DUT0_IIC_ADDR		XPAR_MB_DUT0_AXI_IIC_0_BASEADDR
#define	DUT0_SMBUS_ADDR		XPAR_MB_DUT0_AXI_IIC_1_BASEADDR
#define	DUT0_INTC_ADDR		XPAR_MB_DUT0_MICROBLAZE_0_AXI_INTC_BASEADDR
#define	DUT0_TIMER_0_ADDR	XPAR_MB_DUT0_AXI_TIMER_0_BASEADDR
#define	DUT0_INF_CHECK_ADDR	XPAR_MB_DUT0_V50_INTERFACE_CHECK_0_S00_AXI_BASEADDR

#define INF_CHECK_WRITE_REG(base_addr, reg_offset, data) \
	Xil_Out32((base_addr) + (reg_offset), (uint32_t)(data))

#define INF_CHECK_READ_REG(base_addr, reg_offset) \
	Xil_In32((base_addr) + (reg_offset))

#define GPI_DIS_WRITE_REG(base_addr, reg_offset, data) \
	Xil_Out32((base_addr) + (reg_offset), (uint32_t)(data))

#define GPI_DIS_READ_REG(base_addr, reg_offset) \
	Xil_In32((base_addr) + (reg_offset))

#define	FT_FW_VER	5

typedef struct{
	uint8_t g_ft2_pattern_num;
	uint8_t g_ft2_start_ready;
	uint8_t g_ft2_test_done;
	uint8_t g_ft2_retest;
	int8_t g_result_fail;
	uint32_t g_pattern_timer;
	uint32_t g_axitmr_cnt0;
	uint32_t g_axitmr_cnt1;
	uint32_t g_test_cnt;
	uint32_t g_pass_cnt;
	uint32_t g_eqa_test_cnt;
	uint32_t g_eqa_pass_cnt;
	uint32_t g_gpio_shadow_state[2];

	uint16_t g_freq_cnt;
	uint16_t g_adc_a;
	uint8_t g_adc_b_signbit;
	uint8_t g_adc_b_offset;
	uint8_t g_ldo3v3_offset;
	uint8_t g_rp12k_signbit;
	uint8_t g_rp12k_offset;
//	uint8_t g_rd_signbit;
//	uint8_t g_rd_offset;
}DUT;

extern DUT dut0;
extern uint8_t g_led_tg;
extern uint8_t g_timer_flag;
extern uint32_t g_rec_sla_1_data;
extern uint32_t g_rec_sla_2_data ;
extern uint32_t g_rec_sla_3_data;
extern uint32_t g_adc_tx1_dct_vol1;
extern uint32_t g_adc_rx1_dct_vol1;

int8_t pattern_initial_state_dut0();
int8_t pattern_safe_state_dut0();

void platform_initial();
void microblaze_softreset();

void init_platform();
void cleanup_platform();

#endif
