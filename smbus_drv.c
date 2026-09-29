#include "platform.h"

int8_t smbus_xfer_core(smbus_xfer_pack_t *xfer_pack, uint8_t slave_addr)
{
	uint8_t i;
	uint8_t pinstatus;
	uint8_t smbus_cmd_type;
	uint8_t smbus_cmd_type_add;

	uint8_t smbus_second_readcmd = SMBUS_SECOND_READCMD;

	if(xfer_pack == NULL)	return -1;

	smbus_cmd_type = xfer_pack->control_buf[1];
	smbus_cmd_type_add = xfer_pack->control_buf[2];

	if(((smbus_cmd_type & 0xf0) == 0x10) || (smbus_cmd_type == 0x02) || (smbus_cmd_type == 0x03) || (smbus_cmd_type == 0x04)
			|| (smbus_cmd_type == 0x05) || ((smbus_cmd_type == 0x01) && (smbus_cmd_type_add == 0xda)))
	{
		switch(smbus_cmd_type)
		{
			case WRITE_MEM:
			case WRITE_EFUSE:
			case WRITE_FLASH:
			{
				xfer_pack->writecmd_count = xfer_pack->writedata_count + 5;
				xfer_pack->writecmd_buf[0] = xfer_pack->control_buf[1];
				xfer_pack->writecmd_buf[1] = xfer_pack->writedata_count + 3;
				xfer_pack->writecmd_buf[2] = xfer_pack->control_buf[2];
				xfer_pack->writecmd_buf[3] = xfer_pack->control_buf[3];
				xfer_pack->writecmd_buf[4] = xfer_pack->control_buf[4];

				for(i=0;i<xfer_pack->writedata_count;i++)
				{
					xfer_pack->writecmd_buf[i+5] = xfer_pack->control_buf[i+5];
				}
				break;
			}

			case WRITE_PHY:
			{
				if(xfer_pack->control_buf[4] == 0)
				{
					xfer_pack->writecmd_count = xfer_pack->writedata_count + 4;
					xfer_pack->writecmd_buf[0] = xfer_pack->control_buf[1];
					xfer_pack->writecmd_buf[1] = xfer_pack->writedata_count + 2;
					xfer_pack->writecmd_buf[2] = xfer_pack->control_buf[2];
					xfer_pack->writecmd_buf[3] = xfer_pack->control_buf[3];

					for(i=0;i<(xfer_pack->writedata_count);i++)
					{
						xfer_pack->writecmd_buf[i+4] = xfer_pack->control_buf[i+5];
					}
					break;
				}
				else if(xfer_pack->control_buf[4] == 2)
				{
					xfer_pack->writecmd_count = xfer_pack->writedata_count + 5;
					xfer_pack->writecmd_buf[0] = xfer_pack->control_buf[1];
					xfer_pack->writecmd_buf[1] = xfer_pack->writedata_count + 3;
					xfer_pack->writecmd_buf[2] = xfer_pack->control_buf[2];
					xfer_pack->writecmd_buf[3] = xfer_pack->control_buf[3];
					xfer_pack->writecmd_buf[4] = xfer_pack->control_buf[4];

					for(i=0;i<xfer_pack->writedata_count;i++)
					{
						xfer_pack->writecmd_buf[i+5] = xfer_pack->control_buf[i+5];
					}
					break;
				}
				else
				{
					return -1;
				}
			}

			case VDCMD_ENABLE:
			case RESET_TO_ROM:
			case ERASE_FLASH:
			case RESET_TO_FLASH:
			{
				xfer_pack->writecmd_count = 5;
				xfer_pack->writecmd_buf[0] = xfer_pack->control_buf[1];
				xfer_pack->writecmd_buf[1] = 0x03;
				xfer_pack->writecmd_buf[2] = xfer_pack->control_buf[2];
				xfer_pack->writecmd_buf[3] = xfer_pack->control_buf[3];
				xfer_pack->writecmd_buf[4] = xfer_pack->control_buf[4];

				break;
			}

			default:
				return -1;
		}

		XIic_DynInit(DUT0_SMBUS_ADDR);
		delay_us(10);
		XIic_Send(DUT0_SMBUS_ADDR, slave_addr, xfer_pack->writecmd_buf, xfer_pack->writecmd_count, XIIC_STOP);
		delay_us(10);

		for(i=0;i<100;i++)
		{
			pinstatus = smbus_get_pinstatus(slave_addr);

			if(pinstatus)
			{
				return 0;
			}
			delay_ms(1);
		}

		return -1;
	}

	if(((smbus_cmd_type & 0xf0) == 0x30) || (smbus_cmd_type == 0x24) || ((smbus_cmd_type == 0x01) && (smbus_cmd_type_add == 0x04)))
	{
		xfer_pack->writecmd_count = 5;
		xfer_pack->writecmd_buf[0] = xfer_pack->control_buf[1];
		xfer_pack->writecmd_buf[1] = 0x03;
		xfer_pack->writecmd_buf[2] = xfer_pack->control_buf[2];
		xfer_pack->writecmd_buf[3] = xfer_pack->control_buf[3];
		xfer_pack->writecmd_buf[4] = xfer_pack->control_buf[4];

		XIic_DynInit(DUT0_SMBUS_ADDR);
		delay_us(10);
		XIic_Send(DUT0_SMBUS_ADDR, slave_addr, xfer_pack->writecmd_buf, xfer_pack->writecmd_count, XIIC_STOP);
		delay_us(10);

		for(i=0;i<100;i++)
		{
			pinstatus = smbus_get_pinstatus(slave_addr);

			if(pinstatus)
			{
				xfer_pack->readdata_count = xfer_pack->control_buf[4];

				XIic_DynInit(DUT0_SMBUS_ADDR);
				delay_us(10);
				XIic_Send(DUT0_SMBUS_ADDR, slave_addr, &smbus_second_readcmd, 1, XIIC_REPEATED_START);
				delay_us(10);

				XIic_DynInit(DUT0_SMBUS_ADDR);
			    delay_us(10);
				XIic_Recv(DUT0_SMBUS_ADDR, slave_addr, xfer_pack->readdata_buf, xfer_pack->readdata_count + 1, XIIC_STOP);

				return 0;
			}
			delay_ms(1);
		}

		return -1;
	}

	return -1;
}

