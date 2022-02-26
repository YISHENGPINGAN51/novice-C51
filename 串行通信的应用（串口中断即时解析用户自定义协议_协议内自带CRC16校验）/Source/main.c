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
			start_timer = 0;//�ض�ʱ��
			//У�鱾����ַ���Ǳ����ģ�����մ��������˳�
			if (recv_buf[0] != LOCAL_ADDRESS)
			{
				return;
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
					led_data = recv_buf[2];
					led_data = led_data << 8;
					led_data = led_data + recv_buf[3];
					led_cnt = 0;//Ŀ����ʹLED�����������յ����ݵ�ʱ��
					break;
				case 2:
					beep_data = recv_buf[2];
					beep_data = beep_data << 8;
					beep_data = beep_data + recv_buf[3];
					beep_cnt = beep_data;
					break;
				default: break;
			}
			//sendString(recv_buf);//��������
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
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TR0 = 1;
}