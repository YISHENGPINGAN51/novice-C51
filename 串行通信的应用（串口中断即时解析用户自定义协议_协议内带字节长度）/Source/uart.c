#include "uart.h"

unsigned char code recv_correct[] = { 0x55, 0xAA, 0x80, 0x00, 0x80, 0x80 };
unsigned char code sum_check_error[] = { 0x55, 0xAA, 0x81, 0x00, 0x81, 0x81 };
unsigned char code xor_check_error[] = { 0x55, 0xAA, 0x82, 0x00, 0x82, 0x82 };
unsigned char recv_buf[MAX_REV_NUM];
unsigned char recv_cnt;
unsigned char recv_length;
unsigned char recv_flag;
unsigned char machine_step = 0;

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
	unsigned char i;
	unsigned char recv_data;//接收数据的中间变量
	static unsigned char sum_check;
	static unsigned char xor_check;
	if (RI)
	{
		RI = 0;
		recv_data = SBUF;
		switch(machine_step)
		{
			case 0:
				if (recv_data == 0x55)
				{
					machine_step = 1;
				}
				else
				{
					machine_step = 0;
				}
				break;		
			case 1:
				if (recv_data == 0xAA)
				{
					machine_step = 2;
					recv_cnt = 0;
				}
				else
				{
					machine_step = 0;
				}
				break;
			case 2:
				//开始和校验  异或校验
				sum_check = recv_data;
				xor_check = recv_data;
				recv_buf[recv_cnt] = recv_data;
				recv_cnt++;
				machine_step = 3;
				break;
			case 3:
				sum_check += recv_data;
				xor_check ^= recv_data;
				recv_length = recv_data;
				machine_step = 4;
				break;
			case 4:
				sum_check += recv_data;
				xor_check ^= recv_data;
				recv_buf[recv_cnt] = recv_data;
				if (recv_cnt == recv_length)
				{
					machine_step = 5;
				}
				else
				{
					machine_step = 4;
				}
				recv_cnt++;
				break;
			case 5:
				if (sum_check == recv_data)//和校验正确
				{
					machine_step = 6;
				}
				else
				{
					machine_step = 0;
					for (i = 0; i < 6; i++)
					{
						sendByte(sum_check_error[i]);
					}
				}
				break;
			case 6:
				if (xor_check == recv_data)//异或校验正确
				{
					recv_flag = 1;//正确接收一串数据
					for (i = 0; i < 6; i++)
					{
						sendByte(recv_correct[i]);
					}
				}
				else
				{
					for (i = 0; i < 6; i++)
					{
						sendByte(xor_check_error[i]);
					}
				}
				machine_step = 0;
				recv_cnt = 0;
				sum_check = 0;
				xor_check = 0;
				break;
			default: break;
		}
	}
	if (TI)
	{
		TI = 0;
	}
}