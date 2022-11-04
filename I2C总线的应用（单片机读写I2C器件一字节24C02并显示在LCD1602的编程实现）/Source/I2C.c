#include "I2C.h"

void I2CStart()
{
	I2C_SCL = 1;//���߿���ʱ SCL SDA ��Ϊ�ߵ�ƽ	
	I2C_SDA = 1;
	I2CDelay();//SCL����4.7us֮������SDA��������ʼ�ź�
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
		if( (temp & dat) == 0) //��ǰλΪ0
			I2C_SDA = 0;
		else									 //��ǰλΪ1
			I2C_SDA = 1;
		I2CDelay();//��ʱ����4us ʹSCL���ֵ�
		I2C_SCL = 1;//���� ����������λ
		I2CDelay();//��ʱ����4us ʹSCL���ָ�
		I2C_SCL = 0;//����
	}
	ack = I2CRecvAck();
	return ack;
}

bit I2CRecvAck()
{
	bit ack;
	I2C_SDA = 1;//���������ͷ�SDA��Ϊ��ack��׼��
	I2CDelay();//SCL����4.7us��
	I2C_SCL = 1;//����
	ack = I2C_SDA;
	I2CDelay();//��ʱ����4us ʹSCL���ָ�
	I2C_SCL = 0;//����SCL
	return ack;
}

unsigned char I2CReadByte()
{
	unsigned char dat = 0;
	unsigned char temp;
	I2C_SDA = 1;//�����ͷ����ߣ�Ϊ�������Ķ�������׼��
	for (temp = 0x80; temp != 0; temp >>= 1)//���ǴӸ�λ����λ��
	{
		I2CDelay();//��ʱ����4us ʹSCL���ֵ�
		I2C_SCL = 1;//���� ����������λ
		if (I2C_SDA == 1)
			dat |= temp;
		else
			dat &= ~temp;
		I2CDelay();//��ʱ����4us ʹSCL���ָ�
		I2C_SCL = 0;//���� Ϊ��һ�δ�����׼��
	}
	return dat;
}

void SendAck(bit ack)
{
	I2C_SDA = ack;
	I2CDelay();//��ʱ����4us ʹSCL���ֵ�
	I2C_SCL = 1;//���� ����������λ
	I2CDelay();//��ʱ����4us ʹSCL���ָ�
	I2C_SCL = 0;//���� Ϊ��һ�δ�����׼��
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
