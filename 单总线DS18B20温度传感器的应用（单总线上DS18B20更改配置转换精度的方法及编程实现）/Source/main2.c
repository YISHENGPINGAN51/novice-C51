#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"

unsigned char flag = 0;    //1s定时标志

void Timer0Init(void);		//10毫秒@12.000MHz

void main()
{
	bit ack;
	int temp;    //读取到的当前温度值
	float tmp;
	Timer0Init();		//10毫秒@12.000MHz
	EA = 1;    //开总中断
//	Config18B20(0x1F);//配置成9位  0.5
	Start18B20();    //启动DS18B20
	LCDInit();    //初始化液晶
	DelayXms(10);
	while (1)
	{
		if (flag)    //每秒更新一次温度
		{
			flag = 0;
			ack = Read18B20(&temp);    //读取当前温度
			if (ack)                      //读取成功时，刷新当前温度显示
			{
				if (temp < 0)       //当温度值为负数
				{
					LCDWriteCmd(0x80);    //写地址 80表示初始地址
					LCDWriteData('-');    //显示负
					temp = ~temp;  //补码存放，取反加一求原码
					temp = temp + 1;
					tmp = temp;
					temp = tmp * 0.0625 * 100;  //小数点后保留两位
				}
				else
				{
					LCDWriteCmd(0x80);    //写地址 80表示初始地址
					LCDWriteData(' ');    //显示空
					tmp = temp;              //正数
					temp = tmp * 0.0625 * 100;  //小数点后保留两位
				}
				if (temp >= 10000)//如果温度大于等于100℃
				{
					LCDWriteCmd(0x82);    //写地址 82表示初始地址
					LCDWriteData('0' + temp / 10000);    //百位
					LCDWriteData('0' + temp % 10000 / 1000);    //十位
					LCDWriteData('0' + temp % 1000 / 100);    //个位
					LCDWriteData('.');    //显示  ‘.'
					LCDWriteData('0' + temp % 100 / 10);    //显示小数点
					LCDWriteData('0' + temp % 10);    //显示小数点
				}
				else //温度小于100
				{
					if (temp >= 1000)//如果温度大于等于10℃
					{
						LCDWriteCmd(0x82);    //写地址 82表示初始地址
						LCDWriteData('0' + temp % 10000 / 1000);    //十位
						LCDWriteData('0' + temp % 1000 / 100);    //个位
						LCDWriteData('.');    //显示  ‘.'
						LCDWriteData('0' + temp % 100 / 10);    //显示小数点
						LCDWriteData('0' + temp % 10);    //显示小数点
						LCDWriteData(' ');    //数据对齐，清除原有的显示
					}
					else
					{
						LCDWriteCmd(0x82);    //写地址 82表示初始地址
						LCDWriteData('0' + temp % 1000 / 100);    //个位
						LCDWriteData('.');    //显示  ‘.'
						LCDWriteData('0' + temp % 100 / 10);    //显示小数点
						LCDWriteData('0' + temp % 10);    //显示小数点
						LCDWriteData(' ');    //数据对齐，清除原有的显示
						LCDWriteData(' ');    //数据对齐，清除原有的显示
					}
				}
				Start18B20();    //重新启动下一次转换
			}
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
	ET0 = 1;    //使能T0中断
	TR0 = 1;		//定时器0开始计时
}

void Timer0_ISR() interrupt 1
{
	static unsigned char timer0Cnt = 0;
	TR0 = 0;
	TL0 = 0xF0;		//设置定时初始值
	TH0 = 0xD8;		//设置定时初始值
	timer0Cnt++;
	if (timer0Cnt >= 100)
	{
		timer0Cnt = 0;
		flag = 1;
	}
	TR0 = 1;
}