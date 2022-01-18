#include <reg51.h>
#include "display.h"
#include "delay.h"

//函数声明
void EX0_Init(void);
void EX1_Init(void);
void Dis_Service();
unsigned int parameter = 0;

void main()
{
	unsigned int i;
	EX0_Init();
	EX1_Init();
	EA = 1;
	for (i = 0; i < 2000; i++)
	{
		Display();
	}
	while (1)
	{
		Dis_Service();
	}
}

void Dis_Service()
{
	LEDBuf[0] = parameter / 1000;
	LEDBuf[1] = parameter / 100 % 10;
	LEDBuf[2] = parameter / 10 % 10;
	LEDBuf[3] = parameter % 10;
	Display();
}

//外部中断0  初始化
void EX0_Init(void)
{
	IT0 = 1;//设置  下降沿触发  TCON
	EX0 = 1;//IE
}

//外部中断1  初始化
void EX1_Init(void)
{
	IT1 = 1;//设置  下降沿触发  TCON
	EX1 = 1;//IE
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

void EX0_ISR(void) interrupt 0
{
	DelayXms(10);
	if (!INT0)
	{
		parameter++;
		if (parameter > 9999)
			parameter = 0;
	}
}

void EX1_ISR(void) interrupt 2
{
	DelayXms(10);
	if (!INT1)
	{
		parameter--;
		if (parameter > 9999)
			parameter = 9999;
	}
}