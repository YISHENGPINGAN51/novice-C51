#include "DS18B20.h"

unsigned char code rom1[] = { 0x28, 0x30, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0x8E };
unsigned char code rom2[] = { 0x28, 0x31, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xB9 };
unsigned char code rom3[] = { 0x28, 0x32, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xE0 };
unsigned char code rom4[] = { 0x28, 0x33, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xD7 };

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
		//3、功能指令 读取转换结果
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

/*****************************************************
函数名：MatchRomCode
功  能：根据参数 匹配不同的18B20的64位ROM码 rom1[] rom2[] rom3[] rom4[]
参  数：unsigned char n(范围：1 - 4)
返回值：无
*****************************************************/
void MatchRomCode(unsigned char n)
{
	unsigned char i;
	WriteOneWire(MATH_ROM);
	switch (n)
	{
		case 1:
			for (i = 0; i < 8; i++)
				WriteOneWire(rom1[i]);
			break;
		case 2:
			for (i = 0; i < 8; i++)
				WriteOneWire(rom2[i]);
			break;
		case 3:
			for (i = 0; i < 8; i++)
				WriteOneWire(rom3[i]);
			break;
		case 4:
			for (i = 0; i < 8; i++)
				WriteOneWire(rom4[i]);
			break;
		default: break;
	}
}

void Get18B20Temp(int *temp, unsigned char n)
{
	bit ack;
	unsigned char MSB, LSB;
	//1、初始化
	ack = OneWireRst();
	while(ack);
	//2、ROM指令 匹配
	MatchRomCode(n);
	//3、功能指令 启动温度转换
	WriteOneWire(CONVERT_T);
	
	//1、初始化
	ack = OneWireRst();
	while(ack);
	//2、ROM指令
	MatchRomCode(n);
	//3、功能指令 读取转换结果
	WriteOneWire(READ_REGISTER);
	//4、读转换结果  根据功能指令来确定
	LSB = ReadOneWire();
	MSB = ReadOneWire();
	*temp = ((int)MSB << 8) + LSB;
}
