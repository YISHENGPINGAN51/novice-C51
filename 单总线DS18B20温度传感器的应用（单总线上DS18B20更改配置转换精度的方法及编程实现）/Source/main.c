#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"

void Timer0Init(void);
unsigned char flag;

void main()
{
	unsigned char ack;
	int temp;//保存接收温度数据
	int intTemp, decTemp;//分离温度数据的整数部分和小数部分
	unsigned char str[12];//保存数据转换成的字符串   ASCII
	unsigned char len;
	
	LCDInit();
	Timer0Init();
	Start18B20();
	DelayXms(10);
	while (1)
	{
		if (flag)
		{
			flag = 0;
			ack = Read18B20(&temp);
			if (ack)
			{
				intTemp = temp >> 4;//保留整数部分
				decTemp = temp & 0x0f;
				len = IntegerToStr(intTemp, str);
				str[len++] = '.';
				
				decTemp = (decTemp * 100) / 16;//*0.0625
				str[len++] = decTemp / 10 + '0';//小数部分
				str[len++] = decTemp % 10 + '0';
				while (len < 6)
				{
					str[len++] = ' ';
				}
				str[len] = '\0';
				LCDShowStr(0, 0, str);
			}
			Start18B20();
		}
	}
}

void Timer0Init(void)		//10毫秒@12.000MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xF0;		//设置定时初始值
	TH0 = 0xD8;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA = 1;
	TR0 = 1;		//定时器0开始计时
}

void Timer0_ISR() interrupt 1
{
	static unsigned char timer0Cnt = 0;
	TR0 = 0;
	TL0 = 0xF0;		//设置定时初始值
	TH0 = 0xD8;		//设置定时初始值
	timer0Cnt++;
	if (timer0Cnt >= 100)
	{
		timer0Cnt = 0;
		flag = 1;
	}
	TR0 = 1;
}