#include "uart.h"

unsigned char recv_flag = 0;
unsigned char start_timer = 0;
unsigned char recv_buf[MAX_REV_NUM];
unsigned char recv_cnt;
unsigned char recv_timer_cnt;

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

#if 0
char putchar(char c)
{
	sendByte(c);
	return c;
}
#endif

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
		start_timer = 1;//1��ÿ���յ�һ֡���ݵ�ʱ�򣬴������ʱ����ȥ����
		if (recv_cnt < MAX_REV_NUM)
		{
			recv_buf[recv_cnt] = SBUF;//2���������ݵ����ݻ�������ע�⻺�����Ĵ�С��Χ����
			recv_cnt++;
		}
		else
		{
			recv_cnt = MAX_REV_NUM;
		}
		recv_timer_cnt = 0;//3��ÿ����һ֡���ݣ��ǵðѶ�ʱ��������  �൱����ι���ź�
		                   //�����ڶ�ʱ�ж�����᲻���ۼ�
	}
}
