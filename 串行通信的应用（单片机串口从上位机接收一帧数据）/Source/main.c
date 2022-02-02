#include <reg51.h>
#include "delay.h"
#include "uart.h"

//sbit LED1 = P1^0;
//sbit LED2 = P1^1;
//sbit LED3 = P1^2;
//sbit LED4 = P1^3;

void UartInit(void);

void main()
{
	UartInit();
	printf("Wait for Serial Communication Test Start.\r\n");
	printf("Please Send a command:\r\n");
	while (1)
	{
		if (recv_flag == 1)
		{
			recv_flag = 0;
			switch (recv_data)
			{
				case 0x01: P1 = 0xfe; break;
				case 0x02: P1 = 0xfd; break;
				case 0x03: P1 = 0xfb; break;
				case 0x04: P1 = 0xf7; break;
				default: break;
			}
		}
	}
}

//void main()
//{
//	UartInit();
//	printf("Wait for Serial Communication Test Start.\r\n");
//	printf("Please Send a frame of data:\r\n");
//	while (1)
//	{
//		if (recv_flag == 1)
//		{
//			recv_flag = 0;
//			recv_data = recv_data + 1;
//			sendByte(recv_data);
//			printf("\r\n");
//			printf("%bd\r\n", recv_data);
//		}
//	}
//}
