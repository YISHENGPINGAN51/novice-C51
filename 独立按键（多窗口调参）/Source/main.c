/*********************************************************
程序功能：按键调整不同窗口的参数 P1 - P4 四个窗口
编 写 人：FYL
修订时间：2022/1/16
*********************************************************/
//头文件
#include <reg51.h>
#include "delay.h"
#include "display.h"
#include "Key.h"

//全局变量的定义
unsigned char wnd = 0;//窗口变量，初始为窗口P1
unsigned char parm1 = 0;//窗口P1 对应的变量
unsigned char parm2 = 0;//窗口P2 对应的变量
unsigned char parm3 = 0;//窗口P3 对应的变量
unsigned char parm4 = 0;//窗口P4 对应的变量

//函数声明
void dis_Service();//显示的功能函数
void key_Service();//按键的功能函数

/*****************************************
函数名：主函数
功  能：完成程序模块的调用
参  数：无
*****************************************/
void main()
{
	unsigned int i;// 0 - 65535
	//开机界面
	for (i = 0; i < 5000; i++)
	{
		Display();
	}
	while(1)
	{
		dis_Service();
		Key_Service();
		Display();
	}
}

void dis_Service()
{
	switch (wnd)
		{
			case 0:
				LEDBuf[0] = 20;
			  LEDBuf[1] = 1;
			  LEDBuf[2] = parm1 / 10;
			  LEDBuf[3] = parm1 % 10;
				
				break;
				
			case 1:
				LEDBuf[0] = 20;
			  LEDBuf[1] = 2;
			  LEDBuf[2] = parm2 / 10;
			  LEDBuf[3] = parm2 % 10;
				
				break;
				
			case 2:
				LEDBuf[0] = 20;
			  LEDBuf[1] = 3;
			  LEDBuf[2] = parm3 / 10;
			  LEDBuf[3] = parm3 % 10;
				
				break;
				
			case 3:
				LEDBuf[0] = 20;
			  LEDBuf[1] = 4;
			  LEDBuf[2] = parm4 / 10;
			  LEDBuf[3] = parm4 % 10;
				
				break;
				
			default:break;
		}
}

void key_Service()
{
	switch (Key_Scan())
	{
		case 1: wnd++; if (wnd > 3) wnd = 0; break;
		case 2:
			switch (wnd)
			{
				case 0: parm1++; if (parm1 > 99) parm1 = 0; break;
				case 1: parm2++; if (parm2 > 99) parm2 = 0; break;
				case 2: parm3++; if (parm3 > 99) parm3 = 0; break;
				case 3: parm4++; if (parm4 > 99) parm4 = 0; break;
				default: break;
			}
			break;
			
		case 3:
			switch (wnd)
			{
				case 0: parm1--; if (parm1 > 99) parm1 = 99; break;
				case 1: parm2--; if (parm2 > 99) parm2 = 99; break;
				case 2: parm3--; if (parm3 > 99) parm3 = 99; break;
				case 3: parm4--; if (parm4 > 99) parm4 = 99; break;
				default: break;
			}
			break;
			
		case 4:
			switch (wnd)
			{
				case 0: parm1 = 0; break;
				case 1: parm2 = 0; break;
				case 2: parm3 = 0; break;
				case 3: parm4 = 0; break;
				default: break;
			}
			break;
			
		default: break;
	}
}