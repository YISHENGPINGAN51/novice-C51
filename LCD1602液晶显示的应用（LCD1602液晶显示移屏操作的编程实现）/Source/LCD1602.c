#include "LCD1602.h"

//unsigned char code str[] = { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00 };

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


void LCDSetPosition(unsigned char x, unsigned char y)
{
	if (0 == y)
	{
		LCDWriteCmd(0x80 | x);
	}
	else
	{
		LCDWriteCmd(0x80 | (0x40 + x));
	}
}
	
void LCDShowStr(unsigned char x, unsigned char y, unsigned char *str)
{
	LCDSetPosition(x, y);
	while (*str != '\0')
	{
		LCDWriteData(*str++);
	}
}

//第一种方法
//void LCDWriteCGRAM()
//{
//	unsigned char i;
//	LCDWriteCmd(0x40);//1、构造自定义字符
//	for (i = 0; i < 64; i++)
//	{
//		LCDWriteData(str[i]);
//	}
//	//2、显示这个字符
//	LCDWriteCmd(0x80 | 0x00);
//	LCDWriteData(0x01);
//}

//第二种方法
/*****************************************************
函数名：LCDSetChar
功  能；显示自定义字符
参  数；x-列  y-行  pos-CGRAM位置  *str-自定义字符数据
返回值；无
*****************************************************/
void LCDSetChar(unsigned char x, unsigned char y, unsigned char pos, unsigned char *str)//x:0~F y:0/1 pos:0~7
{
	unsigned char i;
	//先构造自定义字符 确定位置 CGRAM
	for (i = 0; i < 8; i++)
	{
		LCDWriteCmd(0x40 + pos*8 + i);
		LCDWriteData(*(str+i));
	}
	//显示
	LCDSetPosition(x, y);//设置显示位置 DDRAM
	LCDWriteData(0x00 + pos);//显示代码
}
