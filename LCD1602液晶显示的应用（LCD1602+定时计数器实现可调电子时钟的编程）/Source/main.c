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
	LCDWriteCmd(LCD_SCREEN_CLR);//����
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
	IT0 = 1;//�½��ش�����ʽ INT0
	IT1 = 1;//�½��ش�����ʽ INT1
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

void Timer0Init(void)		//1����@12.000MHz
{
//	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;
	EA = 1;
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	TR0 = 1;
}