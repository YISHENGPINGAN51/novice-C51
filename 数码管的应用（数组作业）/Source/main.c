#include <reg51.h>
#include "delay.h"
#include "display.h"

void main()
{
	unsigned int i;// 0 - 65535
	unsigned int num1 = 99;// 0 - 99
	unsigned int num2 = 520;// 0 - 999
	unsigned int num3 = 1314;// 0 - 9999
	BootUnit();
	while(1)
	{
		//参数1
		LEDBuf[0] = num1 / 1000;
		LEDBuf[1] = num1 / 100 % 10;
		LEDBuf[2] = num1 / 10 % 10;
		LEDBuf[3] = num1 % 10;
		for (i = 0; i < 1900; i++)
		{
			Display();
		}
		
		//参数2
		LEDBuf[0] = num2 / 1000;
		LEDBuf[1] = num2 / 100 % 10;
		LEDBuf[2] = num2 / 10 % 10;
		LEDBuf[3] = num2 % 10;
		for (i = 0; i < 1900; i++)
		{
			Display();
		}
		
		//参数3
		LEDBuf[0] = num3 / 1000;
		LEDBuf[1] = num3 / 100 % 10;
		LEDBuf[2] = num3 / 10 % 10;
		LEDBuf[3] = num3 % 10;
		for (i = 0; i < 1900; i++)
		{
			Display();
		}
	}
}
