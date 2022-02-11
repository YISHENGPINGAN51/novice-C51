#include "uart.h"

unsigned char recv_buf[MAX_REV_NUM];
unsigned char recv_cnt;
unsigned char recv_flag;
unsigned char machine_step = 0;
unsigned int led_data;
unsigned int beep_data;
unsigned int led_cnt;
unsigned int beep_cnt;
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

void clr_recvbuffer(unsigned char *buf)
{
	unsigned char i;
	for(i = 0; i < MAX_REV_NUM; i++)
	{
		buf[i] = 0;
	}
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
	if (RI)
	{
		RI = 0;
		switch(machine_step)
		{
			case 0:
				recv_buf[0] = SBUF;
				if (recv_buf[0] == 0xAA)
				{
					machine_step = 1;
				}
				else
				{
					machine_step = 0;
				}
				break;		
			case 1:
				recv_buf[1] = SBUF;
				if (recv_buf[1] == 0x55)
				{
					machine_step = 2;
					recv_cnt = 2;
				}
				else
				{
					machine_step = 0;
				}
				break;
			case 2:
				recv_buf[recv_cnt] = SBUF;
				recv_cnt++;
				if (recv_cnt > 4)
				{
					machine_step = 3;
				}
				else
				{
					machine_step = 2;
				}
				break;
			case 3:
				recv_buf[recv_cnt] = SBUF;
				if (recv_buf[recv_cnt] == 0x0D)
				{
					switch (recv_buf[2])
					{
						case 1:
							led_data = recv_buf[3];
							led_data = led_data << 8;
							led_data = led_data + recv_buf[4];
							led_cnt = 0;//目的是使LED点亮上述接收的数据的时间
							break;
						case 2:
							beep_data = recv_buf[3];
							beep_data = beep_data << 8;
							beep_data = beep_data + recv_buf[4];
							beep_cnt = beep_data;
							break;
						default: break;
					}
					machine_step = 0;
					recv_cnt = 0;
					recv_flag = 1;//接收完一串数据，标志位置1
				}
				break;
			default: break;
		}
	}
	if (TI)
	{
		TI = 0;
		
	}
}