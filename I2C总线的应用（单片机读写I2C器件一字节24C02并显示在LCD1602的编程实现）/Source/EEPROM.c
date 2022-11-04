#include "EEPROM.h"

/***************************************************************
函数名：E2ReadByte
功  能：读取器件地址为IC_Addr的器件的内部字节地址addr中的数据
参  数：IC_Addr-器件地址  addr-器件的内部字节地址
返回值：dat-读取的一字节数据
***************************************************************/
unsigned char E2ReadByte(unsigned char IC_Addr, unsigned char addr)
{
	unsigned char dat;
	I2CStart();//启动总线
	I2CWriteByte(IC_Addr << 1);//器件寻址，执行写操作 从机应答在函数内部实现
	I2CWriteByte(addr);//写内部字节地址，告诉器件要从哪个地方开始读数据
	I2CStart();//重启总线
	I2CWriteByte((IC_Addr << 1) | 0x01);//后续操作为读操作，从地址addr开始读数据
	dat = I2CReadByte();//从总线上读一个字节数据
	SendAck(1);//主机只读一个字节，发NACK 发1 如果还继续读就发ACK 发0
	I2CStop();
	return dat;
}

void E2WriteByte(unsigned char IC_Addr, unsigned char addr, unsigned char dat)
{
	I2CStart();//启动总线
	I2CWriteByte(IC_Addr << 1);//器件寻址，执行写操作 从机应答在函数内部实现
	I2CWriteByte(addr);//写内部字节地址，告诉器件要从哪个地方开始读数据
	I2CWriteByte(dat);//写数据
	I2CStop();//发完Stop后，器件才会把数据进行擦写，搬运到非易失区，
						//这段时间里面器件不再响应主机的操作
}