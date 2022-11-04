#include "EEPROM.h"

/***************************************************************
��������E2ReadByte
��  �ܣ���ȡ������ַΪIC_Addr���������ڲ��ֽڵ�ַaddr�е�����
��  ����IC_Addr-������ַ  addr-�������ڲ��ֽڵ�ַ
����ֵ��dat-��ȡ��һ�ֽ�����
***************************************************************/
unsigned char E2ReadByte(unsigned char IC_Addr, unsigned char addr)
{
	unsigned char dat;
	I2CStart();//��������
	I2CWriteByte(IC_Addr << 1);//����Ѱַ��ִ��д���� �ӻ�Ӧ���ں����ڲ�ʵ��
	I2CWriteByte(addr);//д�ڲ��ֽڵ�ַ����������Ҫ���ĸ��ط���ʼ������
	I2CStart();//��������
	I2CWriteByte((IC_Addr << 1) | 0x01);//��������Ϊ���������ӵ�ַaddr��ʼ������
	dat = I2CReadByte();//�������϶�һ���ֽ�����
	SendAck(1);//����ֻ��һ���ֽڣ���NACK ��1 ������������ͷ�ACK ��0
	I2CStop();
	return dat;
}

void E2WriteByte(unsigned char IC_Addr, unsigned char addr, unsigned char dat)
{
	I2CStart();//��������
	I2CWriteByte(IC_Addr << 1);//����Ѱַ��ִ��д���� �ӻ�Ӧ���ں����ڲ�ʵ��
	I2CWriteByte(addr);//д�ڲ��ֽڵ�ַ����������Ҫ���ĸ��ط���ʼ������
	I2CWriteByte(dat);//д����
	I2CStop();//����Stop�������Ż�����ݽ��в�д�����˵�����ʧ����
						//���ʱ����������������Ӧ�����Ĳ���
}