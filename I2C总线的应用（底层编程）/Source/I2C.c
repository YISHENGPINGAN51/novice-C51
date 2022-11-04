#include "I2C.h"

void I2CStart()
{
	I2C_SCL = 1;//总线空闲时 SCL SDA 都为高电平	
	I2C_SDA = 1;
	I2CDelay();//SCL保持4.7us之后，拉低SDA，产生起始信号
	I2C_SDA = 0;
	I2CDelay();
	I2C_SCL = 0;
}

void I2CWriteByte(unsigned char dat)
{
	unsigned char temp;
	for (temp = 0x80; temp != 0; temp >>= 1)
	{
		if( (temp & dat) == 0) //当前位为0
			I2C_SDA = 0;
		else									 //当前位为1
			I2C_SDA = 1;
		I2CDelay();//延时至少4us 使SCL保持低
		I2C_SCL = 1;//拉高 器件读数据位
		I2CDelay();//延时至少4us 使SCL保持高
		I2C_SCL = 0;//拉低
	}
}

bit I2CRecvAck()
{
	bit ack;
	I2C_SDA = 1;//主机主动释放SDA，为读ack做准备
	I2CDelay();//SCL保持4.7us低
	I2C_SCL = 1;//拉高
	ack = I2C_SDA;
	I2CDelay();//延时至少4us 使SCL保持高
	I2C_SCL = 0;//拉低SCL
	return ack;
}

void I2CStop()
{
	I2C_SCL = 0;
	I2C_SDA = 0;
	I2CDelay();
	I2C_SCL = 1;
	I2CDelay();
	I2C_SDA = 1;
	I2CDelay();
}
