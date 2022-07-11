#include <reg51.h>
#include "delay.h"
#include "display.h"
#include "DS18B20.h"

void Timer0Init(void);
unsigned char flag;

void main()
{
	unsigned char ack;
	int temp;//��������¶�����
	int intTemp, decTemp;//�����¶����ݵ��������ֺ�С������
	
	Timer0Init();
	Start18B20();
	
	while (1)
	{
		if (flag)
		{
			flag = 0;
			ack = Read18B20(&temp);
			if (ack)
			{
				intTemp = temp >> 4;//������������
				decTemp = temp & 0x0f;
				decTemp = (decTemp * 10) / 16;//*0.0625  �Ŵ�10��  С�����1λ
				
				if (intTemp < 0)
				{
					intTemp = -intTemp;
					LEDBuf[0] = 22;
					if (decTemp % 10 != 0)  //DS18B20����0.5������
					{
						intTemp = intTemp - 1;
					}
				}
				else
				{
					if (intTemp >= 100)
					{
						LEDBuf[0] = intTemp / 100;
					}
					else
					{
						LEDBuf[0] = 23;  //������100�� �ص���λ
					}
				}
				//������������Ҫ��ʾ
				if (intTemp >= 10)  //ʮλ
				{
					LEDBuf[1] = intTemp / 10 % 10;
				}
				else
				{
					LEDBuf[1] = 23;  //������10�� �ص�ʮλ
				}
				LEDBuf[2] = intTemp % 10;  //��λ
				LEDBuf[3] = decTemp;  //С��λ
			}
			Start18B20();
		}
	}
}

void Timer0Init(void)		//10����@12.000MHz
{
//	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xF0;		//���ö�ʱ��ʼֵ
	TH0 = 0xD8;		//���ö�ʱ��ʼֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;
	EA = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer0_ISR() interrupt 1
{
	static unsigned char timer0Cnt = 0;
	TR0 = 0;
	TL0 = 0xF0;		//���ö�ʱ��ʼֵ
	TH0 = 0xD8;		//���ö�ʱ��ʼֵ
	Display();
	timer0Cnt++;
	if (timer0Cnt >= 100)
	{
		timer0Cnt = 0;
		flag = 1;
	}
	TR0 = 1;
}