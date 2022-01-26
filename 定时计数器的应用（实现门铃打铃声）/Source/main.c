#include <reg51.h>
#include "Key.h"

sbit DoorBell = P3^7;

void Timer0Init(void);
void Key_Service();

unsigned int timerCnt = 0;
unsigned char uc500Hz = 0;
unsigned char uc700Hz = 0;
unsigned char flag = 0;
void main()
{
	Timer0Init();
	while (1)
	{
		Key_Service();
	}
}

void Key_Service()
{
	switch (Key_Scan())
	{
		case 1: TR0 = ~TR0; break;
		case 2: break;
		case 3: break;
		case 4: break;
		default: break;
	}
}

void Timer0Init(void)		//250΢��@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x06;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;
	EA = 1;
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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
	if (timerCnt >= 2000)
	{
		timerCnt = 0;
		flag = ~flag;
	}
	if (!flag)
	{
		uc700Hz++;
		if (uc700Hz >= 3)
		{
			uc700Hz = 0;
			DoorBell = ~DoorBell;
		}
	}
	if (flag)
	{
		uc500Hz++;
		if (uc500Hz >= 4)
		{
			uc500Hz = 0;
			DoorBell = ~DoorBell;
		}
	}
	TL0 = 0x06;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
}