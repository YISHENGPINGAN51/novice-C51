#include <reg51.h>
#include "Key.h"
#include "display.h"

void Dis_Service();
void Key_Service();

unsigned int NumCnt;

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
	LEDBuf[0] = NumCnt / 1000;
	LEDBuf[1] = NumCnt / 100 % 10;
	LEDBuf[2] = NumCnt / 10 % 10;
	LEDBuf[3] = NumCnt % 10;
}

void Key_Service()
{
	switch (Key_Scan())
	{
		case 0: break;
		case 1: NumCnt++; if (NumCnt > 9999) NumCnt = 0; break;
		case 2: NumCnt--; if (NumCnt > 9999) NumCnt = 9999; break;
		case 3: NumCnt = 0; break;
		case 4: NumCnt = 88; break;
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