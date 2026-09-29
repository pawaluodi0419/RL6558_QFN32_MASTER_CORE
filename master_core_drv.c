#include "platform.h"

int8_t master_core_write(uint32_t core_baseaddr, uint32_t core_index, uint32_t write_data)
{
	//core_index: 1 -> bit 0, offset 0
	//core_index: 2 -> bit 1, offset 4
	//core_index: 3 -> bit 2, offset 8
	uint32_t bit_shift = core_index - 1;
	uint32_t data_offset = (core_index - 1) * 4;

	uint32_t timeout_cnt = 0;
	//read slave core status
	while(!((CORE2CORE_BRIDGE_READ_REG(core_baseaddr, 16) >> bit_shift) & 0x01))
	{
		timeout_cnt++;
		if(timeout_cnt >= TIMEOUT_MAX_COUNT)
		{
			return -1;
		}
	}
	//write to slave core
	CORE2CORE_BRIDGE_WRITE_REG(core_baseaddr, data_offset, write_data);

	return 0;
}

int8_t master_core_read(uint32_t core_baseaddr, uint32_t core_index, uint32_t *read_data)
{
    //core_index: 1 -> bit 0, offset 0
    //core_index: 2 -> bit 1, offset 4
    //core_index: 3 -> bit 2, offset 8
    uint32_t bit_shift = core_index - 1;
    uint32_t data_offset = (core_index - 1) * 4;

    uint32_t timeout_cnt = 0;
    //read slave core write done flag
    while(!((CORE2CORE_BRIDGE_READ_REG(core_baseaddr, 24) >> bit_shift) & 0x01))
    {
        timeout_cnt++;
        if(timeout_cnt >= TIMEOUT_MAX_COUNT)
        {
            return -1;
        }
    }
    //read slave core write data
    *read_data = CORE2CORE_BRIDGE_READ_REG(core_baseaddr, data_offset);

    //clear slave core write done flag
    CORE2CORE_BRIDGE_WRITE_REG(core_baseaddr, 24, (1 << bit_shift));

    return 0;
}
