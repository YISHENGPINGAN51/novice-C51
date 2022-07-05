#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include <stdio.h>
#include "menu.h"

void LCDShowService();
void EXT_Init();
void Timer0Init(void);

unsigned char sec, min, hour;

unsigned int timer0Cnt;
unsigned char state = 0;

void main()
{
	LCDInit();
	EXT_Init();
	Timer0Init();
	DelayXms(10);
	Startmenu();
	DelayXms(2000);
	LCDWriteCmd(LCD_SCREEN_CLR);//清屏
	while (1)
	{
		LCDShowStr(0, 0, "  Current Time  ");
		LCDShowService();
	}
}

void LCDShowService()
{
	switch(state)
	{
		case 0: TR0 = 1; 	LCDShowSec(); LCDShowMin(); LCDShowHour(); break;
		case 1: LCDShowSec(); break;
		case 2: LCDShowMin(); break;
		case 3: LCDShowHour(); break;
		default: break;
	}
}

void EXT_Init()
{
	IT0 = 1;//下降沿触发方式 INT0
	IT1 = 1;//下降沿触发方式 INT1
	EX0 = 1;
	EX1 = 1;
}

void EX0_ISR() interrupt 0
{
	TR0 = 0;
	state++;
	if (state > 3)
	{
		state = 0;
	}
}

void EX1_ISR() interrupt 2
{
	switch (state)
	{
		case 1: sec++; if (sec >= 60) sec = 0; break;
		case 2: min++; if (min >= 60) min = 0; break;
		case 3: hour++; if (hour >= 24) hour = 0; break;
		default: break;
	}
}

void Timer0Init(void)		//1毫秒@12.000MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA = 1;
//	TR0 = 1;		//定时器0开始计时
}

void Time0ISR() interrupt 1
{
	TR0 = 0;
	timer0Cnt++;
	if (timer0Cnt >= 1000)
	{
		timer0Cnt = 0;
		sec++;
		if (sec >= 60)
		{
			sec = 0;
			min++;
			if (min >= 60)
			{
				min = 0;
				hour++;
				if (hour >= 24)
				{
					hour = 0;
				}
			}
		}
	}
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TR0 = 1;
}