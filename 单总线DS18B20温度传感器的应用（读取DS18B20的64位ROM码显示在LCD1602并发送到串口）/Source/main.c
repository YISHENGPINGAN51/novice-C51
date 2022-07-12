#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"

void Timer0Init(void);
unsigned char flag;

void main()
{
	unsigned char ack;
	int temp;//��������¶�����
	int intTemp, decTemp;//�����¶����ݵ��������ֺ�С������
	unsigned char str[12];//��������ת���ɵ��ַ���   ASCII
	unsigned char len;
	
	LCDInit();
	Timer0Init();
	Start18B20();
	DelayXms(10);
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
				len = IntegerToStr(intTemp, str);
				str[len++] = '.';
				
				decTemp = (decTemp * 100) / 16;//*0.0625
				str[len++] = decTemp / 10 + '0';//С������
				str[len++] = decTemp % 10 + '0';
				while (len < 6)
				{
					str[len++] = ' ';
				}
				str[len] = '\0';
				LCDShowStr(0, 0, str);
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
	timer0Cnt++;
	if (timer0Cnt >= 100)
	{
		timer0Cnt = 0;
		flag = 1;
	}
	TR0 = 1;
}