#include "LCD1602.h"

void LCDReadBF()
{
	unsigned char state;
	unsigned char i;
	LCD1602_DB = 0xFF;//IO口置1 做输入
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do
	{
		LCD1602_EN = 1;
		state = LCD1602_DB;
		LCD1602_EN = 0;
		i++;
		if (i > 50)
			break;
	}  while (state & 0x80);
}

void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//等待忙检测，不忙时操作
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

void LCDWriteData(unsigned char dat)
{
	LCDReadBF();//等待忙检测，不忙时操作
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

void LCDInit()
{
	LCDWriteCmd(LCD_MODE_PIN8);//显示模式设置 2行 5*8点阵
	LCDWriteCmd(LCD_DIS_ON);//显示开，光标关
	LCDWriteCmd(LCD_CURSOR_RIGHT);//光标右移
	LCDWriteCmd(LCD_SCREEN_CLR);//清屏
}

void LCDShowStr(unsigned char x, unsigned char y, unsigned char *str)
{
	if (0 == y)
	{
		LCDWriteCmd(0x80 | x);
	}
	else
	{
		LCDWriteCmd(0x80 | (0x40 + x));
	}
	while (*str != '\0')
	{
		LCDWriteData(*str);
		str++;
	}
}
