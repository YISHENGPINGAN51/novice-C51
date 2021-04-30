/******************************
功能：库函数(循环左移或右移函数 _crol_ _cror_)实现流水灯
编程人：FYL
时间：2021_03_19
版本：V1.1
******************************/

//头文件
#include <reg51.h>
#include <intrins.h>
#include "delay.h"

/******************************
函数名：main
功  能：主函数
参  数：无
返回值：无
******************************/
void main()
{
  unsigned char temp = 0xfe;// 1111 1110
  while (1)
  {
    P1 = temp; 
    temp = _crol_(temp, 1);//循环左移实现正向流水灯
    DelayXms(1000);   
  }
}