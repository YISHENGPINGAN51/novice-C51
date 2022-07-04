#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include <string.h>

void main()
{
	unsigned char i;
	unsigned char str[] = "Hello LCD 1602";
	unsigned char str1[] = "Welcome to Study LCD 1602";
	LCDInit();
	DelayXms(10);
//	LCDWriteCmd(LCD_DIS_MODE_LEFT);//初始设置的字符输入模式 整屏左移

//	while (1)
//	{
//		LCDWriteCmd(0x80);
//		for (i = 0; i < strlen(str); i++)
//		{
//			LCDWriteData(str[i]);
//			DelayXms(200);
//		}
//		
//		LCDWriteCmd(0xC0);
//		for (i = 0; i < strlen(str1); i++)
//		{
//			LCDWriteData(str1[i]);
//			DelayXms(200);
//		}
//	}

	LCDWriteCmd(0x80);
	for (i = 0; i < strlen(str); i++)
	{
		LCDWriteData(str[i]);
//		DelayXms(200);
	}
	LCDWriteCmd(0xC0);
	for (i = 0; i < strlen(str1); i++)
	{
		LCDWriteData(str1[i]);
//		DelayXms(200);
	}
	while(1)
	{
		LCDWriteCmd(LCD_DIS_MOVE_LEFT);
		DelayXms(500);
	}
}
