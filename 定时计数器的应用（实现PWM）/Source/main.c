#include <reg51.h>

sbit PWM = P1^0;

unsigned char  PWM_Duty = 0;
unsigned char PWM_Cnt;

void Timer0Init(void);
void EX0_Init();

void main()
{
	Timer0Init();
	EX0_Init();
	EA = 1;
	while (1)
	{
		
	}
}

void Timer0Init(void)		//100微秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA = 1;
	TR0 = 1;		//定时器0开始计时
}

void EX0_Init()
{
	IT0 = 1;//下降沿触发
	EX0 = 1;
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
	PWM_Cnt++;
	if (PWM_Cnt >= 100)
	{
		PWM_Cnt = 0;
	}
	if (PWM_Cnt <= PWM_Duty)
	{
		PWM = 1;
	}
	else
		PWM = 0;
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TR0 = 1;
}

void EX0_ISR(void) interrupt 0
{
	static unsigned char PWM_KEY;
	PWM_KEY++;
	switch (PWM_KEY)
	{
		case 1:	PWM_Duty = 25; break;
		case 2:	PWM_Duty = 50; break;
		case 3:	PWM_Duty = 75; break;
		case 4:	PWM_Duty = 80; break;
		case 5:	PWM_Duty = 100; break;
		case 6:	PWM_Duty = 0; PWM_KEY = 0; break;
		default: break;
	}
}