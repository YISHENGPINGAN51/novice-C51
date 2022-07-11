#include "DS18B20.h"

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
		//3������ָ�� �����¶�ת��
		WriteOneWire(READ_REGISTER);
		//4����ת�����  ���ݹ���ָ����ȷ��
		LSB = ReadOneWire();
		MSB = ReadOneWire();
		*temp = ((int)MSB << 8) + LSB;
	}
	return ~ack;
}