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
	unsigned char i;
	unsigned char recv_data;//�������ݵ��м����
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
				//��ʼ��У��  ���У��
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
				if (sum_check == recv_data)//��У����ȷ
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
				if (xor_check == recv_data)//���У����ȷ
				{
					recv_flag = 1;//��ȷ����һ������
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