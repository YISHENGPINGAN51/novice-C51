#ifndef __KEY_H_
#define __KEY_H_

#include <reg51.h>
#include "delay.h"

sbit START = P3^0;
sbit STOP = P3^1;
sbit DOWN = P3^2;
sbit UP = P3^3;

unsigned char Key_Scan();

#endif
