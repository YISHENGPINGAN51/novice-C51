#include <reg51.h>
#include "delay.h"
#include "display.h"
#include "DS18B20.h"

unsigned char flag = 0;    //1s��ʱ��־

void Timer0Init(void);		//10����@12.000MHz

void main()
{
	bit ack;
	int temp;    //��ȡ���ĵ�ǰ�¶�ֵ
	float tmp;
	Timer0Init();		//10����@12.000MHz
	EA = 1;    //�����ж�
	Start18B20();    //����DS18B20
	while (1)
	{
		if (flag)    //ÿ�����һ���¶�
		{
			flag = 0;
			ack = Read18B20(&temp);    //��ȡ��ǰ�¶�
			if (ack)                      //��ȡ�ɹ�ʱ��ˢ�µ�ǰ�¶���ʾ
			{
				if (temp < 0)       //���¶�ֵΪ����
				{
					LEDBuf[0] = 22;  //��ʾ��
					temp = ~temp;  //�����ţ�ȡ����һ��ԭ��
					temp = temp + 1;
					tmp = temp;
					temp = tmp * 0.0625 * 10;  //С�������һλ    �Ŵ���10��
				}
				else
				{
					tmp = temp;              //����
					temp = tmp * 0.0625 * 10;  //С�������һλ
					if (temp >= 1000)//����¶ȴ��ڵ���100��
					{
						LEDBuf[0] = temp / 1000;
					}
					else
					{
						LEDBuf[0] = 23;
					}
				}
		    if (temp >= 100)//����¶ȴ��ڵ���10��
				{
					LEDBuf[1] = temp / 100 % 10;
				}
				else
				{
					LEDBuf[1] = 23;
				}
				LEDBuf[2] = temp / 10 % 10;
				LEDBuf[3] = temp % 10;//С��λ
				Start18B20();    //����������һ��ת��
			}
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
	ET0 = 1;    //ʹ��T0�ж�
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