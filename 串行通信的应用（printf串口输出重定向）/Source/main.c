#include <reg51.h>
#include "delay.h"
#include "uart.h"

void UartInit(void);

void main()
{
	unsigned char dat = 88;
	unsigned int dat2 = 1250;
	float dat3 = 12.5;
	UartInit();
	while (1)
	{
//		sendByte('8');
//		sendByte('\r');
//		sendByte('\n');
//		sendString("Hello World!\r\n");
		printf("Hello World!\r\n");
		printf("ÄãºÃ\r\n");
		printf("dat = %bu\r\n",dat);
		printf("dat2 =%u\r\n", dat2);
		printf("dat3 =%f\r\n", dat3);
		DelayXms(2000);
	}
}
