#include <reg51.h>
#include "Key.h"
#include <intrins.h>

void Key_Service();

unsigned char temp = 0xfe;// 1111 1110

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
		case 0: 
			break;
		
		case 1: 
			while (1)
			{
				P1 = temp; 
				temp = _crol_(temp, 1);//循环左移实现正向流水灯
				DelayXms(200);
				if (2 == Key_Scan())
					break;
			}
			break;
			
		case 2: 
			P1 = 0xff;
			temp = 0xfe;
			break;
		
		case 3: 
			while (1)
			{
				P1 = temp; 
				temp = _crol_(temp, 1);//循环左移实现正向流水灯
				DelayXms(200);
				if (2 == Key_Scan())
					break;
			}
			break;
			
		case 4: 
			while (1)
			{
				P1 = temp; 
				temp = _cror_(temp, 1);//循环右移实现负向流水灯
				DelayXms(200);
				if (2 == Key_Scan())
					break;
			}
			break;
			
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