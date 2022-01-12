#include <reg51.h>
#include "delay.h"

unsigned char code leddata[]={ //数码管的段码表（共阳极）
              	0xC0,  //"0"
                0xF9,  //"1"
                0xA4,  //"2"
                0xB0,  //"3"
                0x99,  //"4"
                0x92,  //"5"
                0x82,  //"6"
                0xF8,  //"7"
                0x80,  //"8"
                0x90,  //"9"
                0x88,  //"A"
                0x83,  //"B"
                0xC6,  //"C"
                0xA1,  //"D"
                0x86,  //"E"
                0x8E,  //"F"
                0x89,  //"H"
                0xC7,  //"L"
                0xC8,  //"n"
                0xC1,  //"u"
                0x8C,  //"P"
                0xA3,  //"o"
                0xBF,  //"-"
                0xFF,  //熄灭
 
                         };


void main()
{
	unsigned char i;
  while (1)
  {
		for (i = 0; i < 16; i++)
		{
			P2 = leddata[i];
			DelayXms(1000);
		}
  }
}
