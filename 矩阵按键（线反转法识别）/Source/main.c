#include <reg51.h>
#include "delay.h"
#include "display.h"
#include "Key.h"

/*****************************************
��������������
��  �ܣ���ɳ���ģ��ĵ���
��  ������
*****************************************/
void main()
{
	while(1)
	{
		LEDBuf[0] = 23;
		LEDBuf[1] = 23;
		LEDBuf[2] = 23;
		LEDBuf[3] = Key_Scan();
		Display();
	}
}