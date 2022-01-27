#include <reg51.h>
#include "delay.h"

void UartInit(void);
void sendByte(unsigned char dat);

void main()
{
	UartInit();
	while (1)
	{
		sendByte('8');
		DelayXms(1000);
	}
}

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����  SM0  SM1  SM2  REN  TB8  RB8  TI  RI
	                //                    0    1    0    1    0    0   0   0
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}

void sendByte(unsigned char dat)
{
	SBUF = dat;//  10λ  �첽����ͨ��  0 88H 1
	while (!TI);
	TI = 0;
}