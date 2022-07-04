#include "LCD1602.h"

/*****************************************************
函数名：LCDReadBF
功  能；1602读忙检测
参  数；无
返回值；无
*****************************************************/
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

/*****************************************************
函数名：LCDWriteCmd
功  能；LCD1602写指令
参  数；cmd 待写指令
返回值；无
*****************************************************/
void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//等待忙检测，不忙时操作
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

/*****************************************************
函数名：LCDWriteData
功  能；LCD1602写数据
参  数；dat 待写入数据
返回值；无
*****************************************************/
void LCDWriteData(unsigned char dat)
{
	LCDReadBF();//等待忙检测，不忙时操作
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

/*****************************************************
函数名：LCDInit
功  能；LCD1602初始化
参  数；无
返回值；无
*****************************************************/
void LCDInit()
{
	LCDWriteCmd(LCD_MODE_PIN8);//显示模式设置 2行 5*8点阵
	LCDWriteCmd(LCD_DIS_ON);//显示开，光标关
	LCDWriteCmd(LCD_CURSOR_RIGHT);//光标右移
	LCDWriteCmd(LCD_SCREEN_CLR);//清屏
}

/*****************************************************
函数名：LCDSetPosition
功  能；设置显示位置  DDRAM地址
参  数；x-列  y-行  x:0-15  y:0-1
返回值；无
*****************************************************/
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

/*****************************************************
函数名：LCDShowStr
功  能；显示字符
参  数；x-列  y-行  *str-待显示字符数据
返回值；无
*****************************************************/
void LCDShowStr(unsigned char x, unsigned char y, unsigned char *str)
{
	LCDSetPosition(x, y);
	while (*str != '\0')
	{
		LCDWriteData(*str++);
	}
}

/*****************************************************
函数名：LCDWriteCGRAM
功  能；显示自定义字符
参  数；*str-自定义字符数据
返回值；无
*****************************************************/
void LCDWriteCGRAM(unsigned char *str)
{
	unsigned char i;
	LCDWriteCmd(LCD_SET_CGRAM_ADDR);//设定 CGRAM 地址
	for (i = 0; i < 8; i++)
	{
		LCDWriteData(*str++);//写入自定义图形
	}
	LCDWriteCmd(0xC0);//设定屏幕上的显示位置
	LCDWriteData(0x00);//从 CGRAM 中取出自定义图形显示
}

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
		LCDWriteCmd(LCD_SET_CGRAM_ADDR + pos*8 + i);
		LCDWriteData(*(str+i));
	}
	//显示
	LCDSetPosition(x, y);//设置显示位置 DDRAM
	LCDWriteData(0x00 + pos);//显示代码
}
