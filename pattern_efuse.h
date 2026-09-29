#ifndef	PATTERN_EFUSE_H_
#define	PATTERN_EFUSE_H_

#define	ADC_A_TOLERANCE		20
#define	ADC_B_TOLERANCE		10
#define	LDO3V3_TOLERANCE	2
#define	RP12K_TOLERANCE		2
#define	CCDET_TOLERANCE		3

#pragma pack(push, 1)

typedef union{
    uint8_t bytes[27];

    struct{
        //Byte 0
        uint8_t efuse_data_valid        : 1; //Bit 0
        uint8_t ldo_3v3_valid           : 1; //Bit 1
        uint8_t rp12k_valid             : 1; //Bit 2
        uint8_t cc_valid                : 1; //Bit 3
        uint8_t adc_valid               : 1; //Bit 4
        uint8_t mux_10g_calib_valid     : 1; //Bit 5
        uint8_t vconn_discharge_valid   : 1; //Bit 6
        uint8_t vconn_ocp_thres_valid 	: 1; //Bit 7

        //Byte 1
        uint8_t pwr_saving_mode_valid   : 1; //Bit 8
        uint8_t vbus_ocp_dbc_valid      : 1; //Bit 9
        uint8_t efuse_tpp_valid         : 1; //Bit 10
        uint8_t rc10us_timer_valid 		: 1; //Bit 11
        uint8_t reserved_12             : 1; //Bit 12
        uint8_t src_detach_opt_valid    : 1; //Bit 13
        uint8_t smbus_slave_addr_valid  : 1; //Bit 14
        uint8_t efuse_rw_test_result    : 1; //Bit 15

        //Byte 2
        uint8_t ldo_3v3                 : 2; //Bit 16-17
        uint8_t ra_discharge_threshold  : 1; //Bit 18
        uint8_t cp_test_bit             : 1; //Bit 19
        uint8_t soft_delink_enter_cnt   : 1; //Bit 20
        uint8_t src_detach_option       : 1; //Bit 21
        uint8_t reserved_22_23          : 2; //Bit 22-23

        //Byte 3
        uint8_t tpc_vcon_ocp_tm3        : 3; //Bit 24-26
        uint8_t tpc_mux_vbus_ctrl_order : 1; //Bit 27
        uint8_t soft_delink             : 1; //Bit 28
        uint8_t gpio0_output_func       : 1; //Bit 29
        uint8_t reserved_30_31          : 2; //Bit 30-31

        //Byte 4
        uint8_t rp_12k                  : 6; //Bit 32-37
        uint8_t reserved_38_39          : 2; //Bit 38-39

        //Byte 5
        uint8_t reserved_40          	: 1; //Bit 40
        uint8_t smbus_slave_addr   		: 7; //Bit 41-47

        //Byte 6~7
        uint16_t adc_a       			: 16;//Bit 48-63

        //Byte 8
        uint8_t adc_b       			: 8; //Bit 64-71

        //Byte 9~10
        uint16_t mux_10g_calib       	: 16;//Bit 72-87

        //Byte 11
        uint8_t vconn_ocp_threshold     : 5; //Bit 88-92
        uint8_t reserved_93_95          : 3; //Bit 93-95

        //Byte 12
        uint8_t vsafe0v_threshold       : 3; //Bit 96-98
        uint8_t reserved_99          	: 1; //Bit 99
        uint8_t vbus_on_threshold       : 3; //Bit 100-102
        uint8_t reserved_103          	: 1; //Bit 103

        //Byte 13
        uint8_t power_saving_mode       : 1; //Bit 104
        uint8_t reserved_105          	: 1; //Bit 105
        uint8_t default_tpc_current_lvl : 2; //Bit 106-107
        uint8_t unconditionally_src_vcon: 1; //Bit 108
        uint8_t reserved_109_111        : 3; //Bit 109-111

        //Byte 14
        uint8_t tcc_debounce            : 5; //Bit 112-116
        uint8_t reserved_117_119        : 3; //Bit 117-119

        //Byte 15
        uint8_t gpio_debounce_time      : 8; //Bit 120-127

        //Byte 16
        uint8_t attach_detach_debounce  : 4; //Bit 128-131
        uint8_t reg_txvcmmux_sel        : 1; //Bit 132
        uint8_t reg_tx_mux_en           : 1; //Bit 133
        uint8_t reg_rxvcmmux_sel        : 1; //Bit 134
        uint8_t reg_rx_mux_en           : 1; //Bit 135

        //Byte 17~18
        uint16_t reg_cc_vref_cfg0      	: 16;//Bit 136-151

        //Byte 19~20
        uint16_t reg_cc_vref_cfg1      	: 16;//Bit 152-167

        //Byte 21~22
        uint16_t reg_cc_vref_cfg2      	: 16;//Bit 168-183

        //Byte 23~24
        uint16_t reg_cc_vref_cfg3      	: 16;//Bit 184-199

        //Byte 25
        uint8_t efuse_tpp_l             : 8; //Bit 200-207

        //Byte 26
        uint8_t rc10us_timer_threshold	: 8; //Bit 208-215
    } bits;
}efuse_data_t;

#pragma pack(pop)

int8_t pattern_efuse_dut0();
int8_t pattern_efuse_check_dut0();

#endif /* PATTERN_EFUSE_H_ */
