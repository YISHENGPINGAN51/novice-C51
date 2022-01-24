#include <reg51.h>
#include "display.h"

sbit LED = P1^0;

void Timer0Init(void);
void display_Service();

unsigned int num = 4534;
unsigned int systemTimer = 0;
unsigned char systemFlag = 1;

void main()
{
	Timer0Init();
	do
	{
		if (systemTimer % 50 == 0)
		{
			LED = ~LED;
		}
	}	while (systemTimer < 5000);//5S 5000ms/1ms
	systemFlag = 0;
	LED = 1;
	
	while (1)
	{
		display_Service();
	}
}

void display_Service()
{
	LEDBuf[0] = num / 1000;
	LEDBuf[1] = num / 100 % 10;
	LEDBuf[2] = num / 10 % 10;
	LEDBuf[3] = num % 10;
}
void Timer0Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;		//定时器0的终端开关
	EA = 1;		//中断总开关
	TR0 = 1;		//定时器0开始计时
}

/*****************************************************************
1、中断服务函数一定是一个没有返回值的函数
2、中断服务函数一定是没有参数的函数
3、中断服务函数函数名后跟关键字 interrupt
4、interrupt n 0 - 4  5个中断源  8*n + 0003H
0003H INT0    000BH T0    0013H INT1    001BH T1    0023H ES
5、中断服务函数不能被主程序或其他程序所调用
6、n后面跟using m (0 - 3)工作寄存器组
*****************************************************************/
void timer0_ISR(void) interrupt 1
{
	TR0 = 0;
	if (1 == systemFlag)
	{
		systemTimer++;
	}
	Display();
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TR0 = 1;
}