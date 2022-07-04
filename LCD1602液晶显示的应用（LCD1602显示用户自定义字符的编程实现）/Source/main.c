#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"

void main()
{
	unsigned char str[] = "Hello LCD 1602";
	unsigned char str1[] = "123456789ABCDEF";
	unsigned char code str2[] = { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00 };//Ò»
	unsigned char code str3[] = { 0x00, 0x00, 0x00, 0x0E, 0x00, 0x1F, 0x00, 0x00 };//¶þ
	unsigned char code str4[] = { 0x10, 0x06, 0x09, 0x08, 0x08, 0x09, 0x06, 0x00 };//¡æ
	LCDInit();
	DelayXms(10);
//	LCDWriteCGRAM();
	LCDShowStr(0, 1, str);
	while (1)
	{
		LCDSetChar(8, 0, 0, str2);
		LCDSetChar(9, 0, 1, str3);
		LCDSetChar(10, 0, 2, str4);
	}
}
