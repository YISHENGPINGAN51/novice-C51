#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <reg51.h>
#include "delay.h"

//IO������
#define GPIO_DIG     P0 //���� IO
#define GPIO_PLACE   P2 //λѡ IO

#define N            4  //����ܸ���

unsigned char code leddata[];
extern unsigned char LEDBuf[];

void Display();

#endif
