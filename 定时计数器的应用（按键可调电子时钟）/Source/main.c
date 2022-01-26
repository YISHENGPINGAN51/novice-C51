#include <reg51.h>
#include "display.h"

void Timer0Init(void);
void Timer1Init(void);
void showNormal();
void EX0_Init();
void EX1_Init();
void showSec();
void showMin();
void showHour();

unsigned char timerCnt;
unsigned char sec;
unsigned char min;
unsigned char hour;
unsigned char state = 0;

void main()
{
	EX0_Init();
	EX1_Init();
	Timer0Init();
	Timer1Init();
	EA = 1;
	while (1)
	{
		switch (state)
		{
			case 0: TR0 = 1; showNormal(); break;//����ʱ��״̬
			case 1: showSec(); break;//����
			case 2: showMin(); break;//����
			case 3: showHour(); break;//��ʱ
			default: break;
		}
	}
}

void showNormal()
{
	LEDBuf[0] = hour / 10;
	LEDBuf[1] = hour % 10;
	LEDBuf[2] = min / 10;
	LEDBuf[3] = min % 10;
}

void showSec()
{
	LEDBuf[0] = 23;
	LEDBuf[1] = 23;
	LEDBuf[2] = sec / 10;
	LEDBuf[3] = sec % 10;
}

void showMin()
{
	LEDBuf[0] = min / 10;
	LEDBuf[1] = min % 10;
	LEDBuf[2] = 23;
	LEDBuf[3] = 23;
}

void showHour()
{
	LEDBuf[0] = hour / 10;
	LEDBuf[1] = hour % 10;
	LEDBuf[2] = 23;
	LEDBuf[3] = 23;
}

void EX0_Init()
{
	IT0 = 1;
	EX0 = 1;
}

void EX1_Init()
{
	IT1 = 1;
	EX1 = 1;
}

void Timer0Init(void)		//50����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xB0;		//���ö�ʱ��ֵ
	TH0 = 0x3C;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer1Init(void)		//1����@12.000MHz
{
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0x18;		//���ö�ʱ��ֵ
	TH1 = 0xFC;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	ET1 = 1;
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}

/*****************************************************************
1���жϷ�����һ����һ��û�з���ֵ�ĺ���
2���жϷ�����һ����û�в����ĺ���
3���жϷ���������������ؼ��� interrupt
4��interrupt n 0 - 4  5���ж�Դ  8*n + 0003H
0003H INT0    000BH T0    0013H INT1    001BH T1    0023H ES
5���жϷ��������ܱ����������������������
6��n�����using m (0 - 3)�����Ĵ�����
*****************************************************************/
void timer0_ISR(void) interrupt 1
{
	timerCnt++;
	if (timerCnt >= 20)//20��50ms�жϣ���1Sʱ�䵽
	{
		timerCnt = 0;
		sec++;
		if (sec >= 60)
		{
			sec = 0;
			min++;
			if (min >= 60)
			{
				min = 0;
				hour++;
				if (hour >= 23)
				{
					hour = 0;
				}
			}
		}
	}
	TL0 = 0xB0;		//���ö�ʱ��ֵ
	TH0 = 0x3C;		//���ö�ʱ��ֵ
}

void timer1_ISR(void) interrupt 3
{
	TR1 = 0;
	Display();
	TL1 = 0x18;		//���ö�ʱ��ֵ
	TH1 = 0xFC;		//���ö�ʱ��ֵ
	TR1 = 1;
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
		case 0: break;
		case 1: sec++; if (sec >= 60) sec = 0; break;
		case 2: min++; if (min >= 60) min = 0; break;
		case 3: hour++; if (hour >= 23) hour = 0; break;
		default: break;
	}
}