#include "LCD1602.h"

/*****************************************************
函数名：LCDReadBF
功  能：1602读忙检测
参  数：无
返回值：无
*****************************************************/
#ifndef LCD1602_4PINS
void LCDReadBF()
{
	unsigned char state;
	unsigned char i;
	LCD1602_DB |= 0xFF;//高四位IO置1  低四位保持不变
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
#else
void LCDReadBF()
{
	unsigned char state;
	unsigned char i;
	LCD1602_DB |= 0xF0;//高四位IO置1  低四位保持不变
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do
	{
		LCD1602_EN = 1;
		state = LCD1602_DB & 0xF0;//读高四位
		LCD1602_EN = 0;
		
		LCD1602_EN = 1;
		state |= (LCD1602_DB & 0xF0) >> 4;//读低四位
		LCD1602_EN = 0;
		
		i++;
		if (i > 50)
			break;
	}  while (state & 0x80);
}
#endif

/*****************************************************
函数名：LCDWriteCmd
功  能：LCD1602写指令
参  数：cmd 待写指令
返回值：无
*****************************************************/
#ifndef LCD1602_4PINS
void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//等待忙检测，不忙时操作
	LCD1602_RS = 0;//命令
	LCD1602_RW = 0;//写
	LCD1602_DB = cmd;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}
#else
void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//等待忙检测，不忙时操作
	LCD1602_RS = 0;//命令
	LCD1602_RW = 0;//写
	LCD1602_DB = cmd;//高四位
	DelayXms(1);
	LCD1602_EN = 1;
	LCD1602_EN = 0;
	LCD1602_DB = cmd << 4;//低四位
	DelayXms(1);
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}
#endif

/*****************************************************
函数名：LCDWriteData
功  能：LCD1602写数据
参  数：dat 待写入数据
返回值：无
*****************************************************/
#ifndef LCD1602_4PINS
void LCDWriteData(unsigned char dat)
{
	LCDReadBF();//等待忙检测，不忙时操作
	LCD1602_RS = 1;//数据
	LCD1602_RW = 0;//写
	LCD1602_DB = dat;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}
#else
void LCDWriteData(unsigned char dat)
{
	LCDReadBF();//等待忙检测，不忙时操作
	LCD1602_RS = 1;//数据
	LCD1602_RW = 0;//写
	LCD1602_DB = dat;//高四位
	DelayXms(1);
	LCD1602_EN = 1;
	LCD1602_EN = 0;
	LCD1602_DB = dat << 4;//低四位
	DelayXms(1);
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}
#endif

/*****************************************************
函数名：LCDInit
功  能：LCD1602初始化
参  数：无
返回值：无
*****************************************************/
#ifndef LCD1602_4PINS
void LCDInit()
{
	LCDWriteCmd(LCD_MODE_PIN8);//显示模式设置 2行 5*8点阵
	LCDWriteCmd(LCD_DIS_ON);//显示开，光标关
	LCDWriteCmd(LCD_CURSOR_RIGHT);//光标右移
	LCDWriteCmd(LCD_SCREEN_CLR);//清屏
}
#else
void LCDInit()
{
	//看英文手册
	LCDWriteCmd(0x33);
	DelayXms(5);
	LCDWriteCmd(0x32);
	
	LCDWriteCmd(LCD_MODE_PIN4);//显示模式设置 2行 5*8点阵
	LCDWriteCmd(LCD_DIS_ON);//显示开，光标关
	LCDWriteCmd(LCD_CURSOR_RIGHT);//光标右移
	LCDWriteCmd(LCD_SCREEN_CLR);//清屏
}
#endif

/*****************************************************
函数名：LCDSetPosition
功  能：设置显示位置  DDRAM地址
参  数：x-列  y-行  x:0-15  y:0-1
返回值：无
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
功  能：显示字符
参  数：x-列  y-行  *str-待显示字符数据
返回值：无
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
功  能：显示自定义字符
参  数：*str-自定义字符数据
返回值：无
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
功  能：显示自定义字符
参  数：x-列  y-行  pos-CGRAM位置  *str-自定义字符数据
返回值：无
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

/*****************************************************
函数名：IntegerToStr
功  能：整形数据转字符串
参  数：dat-整形数据  *str-字符数据
返回值：len-字符数组的字符个数  长度
*****************************************************/
unsigned char IntegerToStr(long dat, unsigned char *str)
{
	unsigned char i;
	unsigned char len;
	unsigned char buf[11];
	if (dat < 0)
	{
		dat = -dat;//如果是负数，取绝对值
		*str++ = '-';
		len++;
	}
	do
	{
		buf[i++] = dat % 10 + '0';//等价于dat % 10 + 0x30;  buf[0] = '8' buf[1] = '7' buf[2] = '6'
		dat /= 10;
	}  while (dat > 0);
	len += i;
	while (i-- > 0)
	{
		*str++ = buf[i];
	}
	*str = '\0';
	return len;
}
