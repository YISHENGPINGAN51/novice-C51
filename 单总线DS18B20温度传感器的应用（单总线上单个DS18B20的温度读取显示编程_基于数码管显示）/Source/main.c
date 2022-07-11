#include <reg51.h>
#include "delay.h"
#include "display.h"
#include "DS18B20.h"

void Timer0Init(void);
unsigned char flag;

void main()
{
	unsigned char ack;
	int temp;//保存接收温度数据
	int intTemp, decTemp;//分离温度数据的整数部分和小数部分
	
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
				intTemp = temp >> 4;//保留整数部分
				decTemp = temp & 0x0f;
				decTemp = (decTemp * 10) / 16;//*0.0625  放大10倍  小数点后1位
				
				if (intTemp < 0)
				{
					intTemp = -intTemp;
					LEDBuf[0] = 22;
					if (decTemp % 10 != 0)  //DS18B20步进0.5无问题
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
						LEDBuf[0] = 23;  //不大于100℃ 关掉百位
					}
				}
				//无论正负都需要显示
				if (intTemp >= 10)  //十位
				{
					LEDBuf[1] = intTemp / 10 % 10;
				}
				else
				{
					LEDBuf[1] = 23;  //不大于10℃ 关掉十位
				}
				LEDBuf[2] = intTemp % 10;  //个位
				LEDBuf[3] = decTemp;  //小数位
			}
			Start18B20();
		}
	}
}

void Timer0Init(void)		//10毫秒@12.000MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xF0;		//设置定时初始值
	TH0 = 0xD8;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA = 1;
	TR0 = 1;		//定时器0开始计时
}

void Timer0_ISR() interrupt 1
{
	static unsigned char timer0Cnt = 0;
	TR0 = 0;
	TL0 = 0xF0;		//设置定时初始值
	TH0 = 0xD8;		//设置定时初始值
	Display();
	timer0Cnt++;
	if (timer0Cnt >= 100)
	{
		timer0Cnt = 0;
		flag = 1;
	}
	TR0 = 1;
}