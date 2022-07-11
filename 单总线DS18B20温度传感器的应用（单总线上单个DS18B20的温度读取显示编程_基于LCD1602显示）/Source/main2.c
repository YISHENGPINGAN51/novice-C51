#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
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
	LCDInit();    //��ʼ��Һ��
	DelayXms(10);
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
					LCDWriteCmd(0x80);    //д��ַ 80��ʾ��ʼ��ַ
					LCDWriteData('-');    //��ʾ��
					temp = ~temp;  //�����ţ�ȡ����һ��ԭ��
					temp = temp + 1;
					tmp = temp;
					temp = tmp * 0.0625 * 100;  //С���������λ
				}
				else
				{
					LCDWriteCmd(0x80);    //д��ַ 80��ʾ��ʼ��ַ
					LCDWriteData(' ');    //��ʾ��
					tmp = temp;              //����
					temp = tmp * 0.0625 * 100;  //С���������λ
				}
				if (temp >= 10000)//����¶ȴ��ڵ���100��
				{
					LCDWriteCmd(0x82);    //д��ַ 82��ʾ��ʼ��ַ
					LCDWriteData('0' + temp / 10000);    //��λ
					LCDWriteData('0' + temp % 10000 / 1000);    //ʮλ
					LCDWriteData('0' + temp % 1000 / 100);    //��λ
					LCDWriteData('.');    //��ʾ  ��.'
					LCDWriteData('0' + temp % 100 / 10);    //��ʾС����
					LCDWriteData('0' + temp % 10);    //��ʾС����
				}
				else //�¶�С��100
				{
					if (temp >= 1000)//����¶ȴ��ڵ���10��
					{
						LCDWriteCmd(0x82);    //д��ַ 82��ʾ��ʼ��ַ
						LCDWriteData('0' + temp % 10000 / 1000);    //ʮλ
						LCDWriteData('0' + temp % 1000 / 100);    //��λ
						LCDWriteData('.');    //��ʾ  ��.'
						LCDWriteData('0' + temp % 100 / 10);    //��ʾС����
						LCDWriteData('0' + temp % 10);    //��ʾС����
						LCDWriteData(' ');    //���ݶ��룬���ԭ�е���ʾ
					}
					else
					{
						LCDWriteCmd(0x82);    //д��ַ 82��ʾ��ʼ��ַ
						LCDWriteData('0' + temp % 1000 / 100);    //��λ
						LCDWriteData('.');    //��ʾ  ��.'
						LCDWriteData('0' + temp % 100 / 10);    //��ʾС����
						LCDWriteData('0' + temp % 10);    //��ʾС����
						LCDWriteData(' ');    //���ݶ��룬���ԭ�е���ʾ
						LCDWriteData(' ');    //���ݶ��룬���ԭ�е���ʾ
					}
				}
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
	timer0Cnt++;
	if (timer0Cnt >= 100)
	{
		timer0Cnt = 0;
		flag = 1;
	}
	TR0 = 1;
}