#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <reg51.h>
#include "delay.h"

#define GPIO_DIG     P2 //段码 IO
#define GPIO_PLACE   P1 //位选 IO
#define N            4  //数码管个数

unsigned char code leddata[];
extern unsigned char LEDBuf[];

void Display();

#endif
