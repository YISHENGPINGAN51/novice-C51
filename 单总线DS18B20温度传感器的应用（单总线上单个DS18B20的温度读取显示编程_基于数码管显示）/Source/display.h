#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <reg51.h>
#include "delay.h"

//IO的声明
#define GPIO_DIG     P0 //段码 IO
#define GPIO_PLACE   P2 //位选 IO

#define N            4  //数码管个数

unsigned char code leddata[];
extern unsigned char LEDBuf[];

void Display();

#endif
