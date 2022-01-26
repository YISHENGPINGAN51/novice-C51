#ifndef __KEY_H_
#define __KEY_H_

#include <reg51.h>
#include "delay.h"

sbit KEY1 = P3^2;
sbit KEY2 = P3^1;
sbit KEY3 = P3^0;
sbit KEY4 = P3^3;

unsigned char Key_Scan();

#endif
