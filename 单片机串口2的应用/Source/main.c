#include "uart.h"
#include "uart2.h"

void main()
{
	UartInit();//串口1初始化 9600
	Uart2Init();//串口2初始化 9600
	EA = 1;
	sendString("HelloWorld!\r\n");//串口1发送字符串
	sendString2("乌拉\r\n");//串口2发送字符串
	printf("Hello MCU\r\n");
	while (1)
	{
		
	}
}
