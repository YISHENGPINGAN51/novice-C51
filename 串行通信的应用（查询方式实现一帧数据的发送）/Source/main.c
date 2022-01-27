#include <reg51.h>
#include "delay.h"

void UartInit(void);
void sendByte(unsigned char dat);

void main()
{
	UartInit();
	while (1)
	{
		sendByte('8');
		DelayXms(1000);
	}
}

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率  SM0  SM1  SM2  REN  TB8  RB8  TI  RI
	                //                    0    1    0    1    0    0   0   0
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void sendByte(unsigned char dat)
{
	SBUF = dat;//  10位  异步串口通信  0 88H 1
	while (!TI);
	TI = 0;
}