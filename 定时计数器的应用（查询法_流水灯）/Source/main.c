#include <reg51.h>
#include <intrins.h>

void timer0_Init();
unsigned char timerCnt;
unsigned char temp = 0xfe;

void main()
{
	timer0_Init();
	while (1)
	{
		if (1 == TF0)
		{
			TF0 = 0;
			TH0 = (65536 - 20000) / 256;//���¸���ֵ  ���ڲ�����һ�ε�20ms��ʱ
			TL0 = (65536 - 20000) % 256;
			//1S = 1000ms / 20ms = 50��
			timerCnt++;
			if (timerCnt >= 50)
			{
				timerCnt = 0;
				P1 = temp;
				temp = _crol_(temp, 1);
			}
		}
	}
}

void timer0_Init()
{
	//1������TMOD ȷ��������ʽ ��ʱ/����   ��һ�ֹ�����ʽ ������ʽ1   GATE 0
	TMOD = 0X01;//GATE  C/T  M1  M0  GATE  C/T  M1  M0
	//2����ʱ��ֵ�ļ���  (eg: 20ms  12M)
	TH0 = (65536 - 20000) / 256;
	TL0 = (65536 - 20000) % 256;
	//3���򿪶�ʱ/������
	TR0 = 1;//������ʱ������
}