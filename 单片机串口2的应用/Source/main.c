#include "uart.h"
#include "uart2.h"

void main()
{
	UartInit();//����1��ʼ�� 9600
	Uart2Init();//����2��ʼ�� 9600
	EA = 1;
	sendString("HelloWorld!\r\n");//����1�����ַ���
	sendString2("����\r\n");//����2�����ַ���
	printf("Hello MCU\r\n");
	while (1)
	{
		
	}
}
