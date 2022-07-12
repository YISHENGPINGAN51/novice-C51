#ifndef __DS18B20_H_
#define __DS18B20_H_

#include "OneWire.h"

//ROMָ��
#define SEARCH_ROM               0xf0   //����ROMָ��
#define READ_ROM                 0x33   //��ȡROMָ��
#define MATH_ROM                 0x55   //ƥ��ROMָ��
#define SKIP_ROM                 0xcc   //����ROMָ��
#define ALARM_SEARCH             0xec   //��������ָ��

//�ݴ���ָ��
#define CONVERT_T                0x44   //�¶�ת��ָ��
#define WRITE_REGISTER           0x4e   //д�ݴ���ָ��
#define READ_REGISTER            0xbe   //��ȡ�ݴ���ָ��
#define COPY_REGISTER            0x48   //�����ݴ���ָ��
#define RECALL_E2                0xb8   //�ٻ�EEPROMָ��
#define READ_POWER_SUPPLY        0xb4   //��ȡ��Դģʽָ��

bit Start18B20();
bit Read18B20(int *temp);
void ReadRomCode(unsigned char *romcode);

#endif
