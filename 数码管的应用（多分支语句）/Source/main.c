#include <reg51.h>
#include "delay.h"
#include "display.h"

unsigned char wnd;
unsigned char parm1 = 44;
unsigned char parm2 = 55;
unsigned char parm3 = 66;
unsigned char parm4 = 77;

void dis_Service();

void main()
{
	unsigned int i;// 0 - 65535
	for (i = 0; i < 5000; i++)
	{
		Display();
	}
	while(1)
	{
		dis_Service();
	}
}

void dis_Service()
{
	unsigned int i;
	switch (wnd)
		{
			case 0:
				LEDBuf[0] = 0;
			  LEDBuf[1] = 22;
			  LEDBuf[2] = parm1 / 10;
			  LEDBuf[3] = parm1 % 10;
				for (i = 0; i < 5000; i++)
				{
					Display();
				}
				wnd++;
				break;
				
			case 1:
				LEDBuf[0] = 1;
			  LEDBuf[1] = 22;
			  LEDBuf[2] = parm2 / 10;
			  LEDBuf[3] = parm2 % 10;
				for (i = 0; i < 5000; i++)
				{
					Display();
				}
				wnd++;
				break;
				
			case 2:
				LEDBuf[0] = 2;
			  LEDBuf[1] = 22;
			  LEDBuf[2] = parm3 / 10;
			  LEDBuf[3] = parm3 % 10;
				for (i = 0; i < 5000; i++)
				{
					Display();
				}
				wnd++;
				break;
				
			case 3:
				LEDBuf[0] = 3;
			  LEDBuf[1] = 22;
			  LEDBuf[2] = parm4 / 10;
			  LEDBuf[3] = parm4 % 10;
				for (i = 0; i < 5000; i++)
				{
					Display();
				}
				wnd = 0;
				break;
				
			default:break;
		}
}