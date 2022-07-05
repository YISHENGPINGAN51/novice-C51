#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "Key.h"

void Startmenu();
void SubMenuOne();
void SubMenuTwo();
void SubMenuThree();
void SubMenuFour();
void AlarmSetMenu();
void KeyService();
void LCDShowService();
void ShowTempData(unsigned char x, unsigned char y, int *buf, unsigned char num);
int TEMPbuf[] = { 125, 126, 127, 128, 
                  223, 224, 225, 226,
                  334, 335, 336, 337,
                  421, 422, 423, 424 };
unsigned char menu;
void main()
{
	LCDInit();
	DelayXms(10);
	Startmenu();
	DelayXms(2000);
	LCDWriteCmd(LCD_SCREEN_CLR);//ÇåÆÁ
	while (1)
	{
		LCDShowService();
		KeyService();
	}
}

void KeyService()
{
	switch (Key_Scan())
	{
		case 1: menu++; if (menu == 4) menu = 0; break;
		case 2: menu--; if (menu > 4) menu = 3; break;
		case 3: menu = 0; break;
		case 4: menu = 4; LCDWriteCmd(LCD_SCREEN_CLR); DelayXms(2); break;
		default: break;
	}
}

void LCDShowService()
{
	switch (menu)
	{
		case 0: SubMenuOne(); break;
		case 1: SubMenuTwo(); break;
		case 2: SubMenuThree(); break;
		case 3: SubMenuFour(); break;
		case 4: AlarmSetMenu(); break;
		default: break;
	}
}
	
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
