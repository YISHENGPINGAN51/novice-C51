#include "ultrasound.h"
#include <intrins.h>
#include <stdio.h>

void Timer0Init(void)		//11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x09;		//��ʽһ		Gate��1	������		P3.2����	INT0��
	TL0 = 0;		//���ö�ʱ��ֵ
	TH0 = 0;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0�����Ὺʼ������������P3.2���ָߵ�ƽ�ſ�ʼ����������
}

void ultra_init(void)
{
	Trig_P17 = 0;
	Echo_P32 = 0;
	Timer0Init();
}

int get_distance(void)
{
	unsigned char i;
	unsigned char timeH, timeL;
	unsigned int time;
	unsigned int distance;
	unsigned int t;
	
	Trig_P17 = 1;
	for (i = 0; i < 10; i++)
	{
		_nop_();
	}
	Trig_P17 = 0;
	
	Echo_P32 = 1;
	while(!Echo_P32)//�ȴ��͵�ƽ����
	{
		t++;
		_nop_();
		if (t > 10000)//��ʱ������ֹӲ������������ѭ��
		{
			printf("1\r\n");
			return -1;//����
		}
	}
	t = 0;
	while(Echo_P32)//�ȴ��ߵ�ƽ����
	{
		t++;
		_nop_();
		if (t > 20000)//��ʱ������ֹӲ������������ѭ��
		{
			printf("2\r\n");
			return -2;//����
		}
	}
	timeH = TH0;//ȡ�ߵ�ƽ�ļ�ʱʱ��
	timeL = TL0;
	TH0 = 0;//���ó�ֵ
	TL0 = 0;
	
	time = timeH * 256 + timeL;
	if (time > 12000)
	{
		printf("3\r\n");
		return -3;
	}
	distance = time * 1.7 / 100;// dis = t * 340m/s /2 = t * 170m/s = t * 17000 cm/10^6us
	
	return distance;
}