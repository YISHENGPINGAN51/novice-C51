#include <reg51.h>
#include "I2C.h"
#include "delay.h"
#include "LCD1602.h"

bit E2PROMAddr(unsigned char addr);

void main()
{
	bit ack;
	unsigned char str[6];
	LCDInit();
	DelayXms(10);
	ack = E2PROMAddr(0x50);
	str[0] = '0';
	str[1] = 'x';
	str[2] = '5';
	str[3] = '0';
	str[4] = ':';
	str[5] = (unsigned char)ack + '0';
	LCDShowStr(0, 0, str);
	
	ack = E2PROMAddr(0x51);
	str[0] = '0';
	str[1] = 'x';
	str[2] = '5';
	str[3] = '1';
	str[4] = ':';
	str[5] = (unsigned char)ack + '0';
	LCDShowStr(7, 0, str);
	
	ack = E2PROMAddr(0x52);
	str[0] = '0';
	str[1] = 'x';
	str[2] = '5';
	str[3] = '2';
	str[4] = ':';
	str[5] = (unsigned char)ack + '0';
	LCDShowStr(0, 1, str);
	while (1);
}

bit E2PROMAddr(unsigned char addr)
{
	bit ack;
	I2CStart();//主机发出起始信号
	I2CWriteByte(addr << 1);//1010 0000 0xA0 写一个字节 第一个字节一定是器件寻址字节
	ack = I2CRecvAck();//每写一个字节，从机返回一个ack 应答位
	I2CStop();//停止信号，结束一次数据传输
	return ack;
}