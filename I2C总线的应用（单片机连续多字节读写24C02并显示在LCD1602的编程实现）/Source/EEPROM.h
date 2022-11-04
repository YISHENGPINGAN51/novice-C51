#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "I2C.h"
#include "delay.h"

unsigned char E2ReadByte(unsigned char IC_Addr, unsigned char addr);
void E2WriteByte(unsigned char IC_Addr, unsigned char addr, unsigned char dat);
void E2Read(unsigned char IC_Addr, unsigned char addr, unsigned char *buf, unsigned char len);
void E2Write(unsigned char IC_Addr, unsigned char addr, unsigned char *buf, unsigned char len);

#endif
