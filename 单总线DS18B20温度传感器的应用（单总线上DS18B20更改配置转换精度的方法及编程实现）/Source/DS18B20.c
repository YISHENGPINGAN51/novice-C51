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

/*****************************************************
函数名：Config18B20
功  能：配置18B20转换精度
参  数：unsigned char dat
         9位分辨率     0.5       0x1F
        10位分辨率     0.25      0x3F
        11位分辨率     0.125     0x5F
        12位分辨率     0.0625    0x7F
返回值：无
*****************************************************/
void Config18B20(unsigned char dat)
{
	bit ack;
	ack = OneWireRst();//1、初始化
	if (ack == 0)
	{
		WriteOneWire(SKIP_ROM);//2、ROM指令
		WriteOneWire(WRITE_REGISTER);//3、功能指令
		WriteOneWire(0x4b);
		WriteOneWire(0x00);
		WriteOneWire(dat);
	}
	
	ack = OneWireRst();//1、初始化
	if (ack == 0)
	{
		WriteOneWire(SKIP_ROM);//2、ROM指令
		WriteOneWire(COPY_REGISTER);//3、功能指令
	}
}