#include "uart2.h"
#include "uart.h"

void Uart2Init(void)		//9600bps@11.0592MHz
{
	AUXR &= 0xF7;		//波特率不倍速
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xFB;		//定时器时钟12T模式
	BRT = 0xFD;		//设置定时重载值
	AUXR |= 0x10;		//启动独立波特率发射器
	IE2 = 0x01;             //使能UART2中断
}

void sendByte2(unsigned char dat)
{
	S2BUF = dat;
	while (!(S2CON & S2TI));
	S2CON &= ~S2TI;     //Clear transmit interrupt flag
}

//串口2发送字符串
void sendString2(unsigned char *dat)//Hello World!
{
	while (*dat != '\0')
	{
		sendByte2(*dat++);
	}
}

#if 1
char putchar(char c)
{
	sendByte2(c);
	return c;
}
#endif

void uart2_ISR() interrupt 8
{
	unsigned char dat;
	if (S2CON & S2RI)
	{
		S2CON &= ~S2RI;     //Clear receive interrupt flag
		dat = S2BUF;        //串口2读取一个字节
		sendByte(dat);      //通过串口1转发
	}
}
