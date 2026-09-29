#ifndef	PATTERN_RP12K_H_
#define	PATTERN_RP12K_H_

#define VCON_SW_OFF_VOL	(uint16_t)((100.0 / 3300.0 * 4095.0) / 2.0)
#define VCON_SW_ON_VOL	(uint16_t)((4500.0 / 3300.0 * 4095.0) / 2.0)

int8_t pattern_rp12k_dut0();

#endif /* PATTERN_RP12K_H_ */
