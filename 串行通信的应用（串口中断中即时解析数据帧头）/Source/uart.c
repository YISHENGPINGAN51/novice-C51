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
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����  SM0  SM1  SM2  REN  TB8  RB8  TI  RI
	                //                    0    1    0    1    0    0   0   0
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	ES = 1;
	TR1 = 1;		//������ʱ��1
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
1���жϷ�����һ����һ��û�з���ֵ�ĺ���
2���жϷ�����һ����û�в����ĺ���
3���жϷ���������������ؼ��� interrupt
4��interrupt n 0 - 4  5���ж�Դ  8*n + 0003H
0003H INT0    000BH T0    0013H INT1    001BH T1    0023H ES
5���жϷ��������ܱ����������������������
6��n�����using m (0 - 3)�����Ĵ�����
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
							led_cnt = 0;//Ŀ����ʹLED�����������յ����ݵ�ʱ��
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
					recv_flag = 1;//������һ�����ݣ���־λ��1
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