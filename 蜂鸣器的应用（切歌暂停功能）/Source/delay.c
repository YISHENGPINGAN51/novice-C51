#include "delay.h"

/****************************************
函数名：DelayXms
功  能；毫秒级延时函数
参  数；unsigned int
返回值；无
****************************************/
void DelayXms(unsigned int xms)
{
  unsigned int i, j;  //0 ~ 65535  000H ~ FFFH
  for (i = xms; i > 0; i--)
    for (j = 124; j > 0; j--);
}