#include <reg51.h>
#include "display.h"

void Timer0Init(void);
void EX0_Init();
void EX1_Init();
void display_Service();

unsigned int numCnt = 0;//参数
unsigned char temp0;//用于显示的中间变量
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;

void main()
{
	EX0_Init();
	EX1_Init();
	Timer0Init();
	EA = 1;//中断总开关
	while (1)
	{
		display_Service();
	}
}

void display_Service()
{
	temp0 = numCnt / 1000;
	temp1 = numCnt / 100 % 10;
	temp2 = numCnt / 10 % 10;
	temp3 = numCnt % 10;
	if (numCnt < 1000)
		LEDBuf[0] = 23;
	else
		LEDBuf[0] = temp0;
	if (numCnt < 100)
		LEDBuf[1] = 23;
	else
		LEDBuf[1] = temp1;
	if (numCnt < 10)
		LEDBuf[2] = 23;
	else
		LEDBuf[2] = temp2;
	LEDBuf[3] = temp3;
}
void EX0_Init()
{
	IT0 = 1;//触发方式  下降沿
	EX0 = 1;
}

void EX1_Init()
{
	IT1 = 1;//触发方式  下降沿
	EX1 = 1;
}

void Timer0Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;		//定时器0的终端开关
//	EA = 1;		//中断总开关
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
	Display();
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TR0 = 1;
}

void EX0_ISR(void) interrupt 0
{
	EX0 = 0;
	numCnt++;
	if (numCnt > 9999)
	{
		numCnt = 0;
	}
	EX0 = 1;
}

void EX1_ISR(void) interrupt 2
{
	EX0 = 0;
	numCnt--;
	if (numCnt > 9999)
	{
		numCnt = 9999;
	}
	EX0 = 1;
}