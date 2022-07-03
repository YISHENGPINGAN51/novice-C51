#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"

void main()
{
	unsigned char str[] = "Hello LCD 1602";
	unsigned char str1[] = "123456789ABCDEF";
	LCDInit();
	DelayXms(10);
	LCDShowStr(0, 0, str);
	LCDShowStr(0, 1, str1);
	while (1);
}
