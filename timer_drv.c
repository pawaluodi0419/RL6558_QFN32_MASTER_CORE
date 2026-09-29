#include "platform.h"

void delay_ms(u16 time_ms)
{
	uint16_t time_cnt;
	uint16_t i;

	for(time_cnt=0;time_cnt<time_ms;time_cnt++){
		for(i=0;i<4166;i++);
	}
}

void delay_us(u16 time_us)
{
	uint16_t time_cnt;
	uint16_t i;

	for(time_cnt=0;time_cnt<time_us;time_cnt++){
		for(i=0;i<4;i++);
	}
}
