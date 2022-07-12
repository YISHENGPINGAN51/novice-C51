#include "DS18B20.h"

bit Start18B20()
{
	bit ack;
	//1、初始化
	ack = OneWireRst();
	if (ack == 0)
	{
		//2、ROM指令
		WriteOneWire(SKIP_ROM);
		//3、功能指令 启动温度转换
		WriteOneWire(CONVERT_T);
	}
	return ~ack;
}

bit Read18B20(int *temp)
{
	bit ack;
	unsigned char MSB, LSB;
	//1、初始化
	ack = OneWireRst();
	if (ack == 0)
	{
		//2、ROM指令
		WriteOneWire(SKIP_ROM);
		//3、功能指令 启动温度转换
		WriteOneWire(READ_REGISTER);
		//4、读转换结果  根据功能指令来确定
		LSB = ReadOneWire();
		MSB = ReadOneWire();
		*temp = ((int)MSB << 8) + LSB;
	}
	return ~ack;
}

void ReadRomCode(unsigned char *romcode)
{
	bit ack;
	unsigned char i;
	ack = OneWireRst();//获取复位脉冲
	if (ack == 0)
	{
		WriteOneWire(READ_ROM);//读取ROM指令
		for (i = 0; i < 8; i++)
		{
			*(romcode + i) = ReadOneWire();//romcode[i] 读64位ROM码
		}
	}
}