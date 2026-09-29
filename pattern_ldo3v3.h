#ifndef	PATTERN_LDO3V3_H_
#define	PATTERN_LDO3V3_H_

#define LDO3V3_REF	(uint16_t)((3300.0 / 3300.0 * 4095.0) / 2.0)
#define LDO3V3_MAX	(uint16_t)((3450.0 / 3300.0 * 4095.0) / 2.0)
#define LDO3V3_MIN	(uint16_t)((3150.0 / 3300.0 * 4095.0) / 2.0)

int8_t pattern_ldo3v3_dut0();

#endif /* PATTERN_LDO3V3_H_ */
