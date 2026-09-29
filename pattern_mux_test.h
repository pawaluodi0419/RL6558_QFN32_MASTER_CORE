#ifndef	PATTERN_MUX_TEST_H_
#define	PATTERN_MUX_TEST_H_

#define	DCT_OUTPUT_VOL	900000
#define	DCT_OUTPUT_DIFF	200000

#define SLB_ERR_CNT		0

int8_t hub_slb_initial();

int8_t hub_slb_dsp1_start();
int8_t hub_slb_dsp1_stop();
int8_t hub_slb_dsp1_read_err_cnt(uint32_t *err_cnt);
int8_t hub_slb_dsp1_reset_err_cnt();

int8_t hub_slb_dsp2_start();
int8_t hub_slb_dsp2_stop();
int8_t hub_slb_dsp2_read_err_cnt(uint32_t *err_cnt);
int8_t hub_slb_dsp2_reset_err_cnt();

int8_t hub_slb_dsp3_start();
int8_t hub_slb_dsp3_stop();
int8_t hub_slb_dsp3_read_err_cnt(uint32_t *err_cnt);
int8_t hub_slb_dsp3_reset_err_cnt();

int8_t hub_slb_dsp4_start();
int8_t hub_slb_dsp4_stop();
int8_t hub_slb_dsp4_read_err_cnt(uint32_t *err_cnt);
int8_t hub_slb_dsp4_reset_err_cnt();

int8_t pattern_mux_reverse_test_dut0();
int8_t pattern_mux_obverse_test_dut0();

#endif /* PATTERN_MUX_TEST_H_ */
