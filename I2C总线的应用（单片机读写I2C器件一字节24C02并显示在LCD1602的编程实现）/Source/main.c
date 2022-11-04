#include <reg51.h>
#include "I2C.h"
#include "delay.h"
#include "LCD1602.h"
#include "EEPROM.h"

void numTohexStr(unsigned char dat, unsigned char *str);

void main()
{
	unsigned char dat;
	unsigned char str[5];
	LCDInit();
	DelayXms(10);
	//dat = 0xFF;//复原实验现象
	dat = E2ReadByte(0x50, 0x20);
	LCDSetPosition(0, 0);
	LCDWriteData(dat/100 + '0');
	LCDWriteData(dat/10%10 + '0');
	LCDWriteData(dat%10 + '0');

	numTohexStr(dat, str);
	LCDShowStr(5, 0, str);

	dat++;
	E2WriteByte(0x50, 0x20, dat);
	LCDSetPosition(0, 1);
	LCDWriteData(dat/100 + '0');
	LCDWriteData(dat/10%10 + '0');
	LCDWriteData(dat%10 + '0');
	
	numTohexStr(dat, str);
	LCDShowStr(5, 1, str);
	while (1);
}

//数据转十六进制数据显示的函数
void numTohexStr(unsigned char dat, unsigned char *str)
{
	unsigned char tmp;
	tmp = dat >> 4;//0xff
	if (tmp <= 9)
		*str++ = tmp + '0';
	else
		*str++ = tmp + '7';//tmp - 10 + 'A'
	tmp = dat & 0x0F;
	if (tmp <= 9)
		*str++ = tmp + '0';
	else
		*str++ = tmp + '7';//tmp - 10 + 'A'
	*str = '\0';
}