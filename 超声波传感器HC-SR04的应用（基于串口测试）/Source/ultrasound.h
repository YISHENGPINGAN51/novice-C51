#ifndef __ULTRASOUND_H_
#define __ULTRASOUND_H_

#include <reg51.h>

sbit Trig_P17 = P1^7;
sbit Echo_P32 = P3^2;

void Timer0Init(void);
extern void ultra_init(void);
extern int get_distance(void);

#endif
