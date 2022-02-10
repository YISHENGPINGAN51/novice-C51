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
		start_timer = 0;//�ض�ʱ��
		sendString(buf);//��������
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
		clr_recvbuffer(buf);//�������buffer
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
//			recv_cnt = 0;
			recv_flag = 1;
			
		}
	}
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TR0 = 1;
}