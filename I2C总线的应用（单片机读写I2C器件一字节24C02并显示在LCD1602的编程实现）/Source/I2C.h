#ifndef __I2C_H__
#define __I2C_H__

#include <reg51.h>
#include <intrins.h>

#define I2CDelay() {_nop_();_nop_();_nop_();_nop_();}

sbit I2C_SDA = P1^1;
sbit I2C_SCL = P1^0;

void I2CStart();
bit I2CWriteByte(unsigned char dat);
bit I2CRecvAck();
void I2CStop();
unsigned char I2CReadByte();
void SendAck(bit ack);

#endif
