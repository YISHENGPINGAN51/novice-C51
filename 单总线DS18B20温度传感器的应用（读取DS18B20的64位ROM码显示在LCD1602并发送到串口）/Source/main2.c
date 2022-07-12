#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include "uart.h"

void LCDShowRomCode(unsigned char *romcode, unsigned char num);
unsigned char code rom1[] = { 0x28, 0x30, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0x8E };
unsigned char code rom2[] = { 0x28, 0x31, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xB9 };
unsigned char code rom3[] = { 0x28, 0x32, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xE0 };
unsigned char code rom4[] = { 0x28, 0x33, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xD7 };

unsigned char romcode[8];

void main()
{
	unsigned char i;
	LCDInit();    //≥ı ºªØ“∫æß
	UartInit();
	DelayXms(10);
	ReadRomCode(romcode);
	LCDShowRomCode(romcode, 1);
	for (i = 0; i < 8; i++)
	{
		sendByte(romcode[i]);
	}
	while (1);
}

void LCDShowRomCode(unsigned char *romcode, unsigned char num)
{
	unsigned char i;
	unsigned char temp;
	
	LCDSetPosition(7, 0);
	LCDWriteData('#');
	LCDWriteData(num + '0');
	
	LCDSetPosition(0, 1);
	for (i = 0; i < 8; i++)//eg: 2830C5B8000000(28 + B8 C5 30)
	{
		temp = romcode[i] >> 4;
		if (temp < 10)
			LCDWriteData(temp + '0');
		else
			LCDWriteData(temp + '7');//ABCDEF
		
		temp = romcode[i] & 0x0F;
		if (temp < 10)
			LCDWriteData(temp + '0');
		else
			LCDWriteData(temp + '7');//ABCDEF
	}
}