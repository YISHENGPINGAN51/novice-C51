#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "I2C.h"

unsigned char E2ReadByte(unsigned char IC_Addr, unsigned char addr);
void E2WriteByte(unsigned char IC_Addr, unsigned char addr, unsigned char dat);

#endif