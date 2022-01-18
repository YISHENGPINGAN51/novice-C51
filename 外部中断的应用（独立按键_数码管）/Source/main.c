#include <reg51.h>
#include "display.h"
#include "delay.h"

//��������
void EX0_Init(void);
void EX1_Init(void);
void Dis_Service();
unsigned int parameter = 0;

void main()
{
	unsigned int i;
	EX0_Init();
	EX1_Init();
	EA = 1;
	for (i = 0; i < 2000; i++)
	{
		Display();
	}
	while (1)
	{
		Dis_Service();
	}
}

void Dis_Service()
{
	LEDBuf[0] = parameter / 1000;
	LEDBuf[1] = parameter / 100 % 10;
	LEDBuf[2] = parameter / 10 % 10;
	LEDBuf[3] = parameter % 10;
	Display();
}

//�ⲿ�ж�0  ��ʼ��
void EX0_Init(void)
{
	IT0 = 1;//����  �½��ش���  TCON
	EX0 = 1;//IE
}

//�ⲿ�ж�1  ��ʼ��
void EX1_Init(void)
{
	IT1 = 1;//����  �½��ش���  TCON
	EX1 = 1;//IE
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

void EX0_ISR(void) interrupt 0
{
	DelayXms(10);
	if (!INT0)
	{
		parameter++;
		if (parameter > 9999)
			parameter = 0;
	}
}

void EX1_ISR(void) interrupt 2
{
	DelayXms(10);
	if (!INT1)
	{
		parameter--;
		if (parameter > 9999)
			parameter = 9999;
	}
}