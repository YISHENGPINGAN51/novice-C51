#ifndef __DS18B20_H_
#define __DS18B20_H_

#include "OneWire.h"

//ROM指令
#define SEARCH_ROM               0xf0   //搜索ROM指令
#define READ_ROM                 0x33   //读取ROM指令
#define MATH_ROM                 0x55   //匹配ROM指令
#define SKIP_ROM                 0xcc   //跳过ROM指令
#define ALARM_SEARCH             0xec   //报警搜索指令

//暂存器指令
#define CONVERT_T                0x44   //温度转换指令
#define WRITE_REGISTER           0x4e   //写暂存器指令
#define READ_REGISTER            0xbe   //读取暂存器指令
#define COPY_REGISTER            0x48   //拷贝暂存器指令
#define RECALL_E2                0xb8   //召回EEPROM指令
#define READ_POWER_SUPPLY        0xb4   //读取电源模式指令

bit Start18B20();
bit Read18B20(int *temp);
void ReadRomCode(unsigned char *romcode);

#endif
