#ifndef	PATTERN_CCDET_H_
#define	PATTERN_CCDET_H_

#define VREF_MASK	0xF

typedef struct{
	uint16_t dac_data;
	uint8_t vref_sel;
	uint16_t vref_reg;
	uint8_t vref_shift;
	uint8_t check_bit;
}ccdet_calib_config_t;

extern const ccdet_calib_config_t cc1_config_table[7];
extern const ccdet_calib_config_t cc2_config_table[7];

int8_t ccdet_calib_dut0(const ccdet_calib_config_t *table, uint8_t table_size, uint8_t cc_id);
int8_t pattern_ccdet_dut0();

#endif /* PATTERN_CCDET_H_ */
