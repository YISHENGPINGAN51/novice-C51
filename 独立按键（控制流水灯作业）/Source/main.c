#include <reg51.h>
#include "Key.h"
#include "display.h"

void Key_Service();
void Dis_Service();

unsigned char i;
unsigned char parm[] = { 12, 55, 77, 99 };

void main()
{
	while (1)
	{
		Key_Service();
		Dis_Service();
		Display();
	}
}

void Dis_Service()
{
	LEDBuf[0] = 20;
	LEDBuf[1] = i + 1;
	LEDBuf[2] = parm[i] / 10 % 10;
	LEDBuf[3] = parm[i] % 10;
}

void Key_Service()
{
	switch (Key_Scan())
	{
		case 0: break;
		case 1: i++; if (i > 3) i = 0; break;
		case 2: parm[i]++; if (parm[i] > 99) parm[i] = 0; break;
		case 3: parm[i]--; if (parm[i] > 99) parm[i] = 99; break;
		case 4: parm[i] = 0; break;
		default: break;
	}
}

//void main()
//{
//	while (1)
//	{
//		if (1 == Key_Scan())
//		{
//			P1 = ~P1;
//		}
//	}
//}