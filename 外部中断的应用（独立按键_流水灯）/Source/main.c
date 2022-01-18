#include <reg51.h>
#include "delay.h"
#include <intrins.h>

unsigned char run = 0;//默认流水灯是停止的
unsigned char dir = 1;//默认正向流水灯

void EX0_Init(void);

void main()
{
	unsigned char temp = 0xfe;
	EX0_Init();
	while (1)
	{
		if (run)
		{
			P1 = temp;
			if (dir)
			{
				temp = _crol_(temp, 1);
			}
			else
			{
				temp = _cror_(temp, 1);
			}
			DelayXms(1000);
		}
	}
}

//外部中断0  初始化
void EX0_Init(void)
{
	//1、设置触发方式  外部中断0
	IT0 = 1;//设置  下降沿触发  TCON
	EX0 = 1;//IE
	EA = 1;
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
	switch (P2 & 0x0f)
	{
		case 0x0e: run = 1; break;
		case 0x0d: run = 0; break;
		case 0x0b: dir = 1; break;
		case 0x07: dir = 0; break;
		default: break;
	}
}














//unsigned char run = 0;//默认流水灯是停止的
//unsigned char dir = 1;//默认正向流水灯
//unsigned char LEDBuf[] = { 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f };

//void EX0_Init(void);

//void main()
//{
////	unsigned char temp = 0xfe;
//	unsigned char i = 0;
//	EX0_Init();
//	while (1)
//	{
//		if (run)
//		{
////			P1 = temp;
//			if (dir)
//			{
////				temp = _crol_(temp, 1);
//				for (i = 0; i <= 7; i++)
//				{
//					P1 = LEDBuf[i];
//					DelayXms(1000);
//				}
//			}
//			else
//			{
////				temp = _cror_(temp, 1);
//				for (i = 7; i > 0; i--)
//				{
//					P1 = LEDBuf[i];
//					DelayXms(1000);
//				}
//			}
////			DelayXms(1000);
//		}
//	}
//}

////外部中断0  初始化
//void EX0_Init(void)
//{
//	//1、设置触发方式  外部中断0
//	IT0 = 1;//设置  下降沿触发  TCON
//	EX0 = 1;//IE
//	EA = 1;
//}

///*****************************************************************
//1、中断服务函数一定是一个没有返回值的函数
//2、中断服务函数一定是没有参数的函数
//3、中断服务函数函数名后跟关键字 interrupt
//4、interrupt n 0 - 4  5个中断源  8*n + 0003H
//0003H INT0    000BH T0    0013H INT1    001BH T1    0023H ES
//5、中断服务函数不能被主程序或其他程序所调用
//6、n后面跟using m (0 - 3)工作寄存器组
//*****************************************************************/

//void EX0_ISR(void) interrupt 0
//{
//	switch (P2 & 0x0f)
//	{
//		case 0x0e: run = 1; break;
//		case 0x0d: run = 0; break;
//		case 0x0b: dir = 1; break;
//		case 0x07: dir = 0; break;
//		default: break;
//	}
//}