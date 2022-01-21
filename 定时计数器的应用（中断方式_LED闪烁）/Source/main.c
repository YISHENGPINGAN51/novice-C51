#include <reg51.h>

sbit LED = P1^0;
unsigned char timer0Cnt;
void Timer0Init(void);

void main()
{
	Timer0Init();
	while (1);
}

void Timer0Init(void)		//50毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式  GATE  C/T  M1  M0
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xB0;		//设置定时初值  (65535 - 50000) % 256
	TH0 = 0x3C;		//设置定时初值  (65535 - 50000) / 256
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA = 1;
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
void timer_ISR(void) interrupt 1
{
	TR0 = 0;
	TL0 = 0xB0;		//设置定时初值  (65535 - 50000) % 256
	TH0 = 0x3C;		//设置定时初值  (65535 - 50000) / 256
	timer0Cnt++;
	if (timer0Cnt >= 10)
	{
		LED = ~LED;
	}
	TR0 = 1;
}