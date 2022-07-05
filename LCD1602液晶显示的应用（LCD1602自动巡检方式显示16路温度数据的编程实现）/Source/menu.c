#include "menu.h"

extern int TEMPbuf[];

void Startmenu()
{
	LCDShowStr(1, 0, "The DAS of TEMP");
	LCDShowStr(6, 1, "V1.0");
}

void SubMenuOne()
{
	LCDShowStr(0, 0, "CH0:");
	ShowTempData(4, 0, TEMPbuf, 0);
	LCDShowStr(8, 0, "CH2:");
	ShowTempData(12, 0, TEMPbuf, 2);
	LCDShowStr(0, 1, "CH1:");
	ShowTempData(4, 1, TEMPbuf, 1);
	LCDShowStr(8, 1, "CH3:");
	ShowTempData(12, 1, TEMPbuf, 3);
}

void SubMenuTwo()
{
	LCDShowStr(0, 0, "CH4:");
	ShowTempData(4, 0, TEMPbuf, 4);
	LCDShowStr(8, 0, "CH6:");
	ShowTempData(12, 0, TEMPbuf, 6);
	LCDShowStr(0, 1, "CH5:");
	ShowTempData(4, 1, TEMPbuf, 5);
	LCDShowStr(8, 1, "CH7:");
	ShowTempData(12, 1, TEMPbuf, 7);
}

void SubMenuThree()
{
	LCDShowStr(0, 0, "CH8:");
	ShowTempData(4, 0, TEMPbuf, 8);
	LCDShowStr(8, 0, "CHa:");
	ShowTempData(12, 0, TEMPbuf, 10);
	LCDShowStr(0, 1, "CH9:");
	ShowTempData(4, 1, TEMPbuf, 9);
	LCDShowStr(8, 1, "CHb:");
	ShowTempData(12, 1, TEMPbuf, 11);
}

void SubMenuFour()
{
	LCDShowStr(0, 0, "CHc:");
	ShowTempData(4, 0, TEMPbuf, 12);
	LCDShowStr(8, 0, "CHe:");
	ShowTempData(12, 0, TEMPbuf, 14);
	LCDShowStr(0, 1, "CHd:");
	ShowTempData(4, 1, TEMPbuf, 13);
	LCDShowStr(8, 1, "CHf:");
	ShowTempData(12, 1, TEMPbuf, 15);
}

void AlarmSetMenu()
{
	LCDShowStr(4, 0, "ALARM MENU");
}

void ShowTempData(unsigned char x, unsigned char y, int *buf, unsigned char num)
{
	LCDSetPosition(x, y);
	LCDWriteData(*(buf + num)/100 + '0');
	LCDWriteData(*(buf + num)/10%10 + '0');
	LCDWriteData('.');
	LCDWriteData(*(buf + num)%10 + '0');
}
