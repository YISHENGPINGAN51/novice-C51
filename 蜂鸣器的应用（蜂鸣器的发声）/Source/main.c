/******************************
功  能：蜂鸣器的发声
编程人：FYL
时  间：2021_05_03
版  本：V1.0
******************************/

//头文件
#include <reg51.h>
#include "delay.h"

sbit Sound = P3 ^ 7;

/******************************
函数名：main
功  能：主函数
参  数：无
返回值：无
******************************/
void main()
{
  while(1)
  {
    Sound = ~Sound;
    DelayXms(500);
  }
}