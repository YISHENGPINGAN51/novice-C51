#include <reg51.h>
#include "delay.h"
#include "display.h"
#include "Key.h"

/*****************************************
函数名：主函数
功  能：完成程序模块的调用
参  数：无
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