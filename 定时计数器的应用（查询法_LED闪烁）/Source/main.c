#include <reg51.h>

sbit LED = P1^0;
void timer0_Init();

void main()
{
	timer0_Init();
	while (1)
	{
		if (1 == TF0)
		{
			TF0 = 0;
			TH0 = (65536 - 50000) / 256;//重新赋初值
			TL0 = (65536 - 50000) % 256;
			LED = ~LED;
			
		}
	}
}

void timer0_Init()
{
	//1、设置TMOD 确定工作方式 定时/计数   哪一种工作方式 工作方式1   GATE 0
	TMOD = 0X01;
	//2、定时初值的计算  (eg: 50ms  12M)
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	//3、打开定时/计数器
	TR0 = 1;//启动定时计数器
}