#include <reg51.h>
#include <intrins.h>
#include "display.h"

void Timer0Init(void);
void Timer1Init(void);

unsigned char secCnt;
unsigned char sec = 60;
unsigned char timerCnt;
unsigned char temp = 0xfe;

void main()
{
	Timer0Init();
	Timer1Init();
	EA = 1;
	while (1)
	{
		LEDBuf[0] = 23;
		LEDBuf[1] = 23;
		LEDBuf[2] = sec / 10;
		LEDBuf[3] = sec % 10;
	}
}

void Timer0Init(void)		//1����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer1Init(void)		//50����@12.000MHz
{
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0xB0;		//���ö�ʱ��ֵ
	TH1 = 0x3C;		//���ö�ʱ��ֵ
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
	TR0 = 0;
	Display();
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TR0 = 1;
}

void timer1_ISR(void) interrupt 3
{
	TR1 = 0;
	secCnt++;
	timerCnt++;
	if (timerCnt >= 20)
	{
		timerCnt = 0;
		P1 = temp;
		temp = _crol_(temp, 1);
	}
	if (secCnt >= 20)
	{
		secCnt = 0;
		sec--;
		if (sec > 60)
		{
			sec = 60;
		}
	}
	TL1 = 0xB0;		//���ö�ʱ��ֵ
	TH1 = 0x3C;		//���ö�ʱ��ֵ
	TR1 = 1;
}