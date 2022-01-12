#include <reg51.h>
#include "delay.h"

unsigned char code leddata[]={ //数码管的段码表（共阴极）
 
                0x3F,  //"0"
                0x06,  //"1"
                0x5B,  //"2"
                0x4F,  //"3"
                0x66,  //"4"
                0x6D,  //"5"
                0x7D,  //"6"
                0x07,  //"7"
                0x7F,  //"8"
                0x6F,  //"9"
                0x77,  //"A"
                0x7C,  //"B"
                0x39,  //"C"
                0x5E,  //"D"
                0x79,  //"E"
                0x71,  //"F"
                0x76,  //"H"
                0x38,  //"L"
                0x37,  //"n"
                0x3E,  //"u"
                0x73,  //"P"
                0x5C,  //"o"
                0x40,  //"-"
                0x00,  //熄灭
 
                         };

void main()
{
	while(1)
	{
		P1 = 0xfe;//1111 1110 第一个数码管的位选打开，其他的关掉，打开第一个数码管显示功能
		P2 = leddata[1];
		DelayXms(1);
		
		P1 = 0xfd;//1111 1101 第一个数码管的位选关掉，同时打开第二个数码管的位选，其他的关掉，打开第二个数码管显示功能
		P2 = leddata[2];
		DelayXms(1);
		
		P1 = 0xfb;//1111 1011 第二个数码管的位选关掉，同时打开第三个数码管的位选，其他的关掉，打开第三个数码管显示功能
		P2 = leddata[3];
		DelayXms(1);
		
		P1 = 0xf7;//1111 0111 第三个数码管的位选关掉，同时打开第四个数码管的位选，其他的关掉，打开第四个数码管显示功能
		P2 = leddata[4];
		DelayXms(1);
	}
}
												 
//void main()
//{
//	unsigned char i;
//  while (1)
//  {
//		P1 = 0xf0;
//		for (i = 0; i < 16; i++)
//		{
//			P2 = leddata[i];
//			DelayXms(1000);
//		}
//  }
//}