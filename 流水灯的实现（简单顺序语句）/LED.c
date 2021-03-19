/******************************
���ܣ������ʵ����ˮ�ƣ�����
����ˣ�������
ʱ�䣺2021_03_19
�汾��V1.0
******************************/

#include <reg51.h>

//��������
void DelayXms(unsigned int xms);

void main()
{
  while(1)
  {
    P1 = 0xfe;  //1111 1110       
    DelayXms(1000);
    P1 = 0xfd;  //1111 1101       -1
    DelayXms(1000);
    P1 = 0xfb;  //1111 1011       -2
    DelayXms(1000);
    P1 = 0xf7;  //1111 0111       -4
    DelayXms(1000);
    P1 = 0xef;  //1110 1111       -8
    DelayXms(1000);
    P1 = 0xdf;  //1101 1111       -16
    DelayXms(1000);
    P1 = 0xbf;  //1011 1111       -32
    DelayXms(1000);
    P1 = 0x7f;  //1111 0111       -64
    DelayXms(1000);
  }
}

void DelayXms(unsigned int xms)
{
  unsigned int i, j;
  for (i = xms; i > 0; i--)
    for (j = 124; j > 0; j--);
}