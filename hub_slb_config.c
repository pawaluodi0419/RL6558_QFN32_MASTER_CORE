#include "platform.h"

int8_t hub_slb_initial()
{
	uint8_t tx_data;
	uint8_t tx_buf[10];
	int8_t ret;

    /* HUB SLB configuration */
	tx_buf[0] = 0x00;	//H
	tx_buf[1] = 0x00;	//L
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x30, 0x05, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_data = 0x21;
	ret = smbus_xfer_packet(WRITE_MEM, HUB_ADDR, 0x05, 0xE1, 1, &tx_data, 1);
	if(ret != 0x00)	return -2;
	ret = smbus_xfer_packet(WRITE_MEM, HUB_ADDR, 0x05, 0xE2, 1, &tx_data, 1);
	if(ret != 0x00)	return -2;
	ret = smbus_xfer_packet(WRITE_MEM, HUB_ADDR, 0x05, 0xE3, 1, &tx_data, 1);
	if(ret != 0x00)	return -2;
	ret = smbus_xfer_packet(WRITE_MEM, HUB_ADDR, 0x05, 0xE4, 1, &tx_data, 1);
	if(ret != 0x00)	return -2;

	tx_buf[0] = 0x21;
	tx_buf[1] = 0xE1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x0B, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -3;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x13, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -3;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x1B, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -3;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x23, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -3;

	tx_buf[0] = 0x23;
	tx_buf[1] = 0xE1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x0B, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -4;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x13, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -4;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x1B, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -4;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x23, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -4;

	tx_buf[0] = 0x33;
	tx_buf[1] = 0xE1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x0B, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -5;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x13, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -5;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x1B, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -5;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x23, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -5;

	tx_buf[0] = 0x12;
	tx_buf[1] = 0xE1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x0B, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -6;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x13, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -6;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x1B, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -6;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x23, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -6;

	tx_data = 0x00;
	ret = smbus_xfer_packet(WRITE_MEM, HUB_ADDR, 0x16, 0xFA, 1, &tx_data, 1);
	if(ret != 0x00)	return -7;
	ret = smbus_xfer_packet(WRITE_MEM, HUB_ADDR, 0x26, 0xFA, 1, &tx_data, 1);
	if(ret != 0x00)	return -7;
	ret = smbus_xfer_packet(WRITE_MEM, HUB_ADDR, 0x36, 0xFA, 1, &tx_data, 1);
	if(ret != 0x00)	return -7;
	ret = smbus_xfer_packet(WRITE_MEM, HUB_ADDR, 0x46, 0xFA, 1, &tx_data, 1);
	if(ret != 0x00)	return -7;

	tx_buf[0] = 0x41;
	tx_buf[1] = 0x2C;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x19, 0x01, 2, tx_buf, 2);
	if(ret != 0x00)	return -8;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x19, 0x02, 2, tx_buf, 2);
	if(ret != 0x00)	return -8;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x19, 0x03, 2, tx_buf, 2);
	if(ret != 0x00)	return -8;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x19, 0x04, 2, tx_buf, 2);
	if(ret != 0x00)	return -8;

	tx_buf[0] = 0x41;
	tx_buf[1] = 0xF4;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x99, 0x01, 2, tx_buf, 2);
	if(ret != 0x00)	return -9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x99, 0x02, 2, tx_buf, 2);
	if(ret != 0x00)	return -9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x99, 0x03, 2, tx_buf, 2);
	if(ret != 0x00)	return -9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x99, 0x04, 2, tx_buf, 2);
	if(ret != 0x00)	return -9;

	return 0;
}

