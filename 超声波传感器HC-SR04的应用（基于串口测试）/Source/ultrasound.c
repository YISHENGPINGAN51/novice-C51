#include "ultrasound.h"
#include <intrins.h>
#include <stdio.h>

void Timer0Init(void)		//11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x09;		//方式一		Gate置1	测脉宽		P3.2引脚	INT0脚
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0并不会开始启动，启动由P3.2出现高电平才开始真正的启动
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
	while(!Echo_P32)//等待低电平结束
	{
		t++;
		_nop_();
		if (t > 10000)//超时处理，防止硬件出错，进入死循环
		{
			printf("1\r\n");
			return -1;//出错
		}
	}
	t = 0;
	while(Echo_P32)//等待高电平结束
	{
		t++;
		_nop_();
		if (t > 20000)//超时处理，防止硬件出错，进入死循环
		{
			printf("2\r\n");
			return -2;//出错
		}
	}
	timeH = TH0;//取高电平的计时时间
	timeL = TL0;
	TH0 = 0;//重置初值
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