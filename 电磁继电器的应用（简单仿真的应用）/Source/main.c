#include <reg51.h>

sbit RELAY0 = P1^0;
sbit RELAY1 = P1^1;
sbit RELAY2 = P1^2;
sbit RELAY3 = P1^3;
sbit RELAY4 = P1^4;

void main()
{
	RELAY0 = 1;
	RELAY1 = 0;
	RELAY2 = 0;
	RELAY3 = 0;
	RELAY4 = 0;
	while (1)
	{
		RELAY0 = 0;
		RELAY1 = 1;
		RELAY2 = 1;
		RELAY3 = 1;
		RELAY4 = 1;
	}
}
