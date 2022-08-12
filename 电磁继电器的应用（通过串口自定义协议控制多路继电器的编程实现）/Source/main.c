/************************************************************************
���ܣ���CRCУ��� �Զ���ͨѶЭ��
			01			01				01			03				CRC16
			��ַ		������			����		У����
							01	��һ·�̵���			01	�򿪼̵���
							02	�ڶ�·�̵���			02	�رռ̵���
																	ֻ����������Ч����
************************************************************************/
#include <reg51.h>
#include "uart.h"
#include "Relay.h"
#include "CRC16.h"

#define LOCAL_ADDRESS 0x01

void Timer0Init(void);

void main()
{
	unsigned char i;
	unsigned int crc;
	unsigned char crch, crcl;
	Timer0Init();
	UartInit();
	Relay_Init();
	EA = 1;
	while (1)
	{
		if (recv_flag)
		{
			recv_flag = 0;
			start_timer = 0;//�ض�ʱ��
			//У�鱾����ַ���Ǳ����ģ�����մ��������˳�
			if (recv_buf[0] != LOCAL_ADDRESS)
			{
				//return;
				continue;
			}
			//CRC16У�飬У����ȷ�����ǲŴ�������ֱ�ӷ��أ�������������
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
					if (recv_buf[2] == 0x01)
						Relay0_ON();
					else if (recv_buf[2] == 0x02)
						Relay0_OFF();
					break;
				case 2:
					if (recv_buf[2] == 0x01)
						Relay1_ON();
					else if (recv_buf[2] == 0x02)
						Relay1_OFF();
					break;
				case 3:
					if (recv_buf[2] == 0x01)
						Relay2_ON();
					else if (recv_buf[2] == 0x02)
						Relay2_OFF();
					break;
				case 4:
					if (recv_buf[2] == 0x01)
						Relay3_ON();
					else if (recv_buf[2] == 0x02)
						Relay3_OFF();
					break;
				case 5:
					if (recv_buf[2] == 0x01)
						Relay4_ON();
					else if (recv_buf[2] == 0x02)
						Relay4_OFF();
					break;
				default: break;
			}
			for (i = 0; i < recv_cnt; i++)
			{
				sendByte(recv_buf[i]);
			}
			clr_recvbuffer(recv_buf);//�������buffer
			recv_cnt = 0;
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
			recv_flag = 1;
		}
	}

	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TR0 = 1;
}
