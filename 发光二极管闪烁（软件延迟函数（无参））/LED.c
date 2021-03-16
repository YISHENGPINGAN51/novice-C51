#include <reg51.h>

sbit led = P1 ^ 0;

void Delay500ms();

void main()
{
  while(1)
  {
    led = 0;
    Delay500ms();
    led = 1;
    Delay500ms();
  }
}

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


//sbit led = p1 ^ 0;
//
//void delay();
//
//void main()
//{
//  while(1)
//  {
//    led = 0;
//    delay();
//    led = 1;
//    delay();
//  }
//}
//
//void delay()
//{
//  unsigned int ms = 50000;
//  while(ms--);
//}
