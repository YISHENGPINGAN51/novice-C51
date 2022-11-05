#include <reg51.h>
#include "I2C.h"
#include "delay.h"
#include "LCD1602.h"
#include "EEPROM.h"

void bufTohexStr(unsigned char *buf, unsigned char len, unsigned char *str);

void main()
{
	unsigned char i;
	unsigned char str[40];
	unsigned char buf[10];//0xff, 0x12, 0xff
	LCDInit();
	DelayXms(10);
	
	E2Read(0x51, 0x10, buf, 10);

	bufTohexStr(buf, 10, str);
	LCDShowStr(1, 0, str);
	
	for (i = 0; i < sizeof(buf); i++)
	{
		buf[i] = buf[i] + 1;
	}
	E2Write(0x51, 0x10, buf, 10);
	
	for (i = 0; i < sizeof(buf); i++)
	{
		buf[i] = buf[i] + 1;
	}
	E2WritePage(0x51, 0x10, buf, 10);
	while (1)
	{
		LCDWriteCmd(LCD_DIS_MOVE_LEFT);
		DelayXms(2000);
	}
}

//数据缓冲区中的数据转十六进制数据显示，并保存在str[]中
void bufTohexStr(unsigned char *buf, unsigned char len, unsigned char *str)
{
	unsigned char tmp;
	unsigned char i;
	for (i = 0; i < len; i++)
	{
		tmp = buf[i] >> 4;//0xff
		if (tmp <= 9)
			*str++ = tmp + '0';
		else
			*str++ = tmp + '7';//tmp - 10 + 'A'
		tmp = buf[i] & 0x0F;
		if (tmp <= 9)
			*str++ = tmp + '0';
		else
			*str++ = tmp + '7';//tmp - 10 + 'A'
		*str++ = ' ';//每处理完一个字节的数据加一个空格隔开
	}
	*(str) = '\0';
}