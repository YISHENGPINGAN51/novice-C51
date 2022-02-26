#include <reg51.h>
#include "delay.h"
#include "uart.h"
#include "CRC16.h"

sbit LED = P1^0;
sbit BEEP = P3^7;

unsigned int led_data;
unsigned int beep_data;
unsigned int led_cnt;
unsigned int beep_cnt;

#define LOCAL_ADDRESS 0x01

void Timer0Init(void);

void main()
{
	unsigned char i;
	unsigned int crc;
	unsigned char crch, crcl;
	Timer0Init();
	UartInit();
	EA = 1;
	while (1)
	{
		if (recv_flag)
		{
			recv_flag = 0;
			start_timer = 0;//关定时器
			//校验本机地址，是本机的，则接收处理，否则退出
			if (recv_buf[0] != LOCAL_ADDRESS)
			{
				return;
			}
			//CRC16校验，校验正确，我们才处理，否则直接返回，并给出错误码
			crc = GetCRC16(recv_buf, recv_cnt - 2);
			crch = crc >> 8;
			crcl = crc & 0xFF;
			if ((recv_buf[recv_cnt - 2] != crch) || (recv_buf[recv_cnt - 1] != crcl))
			{
				recv_buf[1] = recv_buf[1] | 0x80;
				crc = GetCRC16(recv_buf, recv_cnt - 2);
				recv_buf[4] = crc & 0xFF;
				recv_buf[5] = crc >> 8;
				for (i = 0; i < recv_cnt; i++)
				{
					sendByte(recv_buf[i]);
				}
				return;
			}
			switch (recv_buf[1])
			{
				case 1:
					led_data = recv_buf[2];
					led_data = led_data << 8;
					led_data = led_data + recv_buf[3];
					led_cnt = 0;//目的是使LED点亮上述接收的数据的时间
					break;
				case 2:
					beep_data = recv_buf[2];
					beep_data = beep_data << 8;
					beep_data = beep_data + recv_buf[3];
					beep_cnt = beep_data;
					break;
				default: break;
			}
			//sendString(recv_buf);//处理数据
			clr_recvbuffer(recv_buf);//清除缓冲buffer
			recv_cnt = 0;
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
	if (1 == start_timer)
	{
		recv_timer_cnt++;//1、累加定时时间计数器
		if (recv_timer_cnt > MAX_REV_TIME)//2、判断定时时间是否超过了设定的最大的阈值，
			                                //超过则说明等待一段时间后没有新的数据到，
		                                  //我们判断一包数据接收完毕
		{
			recv_timer_cnt = 0;//3、清除定时计数器  处理数据  清除buffer（放到数据处理之后）
			recv_flag = 1;
		}
	}
	if (led_cnt < led_data)
	{
		led_cnt++;
		LED = 0;
	}
	else
	{
		LED = 1;
	}
	if (beep_cnt != 0)
	{
		beep_cnt--;
		BEEP = ~BEEP;
	}
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TR0 = 1;
}