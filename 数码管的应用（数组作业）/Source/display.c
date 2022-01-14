#include "display.h"

unsigned char code leddata[] = { //数码管的段码表（共阴极）
 
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

unsigned char LEDBuf[] = { 8, 8, 8, 8 };//数据显示缓冲区
unsigned char code PLACE_CODE[] = { 0xfe, 0xfd, 0xfb, 0xf7 };//位选信号

void Display()
{
	unsigned char i;
	
	//1、送段码
	GPIO_DIG = leddata[LEDBuf[i]];
	//2、送位选
	GPIO_PLACE = PLACE_CODE[i];
	//3、延时 1ms  all<10ms
	DelayXms(1);
	//4、消隐
	GPIO_DIG = 0x00;
	
	i++;
	if (N == i)
		i = 0;
}

void BootUnit()
{
	unsigned int i, j;// 0 - 65535
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < N; j++)
		{
			LEDBuf[j] = 8;
		}
		for (j = 0; j <200; j++)
		{
			Display();
		}
		
		for (j = 0; j < N; j++)
		{
			LEDBuf[j] = 23;
		}
		for (j = 0; j <200; j++)
		{
			Display();
		}
	}
}