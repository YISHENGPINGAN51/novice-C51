#include <reg51.h>
#include "delay.h"
#include "uart.h"

sbit LED = P1^0;
sbit BEEP = P3^7;

unsigned int led_data;
unsigned int beep_data;
unsigned int led_cnt;
unsigned int beep_cnt;

void Timer0Init(void);

void main()
{
	Timer0Init();
	UartInit();
	EA = 1;
	printf("Wait for Serial Communication Test Start.\r\n");
	printf("Please Send a Command:\r\n");
	DelayXms(10);
	while (1)
	{
		if (recv_flag == 1)
		{
			recv_flag = 0;
			sendString(recv_buf);		
			switch (recv_buf[0])
			{
				case 1:
					led_data = recv_buf[1];
					led_data = led_data << 8;
					led_data = led_data + recv_buf[2];
					led_cnt = 0;//Ŀ����ʹLED�����������յ����ݵ�ʱ��
					break;
				case 2:
					beep_data = recv_buf[1];
					beep_data = beep_data << 8;
					beep_data = beep_data + recv_buf[2];
					beep_cnt = beep_data;
					break;
				default:
					clr_recvbuffer(recv_buf);
					break;
			}
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