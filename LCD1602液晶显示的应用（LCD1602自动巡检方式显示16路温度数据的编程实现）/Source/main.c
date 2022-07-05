#include <reg51.h>
#include "Key.h"
#include "menu.h"

void KeyService();
void LCDShowService();
void Timer0Init(void);

TEMPbuf[] = { 125, 126, 127, 128, 
							223, 224, 225, 226,
							334, 335, 336, 337,
							421, 422, 423, 424 };

unsigned char menu;
bit mode = 0;
unsigned int timer0Cnt;
unsigned char menuFlag;

void main()
{
	LCDInit();
	Timer0Init();
	DelayXms(10);
	Startmenu();
	DelayXms(2000);
	LCDWriteCmd(LCD_SCREEN_CLR);//����
	while (1)
	{
		if (mode == 0)
		{
			TR0 = 1;
			if (menuFlag == 1)
			{
				menuFlag = 0;
				menu++;
				if (menu == 4)
					menu = 0;
			}
		}
		LCDShowService();
		KeyService();
	}
}

void KeyService()
{
	switch (Key_Scan())
	{
		case 1: mode = ~mode; break;
		case 2: TR0 = 0;
						if (mode == 1)
					  {
							menu++;
							if (menu == 4)
								menu = 0;
						}
						break;
		case 3: mode = 1; TR0 = 0; menu = 0; break;
		case 4: mode = 1; TR0 = 0; menu = 4; LCDWriteCmd(LCD_SCREEN_CLR); DelayXms(2); break;
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
	if (timer0Cnt >= 2000)
	{
		timer0Cnt = 0;
		menuFlag = 1;
	}
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	TR0 = 1;
}