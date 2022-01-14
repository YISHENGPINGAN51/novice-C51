#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <reg51.h>
#include "delay.h"

#define GPIO_DIG     P2 //���� IO
#define GPIO_PLACE   P1 //λѡ IO
#define N            4  //����ܸ���

unsigned char code leddata[];
extern unsigned char LEDBuf[];

void Display();

#endif
