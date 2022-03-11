#include <reg51.h>
#include "uart.h"
#include <stdio.h>
#include "delay.h"
#include "ultrasound.h"

void main()
{
	int distance = 0;
	UartInit();
	ultra_init();
	printf("Start Measure!\r\n");
	while(1)
	{
		distance = get_distance();
		if (distance < 0)
			printf("ERROR!\r\n");
		else
			printf("distance = %d\r\n", distance);
		DelayXms(2000);
	}
}