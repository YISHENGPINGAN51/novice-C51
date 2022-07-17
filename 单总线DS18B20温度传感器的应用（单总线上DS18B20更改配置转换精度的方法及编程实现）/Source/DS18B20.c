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

/*****************************************************
��������Config18B20
��  �ܣ�����18B20ת������
��  ����unsigned char dat
         9λ�ֱ���     0.5       0x1F
        10λ�ֱ���     0.25      0x3F
        11λ�ֱ���     0.125     0x5F
        12λ�ֱ���     0.0625    0x7F
����ֵ����
*****************************************************/
void Config18B20(unsigned char dat)
{
	bit ack;
	ack = OneWireRst();//1����ʼ��
	if (ack == 0)
	{
		WriteOneWire(SKIP_ROM);//2��ROMָ��
		WriteOneWire(WRITE_REGISTER);//3������ָ��
		WriteOneWire(0x4b);
		WriteOneWire(0x00);
		WriteOneWire(dat);
	}
	
	ack = OneWireRst();//1����ʼ��
	if (ack == 0)
	{
		WriteOneWire(SKIP_ROM);//2��ROMָ��
		WriteOneWire(COPY_REGISTER);//3������ָ��
	}
}