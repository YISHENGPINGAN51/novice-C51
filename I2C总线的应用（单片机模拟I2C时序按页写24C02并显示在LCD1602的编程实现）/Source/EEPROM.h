#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "I2C.h"
#include "delay.h"

#define Max_addr 0xFF
#define PageByte 0x07//8字节一页  0x0F是16字节一页
unsigned char E2ReadByte(unsigned char IC_Addr, unsigned char addr);
void E2WriteByte(unsigned char IC_Addr, unsigned char addr, unsigned char dat);
void E2Read(unsigned char IC_Addr, unsigned char addr, unsigned char *buf, unsigned char len);
void E2Write(unsigned char IC_Addr, unsigned char addr, unsigned char *buf, unsigned char len);
unsigned char E2WritePage(unsigned char IC_Addr, unsigned char addr, unsigned char *buf, unsigned char len);

#endif
