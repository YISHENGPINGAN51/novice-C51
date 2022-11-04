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

bit I2CWriteByte(unsigned char dat)
{
	unsigned char temp;
	bit ack;
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
	ack = I2CRecvAck();
	return ack;
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

unsigned char I2CReadByte()
{
	unsigned char dat = 0;
	unsigned char temp;
	I2C_SDA = 1;//主机释放总线，为接下来的读数据作准备
	for (temp = 0x80; temp != 0; temp >>= 1)//还是从高位到低位读
	{
		I2CDelay();//延时至少4us 使SCL保持低
		I2C_SCL = 1;//拉高 器件读数据位
		if (I2C_SDA == 1)
			dat |= temp;
		else
			dat &= ~temp;
		I2CDelay();//延时至少4us 使SCL保持高
		I2C_SCL = 0;//拉低 为下一次传输作准备
	}
	return dat;
}

void SendAck(bit ack)
{
	I2C_SDA = ack;
	I2CDelay();//延时至少4us 使SCL保持低
	I2C_SCL = 1;//拉高 器件读数据位
	I2CDelay();//延时至少4us 使SCL保持高
	I2C_SCL = 0;//拉低 为下一次传输作准备
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
