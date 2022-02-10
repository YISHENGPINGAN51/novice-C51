#include <reg51.h>
#include "delay.h"
#include "uart.h"

sbit LED = P1^0;

void uart_service(unsigned char *buf);
void Timer0Init(void);

void main()
{
	Timer0Init();
	UartInit();
	EA = 1;
	printf("Wait for Serial Communication Test Start.\r\n");
	printf("Please Send a string of data:\r\n");
	while (1)
	{
		uart_service(recv_buf);
	}
}

void uart_service(unsigned char *buf)
{
	unsigned char recv_move_index;
	if (recv_flag)
	{
		recv_flag = 0;
		start_timer = 0;//关定时器
		sendString(buf);//处理数据
		while ((recv_cnt >= 5) && (recv_move_index <= recv_cnt))
		{
			if ((buf[recv_move_index + 0] == 0x55) && (buf[recv_move_index + 1] == 0xAA) && (buf[recv_move_index + 2] == 0x55))
			{
				if ((buf[recv_move_index + 3] == 0x01) && (buf[recv_move_index + 4] == 0x02))
				{
					LED = 0;
				}
				if ((buf[recv_move_index + 3] == 0x02) && (buf[recv_move_index + 4] == 0x01))
				{
					LED = 1;
				}
				break;
			}
			recv_move_index++;
		}
		recv_cnt = 0;
		clr_recvbuffer(buf);//清除缓冲buffer
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
	if (1 == start_timer)
	{
		recv_timer_cnt++;//1、累加定时时间计数器
		if (recv_timer_cnt > MAX_REV_TIME)//2、判断定时时间是否超过了设定的最大的阈值，
			                                //超过则说明等待一段时间后没有新的数据到，
		                                  //我们判断一包数据接收完毕
		{
			recv_timer_cnt = 0;//3、清除定时计数器  处理数据  清除buffer（放到数据处理之后）
//			recv_cnt = 0;
			recv_flag = 1;
			
		}
	}
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TR0 = 1;
}