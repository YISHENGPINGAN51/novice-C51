#include <reg51.h>
#include "delay.h"
#include "uart.h"
#include "display.h"

void Timer0Init(void);

void main()
{
	Timer0Init();
	UartInit();
	EA = 1;
	printf("Wait for Serial Communication Test Start.\r\n");
	printf("Please Send a Command:\r\n");
	DelayXms(10);
	while (1)
	{
		if (recv_flag == 1)
		{
			recv_flag = 0;		
			switch (recv_buf[0])
			{
				case 1:
					LEDBuf[0] = 23;
					LEDBuf[1] = 23;
					LEDBuf[2] = recv_buf[1] >> 4;
					LEDBuf[3] = recv_buf[1] & 0x0F;
					break;
				case 2:
					LEDBuf[0] = recv_buf[1] >> 4;
					LEDBuf[1] = recv_buf[1] & 0x0F;
					LEDBuf[2] = recv_buf[2] >> 4;
					LEDBuf[3] = recv_buf[2] & 0x0F;
					break;
				case 3:
					LEDBuf[0] = recv_buf[1] >> 4;
					LEDBuf[1] = recv_buf[1] & 0x0F;
					LEDBuf[2] = recv_buf[2] >> 4;
					LEDBuf[3] = recv_buf[2] & 0x0F;
					break;
				default:
					break;
			}
			clr_recvbuffer(recv_buf);
		}
	}
}

void Timer0Init(void)		//1毫秒@11.0592MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	TR0 = 1;		//定时器0开始计时
}

void timer0_ISR() interrupt 1
{
	TR0 = 0;
	Display();
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TR0 = 1;
}