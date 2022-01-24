#include <reg51.h>
#include "display.h"

sbit LED = P1^0;

void Timer0Init(void);
void display_Service();

unsigned int num = 4534;
unsigned int systemTimer = 0;
unsigned char systemFlag = 1;

void main()
{
	Timer0Init();
	do
	{
		if (systemTimer % 50 == 0)
		{
			LED = ~LED;
		}
	}	while (systemTimer < 5000);//5S 5000ms/1ms
	systemFlag = 0;
	LED = 1;
	
	while (1)
	{
		display_Service();
	}
}

void display_Service()
{
	LEDBuf[0] = num / 1000;
	LEDBuf[1] = num / 100 % 10;
	LEDBuf[2] = num / 10 % 10;
	LEDBuf[3] = num % 10;
}
void Timer0Init(void)		//1����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;		//��ʱ��0���ն˿���
	EA = 1;		//�ж��ܿ���
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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
	if (1 == systemFlag)
	{
		systemTimer++;
	}
	Display();
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TR0 = 1;
}