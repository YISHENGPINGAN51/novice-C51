#include "uart2.h"
#include "uart.h"

void Uart2Init(void)		//9600bps@11.0592MHz
{
	AUXR &= 0xF7;		//�����ʲ�����
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xFB;		//��ʱ��ʱ��12Tģʽ
	BRT = 0xFD;		//���ö�ʱ����ֵ
	AUXR |= 0x10;		//�������������ʷ�����
	IE2 = 0x01;             //ʹ��UART2�ж�
}

void sendByte2(unsigned char dat)
{
	S2BUF = dat;
	while (!(S2CON & S2TI));
	S2CON &= ~S2TI;     //Clear transmit interrupt flag
}

//����2�����ַ���
void sendString2(unsigned char *dat)//Hello World!
{
	while (*dat != '\0')
	{
		sendByte2(*dat++);
	}
}

#if 1
char putchar(char c)
{
	sendByte2(c);
	return c;
}
#endif

void uart2_ISR() interrupt 8
{
	unsigned char dat;
	if (S2CON & S2RI)
	{
		S2CON &= ~S2RI;     //Clear receive interrupt flag
		dat = S2BUF;        //����2��ȡһ���ֽ�
		sendByte(dat);      //ͨ������1ת��
	}
}
