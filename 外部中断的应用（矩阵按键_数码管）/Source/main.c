#include <reg51.h>
#include "display.h"
#include "delay.h"
#include "Key.h"

unsigned char KeyNum;
unsigned char KeyPressFlag;
//��������
void EX0_Init(void);
void Dis_Service();

void main()
{
	EX0_Init();
	P0 = 0x0f;
	while (1)
	{
		if (1 == KeyPressFlag)
		{
			KeyPressFlag = 0;
			KeyNum = Key_Scan();
//		P0 = 0x0f;//�߷�ת������Ҫ������ɨ����Ҫ
		}
		Dis_Service();
		Display();
	}
}

void Dis_Service()
{
	LEDBuf[0] = 23;
	LEDBuf[1] = 23;
	LEDBuf[2] = 23;
	LEDBuf[3] = KeyNum;
}

//�ⲿ�ж�0  ��ʼ��
void EX0_Init(void)
{
	IT0 = 1;//����  �½��ش���  TCON
	EX0 = 1;//IE
	EA = 1;
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
	KeyPressFlag = 1;
}