#include <reg51.h>
#include "display.h"

void Timer0Init(void);
void Timer1Init(void);
void showNormal();
void EX0_Init();
void EX1_Init();
void showSec();
void showMin();
void showHour();

unsigned char timerCnt;
unsigned char sec;
unsigned char min;
unsigned char hour;
unsigned char state = 0;

void main()
{
	EX0_Init();
	EX1_Init();
	Timer0Init();
	Timer1Init();
	EA = 1;
	while (1)
	{
		switch (state)
		{
			case 0: TR0 = 1; showNormal(); break;//正常时钟状态
			case 1: showSec(); break;//调秒
			case 2: showMin(); break;//调分
			case 3: showHour(); break;//调时
			default: break;
		}
	}
}

void showNormal()
{
	LEDBuf[0] = hour / 10;
	LEDBuf[1] = hour % 10;
	LEDBuf[2] = min / 10;
	LEDBuf[3] = min % 10;
}

void showSec()
{
	LEDBuf[0] = 23;
	LEDBuf[1] = 23;
	LEDBuf[2] = sec / 10;
	LEDBuf[3] = sec % 10;
}

void showMin()
{
	LEDBuf[0] = min / 10;
	LEDBuf[1] = min % 10;
	LEDBuf[2] = 23;
	LEDBuf[3] = 23;
}

void showHour()
{
	LEDBuf[0] = hour / 10;
	LEDBuf[1] = hour % 10;
	LEDBuf[2] = 23;
	LEDBuf[3] = 23;
}

void EX0_Init()
{
	IT0 = 1;
	EX0 = 1;
}

void EX1_Init()
{
	IT1 = 1;
	EX1 = 1;
}

void Timer0Init(void)		//50毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xB0;		//设置定时初值
	TH0 = 0x3C;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
//	TR0 = 1;		//定时器0开始计时
}

void Timer1Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	ET1 = 1;
	TR1 = 1;		//定时器1开始计时
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
	if (timerCnt >= 20)//20次50ms中断，即1S时间到
	{
		timerCnt = 0;
		sec++;
		if (sec >= 60)
		{
			sec = 0;
			min++;
			if (min >= 60)
			{
				min = 0;
				hour++;
				if (hour >= 23)
				{
					hour = 0;
				}
			}
		}
	}
	TL0 = 0xB0;		//设置定时初值
	TH0 = 0x3C;		//设置定时初值
}

void timer1_ISR(void) interrupt 3
{
	TR1 = 0;
	Display();
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TR1 = 1;
}

void EX0_ISR() interrupt 0
{
	TR0 = 0;
	state++;
	if (state > 3)
	{
		state = 0;
	}
}

void EX1_ISR() interrupt 2
{
	switch (state)
	{
		case 0: break;
		case 1: sec++; if (sec >= 60) sec = 0; break;
		case 2: min++; if (min >= 60) min = 0; break;
		case 3: hour++; if (hour >= 23) hour = 0; break;
		default: break;
	}
}