int8_t smbus_get_pinstatus(uint8_t slave_addr)
{
	uint8_t pinstatus_buf[1] = {0};

	XIic_DynInit(DUT0_SMBUS_ADDR);
	delay_us(10);
	XIic_Recv(DUT0_SMBUS_ADDR, slave_addr, pinstatus_buf, 1, XIIC_STOP);

	return pinstatus_buf[0];
}

/*
 * cmd_type/param1/param2, all cmd use
 * param3, all cmd use except writephy
 * data_len, only write use
 */
int8_t smbus_xfer_packet(uint8_t cmd_type, uint8_t slave_addr, uint8_t param1, uint8_t param2, uint8_t param3, uint8_t *pdata, uint8_t data_len)
{
	smbus_xfer_pack_t xfer_pack;
	int8_t ret;

    memset(&xfer_pack, 0, sizeof(smbus_xfer_pack_t));

    xfer_pack.control_buf[1] = cmd_type;
    xfer_pack.control_buf[2] = param1;
    xfer_pack.control_buf[3] = param2;
    xfer_pack.control_buf[4] = param3;
    xfer_pack.writedata_count = data_len;

    if(pdata != NULL && data_len > 0)
    {
        for(uint8_t i=0;i<data_len;i++)
        {
            xfer_pack.control_buf[i+5] = pdata[i];
        }
    }

    ret = smbus_xfer_core(&xfer_pack, slave_addr);

    if(ret == 0 && pdata != NULL && data_len == 0)
    {
        for(uint8_t i=0;i<(xfer_pack.readdata_count + 1);i++)
        {
            pdata[i] = xfer_pack.readdata_buf[i];
        }
    }

    return ret;
}
