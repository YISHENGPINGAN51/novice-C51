#ifndef __RELAY_H_
#define __RELAY_H_

#include <reg51.h>

sbit RELAY0 = P1^0;
sbit RELAY1 = P1^1;
sbit RELAY2 = P1^2;
sbit RELAY3 = P1^3;
sbit RELAY4 = P1^4;

void Relay_Init(void);
void Relay0_ON(void);
void Relay0_OFF(void);
void Relay1_ON(void);
void Relay1_OFF(void);
void Relay2_ON(void);
void Relay2_OFF(void);
void Relay3_ON(void);
void Relay3_OFF(void);
void Relay4_ON(void);
void Relay4_OFF(void);

#endif