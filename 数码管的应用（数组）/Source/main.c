#include <reg51.h>
#include "delay.h"
#include "display.h"

void main()
{
	unsigned int i;// 0 - 65535
	unsigned int num = 1989;// 0 - 9999  (eg:1989)
	for (i = 0; i < 5000; i++)
	{
		Display();
	}
	while(1)
	{
		LEDBuf[0] = num / 1000;
		LEDBuf[1] = num / 100 % 10;
		LEDBuf[2] = num / 10 % 10;
		LEDBuf[3] = num % 10;
		for (i = 0; i < 2000; i++)
		{
			Display();
		}
		num++;
		if (num > 2000)
		{
			num = 0;
		}
	}
}
