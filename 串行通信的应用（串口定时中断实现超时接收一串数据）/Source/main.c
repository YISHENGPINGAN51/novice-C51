#include <reg51.h>
#include "delay.h"
#include "uart.h"

void Timer0Init(void);

void main()
{
	unsigned char i;
	 Timer0Init();
	UartInit();
	EA = 1;
	printf("Wait for Serial Communication Test Start.\r\n");
	printf("Please Send a string of data:\r\n");
	while (1)
	{
		if (recv_flag)
		{
			recv_flag = 0;
			start_timer = 0;//�ض�ʱ��
			sendString(recv_buf);//��������
			clr_recvbuffer(recv_buf);//�������buffer
		}
	}
}

void Timer0Init(void)		//1����@11.0592MHz
{
//	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void timer0_ISR() interrupt 1
{
	TR0 = 0;
	if (1 == start_timer)
	{
		recv_timer_cnt++;//1���ۼӶ�ʱʱ�������
		if (recv_timer_cnt > MAX_REV_TIME)//2���ж϶�ʱʱ���Ƿ񳬹����趨��������ֵ��
			                                //������˵���ȴ�һ��ʱ���û���µ����ݵ���
		                                  //�����ж�һ�����ݽ������
		{
			recv_timer_cnt = 0;//3�������ʱ������  ��������  ���buffer���ŵ����ݴ���֮��
			recv_cnt = 0;
			recv_flag = 1;
			
		}
	}
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TR0 = 1;
}