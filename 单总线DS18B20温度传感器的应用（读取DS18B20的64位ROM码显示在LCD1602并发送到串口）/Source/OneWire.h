#ifndef __ONEWIRE_H_
#define __ONEWIRE_H_

#include <reg51.h>
#include "delay.h"

sbit DS18B20 = P3^6;

bit OneWireRst();
void WriteOneWire(unsigned char dat);
unsigned char ReadOneWire();

#endif
