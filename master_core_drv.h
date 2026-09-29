#ifndef	MASTER_CORE_DRV_H_
#define	MASTER_CORE_DRV_H_

#define	DUT0_MAS_CORE_BASEADDR	XPAR_MB_DUT0_CORE2CORE_BRIDGE_MAS_0_S00_AXI_BASEADDR

#define CORE2CORE_BRIDGE_WRITE_REG(base_addr, reg_offset, data) \
	Xil_Out32((base_addr) + (reg_offset), (uint32_t)(data))

#define CORE2CORE_BRIDGE_READ_REG(base_addr, reg_offset) \
	Xil_In32((base_addr) + (reg_offset))

#define	TIMEOUT_MAX_COUNT		1000000

#define	CMD_FT2_NOT_START		0xA5A50000
#define	CMD_FT2_TEST_FAIL		0xA5A50001
#define	CMD_FT2_TEST_ING		0xA5A50002
#define	CMD_FT2_TEST_PASS    	0xA5A50003
#define	CMD_REVERSE_PLUG_DONE	0xA5A50004
#define	CMD_REVERSE_SLB_DONE    0xA5A50005
#define	CMD_OBVERSE_PLUG_DONE   0xA5A50006
#define	CMD_OBVERSE_SLB_DONE    0xA5A50007

int8_t master_core_write(uint32_t core_baseaddr, uint32_t core_index, uint32_t write_data);
int8_t master_core_read(uint32_t core_baseaddr, uint32_t core_index, uint32_t *read_data);

#endif /* MASTER_CORE_DRV_H_ */
