#include <reg51.h>
#include <intrins.h>
#include "delay.h"
#include "Key.h"

bit Startflag = 1;
bit UpDownflag = 0;
unsigned char temp = 0xfe;

void Key_Service();
void main()
{
	while (1)
	{
		Key_Service();
	}
}

void Key_Service()
{
	switch (Key_Scan())
	{
		case 1: Startflag = 1; break;//Æô¶¯
		case 2: Startflag = 0; break;//Í£Ö¹
		case 3: UpDownflag = 1; break;//Down
		case 4: UpDownflag = 0; break;//Up
		default: break;
	}
	if (Startflag)
	{
		P1 = temp;
		if (UpDownflag)
		{
			temp = _cror_(temp, 1);
		}
		else
		{
			temp = _crol_(temp, 1);
		}
		DelayXms(500);
	}
}