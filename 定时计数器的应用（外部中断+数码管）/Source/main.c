#include <reg51.h>
#include "display.h"

void Timer0Init(void);
void EX0_Init();
void EX1_Init();
void display_Service();

unsigned int numCnt = 0;//����
unsigned char temp0;//������ʾ���м����
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;

void main()
{
	EX0_Init();
	EX1_Init();
	Timer0Init();
	EA = 1;//�ж��ܿ���
	while (1)
	{
		display_Service();
	}
}

void display_Service()
{
	temp0 = numCnt / 1000;
	temp1 = numCnt / 100 % 10;
	temp2 = numCnt / 10 % 10;
	temp3 = numCnt % 10;
	if (numCnt < 1000)
		LEDBuf[0] = 23;
	else
		LEDBuf[0] = temp0;
	if (numCnt < 100)
		LEDBuf[1] = 23;
	else
		LEDBuf[1] = temp1;
	if (numCnt < 10)
		LEDBuf[2] = 23;
	else
		LEDBuf[2] = temp2;
	LEDBuf[3] = temp3;
}
void EX0_Init()
{
	IT0 = 1;//������ʽ  �½���
	EX0 = 1;
}

void EX1_Init()
{
	IT1 = 1;//������ʽ  �½���
	EX1 = 1;
}

void Timer0Init(void)		//1����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;		//��ʱ��0���ն˿���
//	EA = 1;		//�ж��ܿ���
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
	Display();
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TR0 = 1;
}

void EX0_ISR(void) interrupt 0
{
	EX0 = 0;
	numCnt++;
	if (numCnt > 9999)
	{
		numCnt = 0;
	}
	EX0 = 1;
}

void EX1_ISR(void) interrupt 2
{
	EX0 = 0;
	numCnt--;
	if (numCnt > 9999)
	{
		numCnt = 9999;
	}
	EX0 = 1;
}