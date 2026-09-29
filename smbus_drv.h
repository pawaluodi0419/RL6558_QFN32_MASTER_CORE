#ifndef	SMBUS_DRV_H_
#define	SMBUS_DRV_H_

#define	SMBUS_SECOND_READCMD	0x80
#define SMBUS_MAX_BUF_SIZE		64

#define DUT_ADDR	0x62
#define HUB_ADDR	0x6A

#define VDCMD_ENABLE    0x01
#define RESET_TO_ROM    0x02
#define ERASE_FLASH     0x03
#define WRITE_FLASH     0x04
#define RESET_TO_FLASH	0x05
#define WRITE_MEM       0x18
#define WRITE_EFUSE     0x19
#define WRITE_PHY       0x1B

#define GET_FLASH_ID    0x01
#define READ_FLASH      0x24
#define READ_MEM        0x38
#define READ_EFUSE      0x39
#define GET_IC_STATUS   0x3A
#define READ_PHY        0x3B

typedef struct{
    uint8_t control_buf[SMBUS_MAX_BUF_SIZE];
    uint8_t writedata_count;
    uint8_t writecmd_count;
    uint8_t writecmd_buf[SMBUS_MAX_BUF_SIZE];
    uint8_t readdata_count;
    uint8_t readdata_buf[SMBUS_MAX_BUF_SIZE];
}smbus_xfer_pack_t;

int8_t smbus_get_pinstatus(uint8_t slave_addr);
int8_t smbus_xfer_core(smbus_xfer_pack_t *xfer_pack, uint8_t slave_addr);
int8_t smbus_xfer_packet(uint8_t cmd_type, uint8_t slave_addr, uint8_t param1, uint8_t param2, uint8_t param3, uint8_t *pdata, uint8_t data_len);

#endif /* SMBUS_DRV_H_ */
