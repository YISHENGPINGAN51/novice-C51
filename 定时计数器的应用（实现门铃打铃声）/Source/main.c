#include <reg51.h>
#include "Key.h"

sbit DoorBell = P3^7;

void Timer0Init(void);
void Key_Service();

unsigned int timerCnt = 0;
unsigned char uc500Hz = 0;
unsigned char uc700Hz = 0;
unsigned char flag = 0;
void main()
{
	Timer0Init();
	while (1)
	{
		Key_Service();
	}
}

void Key_Service()
{
	switch (Key_Scan())
	{
		case 1: TR0 = ~TR0; break;
		case 2: break;
		case 3: break;
		case 4: break;
		default: break;
	}
}

void Timer0Init(void)		//250微秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x06;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA = 1;
//	TR0 = 1;		//定时器0开始计时
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
	timerCnt++;
	if (timerCnt >= 2000)
	{
		timerCnt = 0;
		flag = ~flag;
	}
	if (!flag)
	{
		uc700Hz++;
		if (uc700Hz >= 3)
		{
			uc700Hz = 0;
			DoorBell = ~DoorBell;
		}
	}
	if (flag)
	{
		uc500Hz++;
		if (uc500Hz >= 4)
		{
			uc500Hz = 0;
			DoorBell = ~DoorBell;
		}
	}
	TL0 = 0x06;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
}