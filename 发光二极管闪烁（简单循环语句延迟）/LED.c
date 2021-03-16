#include <reg51.h>

void main()
{ 
  unsigned int i;
  while(1)
  {
    P1 = 0xfe;
    for(i = 0; i < 60000; i++);
    P1 = 0xff;    
    for(i = 0; i < 60000; i++);
  }
}