#include <reg51.h>

void main()
{
  while(1)
  {
    P1 = 0xfe;  //P1.7 ~ P1.0 1111 1110  
  }
}