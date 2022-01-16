/*********************************************************
�����ܣ�����������ͬ���ڵĲ��� P1 - P4 �ĸ�����
�� д �ˣ�FYL
�޶�ʱ�䣺2022/1/16
*********************************************************/
//ͷ�ļ�
#include <reg51.h>
#include "delay.h"
#include "display.h"
#include "Key.h"

//ȫ�ֱ����Ķ���
unsigned char wnd = 0;//���ڱ�������ʼΪ����P1
unsigned char parm1 = 0;//����P1 ��Ӧ�ı���
unsigned char parm2 = 0;//����P2 ��Ӧ�ı���
unsigned char parm3 = 0;//����P3 ��Ӧ�ı���
unsigned char parm4 = 0;//����P4 ��Ӧ�ı���

//��������
void dis_Service();//��ʾ�Ĺ��ܺ���
void key_Service();//�����Ĺ��ܺ���

/*****************************************
��������������
��  �ܣ���ɳ���ģ��ĵ���
��  ������
*****************************************/
void main()
{
	unsigned int i;// 0 - 65535
	//��������
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