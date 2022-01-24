#include <reg51.h>
#include <intrins.h>
#include "display.h"

void Timer0Init(void);
void Timer1Init(void);

unsigned char secCnt;
unsigned char sec = 60;
unsigned char timerCnt;
unsigned char temp = 0xfe;

void main()
{
	Timer0Init();
	Timer1Init();
	EA = 1;
	while (1)
	{
		LEDBuf[0] = 23;
		LEDBuf[1] = 23;
		LEDBuf[2] = sec / 10;
		LEDBuf[3] = sec % 10;
	}
}

void Timer0Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	TR0 = 1;		//定时器0开始计时
}

void Timer1Init(void)		//50毫秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0xB0;		//设置定时初值
	TH1 = 0x3C;		//设置定时初值
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
	TR0 = 0;
	Display();
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TR0 = 1;
}

void timer1_ISR(void) interrupt 3
{
	TR1 = 0;
	secCnt++;
	timerCnt++;
	if (timerCnt >= 20)
	{
		timerCnt = 0;
		P1 = temp;
		temp = _crol_(temp, 1);
	}
	if (secCnt >= 20)
	{
		secCnt = 0;
		sec--;
		if (sec > 60)
		{
			sec = 60;
		}
	}
	TL1 = 0xB0;		//设置定时初值
	TH1 = 0x3C;		//设置定时初值
	TR1 = 1;
}