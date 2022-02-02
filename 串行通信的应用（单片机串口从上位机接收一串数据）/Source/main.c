#include <reg51.h>
#include "delay.h"
#include "uart.h"

void UartInit(void);

void main()
{
	unsigned char i;
	UartInit();
	printf("Wait for Serial Communication Test Start.\r\n");
	printf("Please Send a String of Data:\r\n");
	while (1)
	{
		if (1 == recv_flag)
		{
			recv_flag = 0;
			for (i = 0; i < recv_length; i++)
			{
				sendByte(recv_buf[i]);
			}
		}
	}
}
