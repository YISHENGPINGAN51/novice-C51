#include <reg51.h>
#include "display.h"

void Timer0Init(void);
void display_Service();
void Timer1Init(void);

unsigned int dataNum;
unsigned int timerCnt;
void main()
{
	Timer0Init();
	Timer1Init(); 
	EA = 1;		//�ж��ܿ���
	while (1)
	{
		display_Service();
	}
}

void display_Service()
{
	LEDBuf[0] = dataNum / 1000;
	LEDBuf[1] = dataNum / 100 % 10;
	LEDBuf[2] = dataNum / 10 % 10;
	LEDBuf[3] = dataNum % 10;
}

void Timer0Init(void)		//1����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;		//��ʱ��0���жϿ���
//	EA = 1;		//�ж��ܿ���
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer1Init(void)		//@12.000MHz
{
	TMOD &= 0x0F;		//���ü�����ģʽ  GATE  C/T  M1  M0  0  1  0  1
	TMOD |= 0x50;		//���ü�����ģʽ
	TL1 = 0;		//���ö�ʱ��ֵ
	TH1 = 0;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	ET1 = 1;		//��ʱ��1���жϿ���
//	EA = 1;		//�ж��ܿ���
	TR1 = 1;		//��ʱ��1��ʼ����
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
	timerCnt++;
	if (timerCnt >= 1000)//1Sʱ�䵽
	{
		TR1 = 0;
		timerCnt = 0;
		dataNum = TH1 * 256 + TL1;
		TH1 = TL1 = 0;
		TR1 = 1;
	}
	Display();
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TR0 = 1;
}