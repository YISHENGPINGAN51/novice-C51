#include <reg51.h>
#include "display.h"

void Timer0Init(void);
void display_Service();
void Timer1Init(void);

unsigned int dataNum;
unsigned int timerCnt;
void main()
{
	Timer0Init();
	Timer1Init(); 
	EA = 1;		//中断总开关
	while (1)
	{
		display_Service();
	}
}

void display_Service()
{
	LEDBuf[0] = dataNum / 1000;
	LEDBuf[1] = dataNum / 100 % 10;
	LEDBuf[2] = dataNum / 10 % 10;
	LEDBuf[3] = dataNum % 10;
}

void Timer0Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;		//定时器0的中断开关
//	EA = 1;		//中断总开关
	TR0 = 1;		//定时器0开始计时
}

void Timer1Init(void)		//@12.000MHz
{
	TMOD &= 0x0F;		//设置计数器模式  GATE  C/T  M1  M0  0  1  0  1
	TMOD |= 0x50;		//设置计数器模式
	TL1 = 0;		//设置定时初值
	TH1 = 0;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	ET1 = 1;		//定时器1的中断开关
//	EA = 1;		//中断总开关
	TR1 = 1;		//定时器1开始计数
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
	timerCnt++;
	if (timerCnt >= 1000)//1S时间到
	{
		TR1 = 0;
		timerCnt = 0;
		dataNum = TH1 * 256 + TL1;
		TH1 = TL1 = 0;
		TR1 = 1;
	}
	Display();
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TR0 = 1;
}