#include "uart.h"

unsigned char recv_buf[MAX_REV_NUM];
unsigned char recv_flag = 0;
unsigned char recv_length;

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率  SM0  SM1  SM2  REN  TB8  RB8  TI  RI
	                //                    0    1    0    1    0    0   0   0
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	ES = 1;
	EA = 1;
	TR1 = 1;		//启动定时器1
}

void sendByte(unsigned char dat)
{
	SBUF = dat;
	while (!TI);
	TI = 0;
}

void sendString(unsigned char *dat)//Hello World!
{
	while (*dat != '\0')
	{
		sendByte(*dat++);
	}
}

char putchar(char c)
{
	sendByte(c);
	return c;
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

void uart_ISR() interrupt 4
{
	static unsigned char recv_cnt = 0;
	unsigned char temp;
	if (RI)
	{
		RI = 0;
		temp = SBUF;
		if (temp != 0xFF)
		{
			recv_buf[recv_cnt++] = temp;
			if (recv_cnt > MAX_REV_NUM)
			{
				recv_cnt = MAX_REV_NUM;
			}
		}
		else
		{
			recv_flag = 1;
			recv_length = recv_cnt;
			recv_cnt = 0;
		}
	}
}

//void uart_ISR() interrupt 4
//{
//	static unsigned char recv_cnt = 0;
//	if (RI)
//	{
//		RI = 0;
//		recv_buf[recv_cnt++] = SBUF;
//		if (REV_CNT == recv_cnt)
//		{
//			recv_flag = 1;
//			recv_cnt = 0;
//		}
//	}
//}