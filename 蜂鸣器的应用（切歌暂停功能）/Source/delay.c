#include "delay.h"

/****************************************
��������DelayXms
��  �ܣ����뼶��ʱ����
��  ����unsigned int
����ֵ����
****************************************/
void DelayXms(unsigned int xms)
{
  unsigned int i, j;  //0 ~ 65535  000H ~ FFFH
  for (i = xms; i > 0; i--)
    for (j = 124; j > 0; j--);
}