int8_t hub_slb_dsp1_start()
{
	uint8_t tx_buf[10];
	int8_t ret;

	//start error count
	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x08, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x08, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x00;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x08, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp1_stop()
{
	uint8_t tx_buf[10];
	int8_t ret;

	//stop error count
	tx_buf[0] = 0x10;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x08, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x08, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x08, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp1_read_err_cnt(uint32_t *err_cnt)
{
	uint8_t rx_buf[10];
	int8_t ret;

	uint16_t err_cnt_low;
	uint16_t err_cnt_high;

	ret = smbus_xfer_packet(READ_PHY, HUB_ADDR, 0x0C, 0x06, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;
	err_cnt_high  = (rx_buf[1] << 8) | rx_buf[2];

	ret = smbus_xfer_packet(READ_PHY, HUB_ADDR, 0x0D, 0x06, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;
	err_cnt_low  = (rx_buf[1] << 8) | rx_buf[2];

	*err_cnt = (err_cnt_high << 16) | err_cnt_low;

	return 0;
}

int8_t hub_slb_dsp1_reset_err_cnt()
{
	uint8_t tx_buf[10];
	int8_t ret;

	tx_buf[0] = 0x18;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x08, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x08, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp2_start()
{
	uint8_t tx_buf[10];
	int8_t ret;

	//start error count
	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x10, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x10, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x00;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x10, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp2_stop()
{
	uint8_t tx_buf[10];
	int8_t ret;

	//stop error count
	tx_buf[0] = 0x10;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x10, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x10, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x10, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp2_read_err_cnt(uint32_t *err_cnt)
{
	uint8_t rx_buf[10];
	int8_t ret;

	uint16_t err_cnt_low;
	uint16_t err_cnt_high;

	ret = smbus_xfer_packet(READ_PHY, HUB_ADDR, 0x14, 0x06, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;
	err_cnt_high  = (rx_buf[1] << 8) | rx_buf[2];

	ret = smbus_xfer_packet(READ_PHY, HUB_ADDR, 0x15, 0x06, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;
	err_cnt_low  = (rx_buf[1] << 8) | rx_buf[2];

	*err_cnt = (err_cnt_high << 16) | err_cnt_low;

	return 0;
}

int8_t hub_slb_dsp2_reset_err_cnt()
{
	uint8_t tx_buf[10];
	int8_t ret;

	tx_buf[0] = 0x18;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x10, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x10, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp3_start()
{
	uint8_t tx_buf[10];
	int8_t ret;

	//start error count
	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x18, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x18, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x00;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x18, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp3_stop()
{
	uint8_t tx_buf[10];
	int8_t ret;

	//stop error count
	tx_buf[0] = 0x10;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x18, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x18, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x18, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp3_read_err_cnt(uint32_t *err_cnt)
{
	uint8_t rx_buf[10];
	int8_t ret;

	uint16_t err_cnt_low;
	uint16_t err_cnt_high;

	ret = smbus_xfer_packet(READ_PHY, HUB_ADDR, 0x1C, 0x06, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;
	err_cnt_high  = (rx_buf[1] << 8) | rx_buf[2];

	ret = smbus_xfer_packet(READ_PHY, HUB_ADDR, 0x1D, 0x06, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;
	err_cnt_low  = (rx_buf[1] << 8) | rx_buf[2];

	*err_cnt = (err_cnt_high << 16) | err_cnt_low;

	return 0;
}

int8_t hub_slb_dsp3_reset_err_cnt()
{
	uint8_t tx_buf[10];
	int8_t ret;

	tx_buf[0] = 0x18;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x18, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x18, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp4_start()
{
	uint8_t tx_buf[10];
	int8_t ret;

	//start error count
	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x20, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x20, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x00;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x20, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp4_stop()
{
	uint8_t tx_buf[10];
	int8_t ret;

	//stop error count
	tx_buf[0] = 0x10;
	tx_buf[1] = 0xAD;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x20, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA9;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x20, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x20, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}

int8_t hub_slb_dsp4_read_err_cnt(uint32_t *err_cnt)
{
	uint8_t rx_buf[10];
	int8_t ret;

	uint16_t err_cnt_low;
	uint16_t err_cnt_high;

	ret = smbus_xfer_packet(READ_PHY, HUB_ADDR, 0x24, 0x06, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;
	err_cnt_high  = (rx_buf[1] << 8) | rx_buf[2];

	ret = smbus_xfer_packet(READ_PHY, HUB_ADDR, 0x25, 0x06, 2, rx_buf, 0);
	if(ret != 0x00)	return -1;
	err_cnt_low  = (rx_buf[1] << 8) | rx_buf[2];

	*err_cnt = (err_cnt_high << 16) | err_cnt_low;

	return 0;
}

int8_t hub_slb_dsp4_reset_err_cnt()
{
	uint8_t tx_buf[10];
	int8_t ret;

	tx_buf[0] = 0x18;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x20, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	tx_buf[0] = 0x10;
	tx_buf[1] = 0xA1;
	ret = smbus_xfer_packet(WRITE_PHY, HUB_ADDR, 0x20, 0x06, 2, tx_buf, 2);
	if(ret != 0x00)	return -1;

	return 0;
}
