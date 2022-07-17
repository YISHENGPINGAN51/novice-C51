#include "DS18B20.h"

unsigned char code rom1[] = { 0x28, 0x30, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0x8E };
unsigned char code rom2[] = { 0x28, 0x31, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xB9 };
unsigned char code rom3[] = { 0x28, 0x32, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xE0 };
unsigned char code rom4[] = { 0x28, 0x33, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xD7 };

bit Start18B20()
{
	bit ack;
	//1����ʼ��
	ack = OneWireRst();
	if (ack == 0)
	{
		//2��ROMָ��
		WriteOneWire(SKIP_ROM);
		//3������ָ�� �����¶�ת��
		WriteOneWire(CONVERT_T);
	}
	return ~ack;
}

bit Read18B20(int *temp)
{
	bit ack;
	unsigned char MSB, LSB;
	//1����ʼ��
	ack = OneWireRst();
	if (ack == 0)
	{
		//2��ROMָ��
		WriteOneWire(SKIP_ROM);
		//3������ָ�� ��ȡת�����
		WriteOneWire(READ_REGISTER);
		//4����ת�����  ���ݹ���ָ����ȷ��
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
	ack = OneWireRst();//��ȡ��λ����
	if (ack == 0)
	{
		WriteOneWire(READ_ROM);//��ȡROMָ��
		for (i = 0; i < 8; i++)
		{
			*(romcode + i) = ReadOneWire();//romcode[i] ��64λROM��
		}
	}
}

/*****************************************************
��������MatchRomCode
��  �ܣ����ݲ��� ƥ�䲻ͬ��18B20��64λROM�� rom1[] rom2[] rom3[] rom4[]
��  ����unsigned char n(��Χ��1 - 4)
����ֵ����
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
	//1����ʼ��
	ack = OneWireRst();
	while(ack);
	//2��ROMָ�� ƥ��
	MatchRomCode(n);
	//3������ָ�� �����¶�ת��
	WriteOneWire(CONVERT_T);
	
	//1����ʼ��
	ack = OneWireRst();
	while(ack);
	//2��ROMָ��
	MatchRomCode(n);
	//3������ָ�� ��ȡת�����
	WriteOneWire(READ_REGISTER);
	//4����ת�����  ���ݹ���ָ����ȷ��
	LSB = ReadOneWire();
	MSB = ReadOneWire();
	*temp = ((int)MSB << 8) + LSB;
}
