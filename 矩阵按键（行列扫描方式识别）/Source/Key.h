#ifndef __KEY_H_
#define __KEY_H_

#include <reg51.h>
#include "delay.h"

sbit KEYIN1 = P3^0;
sbit KEYIN2 = P3^1;
sbit KEYIN3 = P3^2;
sbit KEYIN4 = P3^3;

sbit KEYOUT1 = P3^4;
sbit KEYOUT2 = P3^5;
sbit KEYOUT3 = P3^6;
sbit KEYOUT4 = P3^7;

unsigned char Key_Scan();

#endif
