#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include "menu.h"

int TEMPbuf[] = { 0, 0, 0, 0 };
unsigned char menu = 0;
unsigned char menuFlag;

void LCDShowService();
void Timer0Init(void);

void main()
{
	LCDInit();
	Timer0Init();
	DelayXms(10);
	Startmenu();
	DelayXms(2000);
	Start18B20();
	LCDWriteCmd(LCD_SCREEN_CLR);//����
	while (1)
	{
		if (menuFlag == 1)
		{
			menuFlag = 0;
			menu++;
			if (menu == 2)
				menu = 0;
			Get18B20Temp(TEMPbuf, 1);
			Get18B20Temp(TEMPbuf + 1, 2);
			Get18B20Temp(TEMPbuf + 2, 3);
			Get18B20Temp(TEMPbuf + 3, 4);
		}
		LCDShowService();
	}
}

void LCDShowService()
{
	switch (menu)
	{
		case 0: SubMenuOne(); break;
		case 1: SubMenuTwo(); break;
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
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Time0ISR() interrupt 1
{
	static unsigned int timer0Cnt;
	TR0 = 0;
	timer0Cnt++;
	if (timer0Cnt >= 3000)
	{
		timer0Cnt = 0;
		menuFlag = 1;
	}
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	TR0 = 1;
}