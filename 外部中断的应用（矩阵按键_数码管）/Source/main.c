#include <reg51.h>
#include "display.h"
#include "delay.h"
#include "Key.h"

unsigned char KeyNum;
unsigned char KeyPressFlag;
//函数声明
void EX0_Init(void);
void Dis_Service();

void main()
{
	EX0_Init();
	P0 = 0x0f;
	while (1)
	{
		if (1 == KeyPressFlag)
		{
			KeyPressFlag = 0;
			KeyNum = Key_Scan();
//		P0 = 0x0f;//线反转法不需要，行列扫描需要
		}
		Dis_Service();
		Display();
	}
}

void Dis_Service()
{
	LEDBuf[0] = 23;
	LEDBuf[1] = 23;
	LEDBuf[2] = 23;
	LEDBuf[3] = KeyNum;
}

//外部中断0  初始化
void EX0_Init(void)
{
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
	KeyPressFlag = 1;
}