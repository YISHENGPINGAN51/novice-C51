#include "EEPROM.h"

/********************************************************************
函数名：E2ReadByte
功  能：读取器件地址为IC_Addr的器件的内部字节地址addr中的数据
参  数：IC_Addr-从器件地址  addr-器件内部字节地址
返回值：dat-读取的一字节数据
********************************************************************/
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

/********************************************************************
函数名：E2WriteByte
功  能：写入一字节数据到从机器件地址为IC_Addr的内部字节地址addr
参  数：IC_Addr-从器件地址  addr-器件内部字节地址  dat-待写入数据
返回值：无
********************************************************************/
void E2WriteByte(unsigned char IC_Addr, unsigned char addr, unsigned char dat)
{
	I2CStart();//启动总线
	I2CWriteByte(IC_Addr << 1);//器件寻址，执行写操作 从机应答在函数内部实现
	I2CWriteByte(addr);//写内部字节地址，告诉器件要从哪个地方开始读数据
	I2CWriteByte(dat);//写数据
	I2CStop();//发完Stop后，器件才会把数据进行擦写，搬运到非易失区，
						//这段时间里面器件不再响应主机的操作
}

/********************************************************************
函数名：E2Read
功  能：从器件地址为IC_Addr的器件的内部字节地址addr开始读取len字节的数据，保存到buf
参  数：IC_Addr-从器件地址  addr-器件内部字节地址
				*buf-保存读取的数据缓冲  len-读取的字节个数 < 0xFF - addr
返回值：无
********************************************************************/
void E2Read(unsigned char IC_Addr, unsigned char addr, unsigned char *buf, unsigned char len)
{
	do{
			I2CStart();//启动总线
			if (!(I2CWriteByte(IC_Addr << 1)))//器件寻址，执行写操作 从机应答在函数内部实现
			{
				break;
			}
			I2CStop();
		}  while (1);
//	I2CStart();//启动总线
//	I2CWriteByte(IC_Addr << 1);//器件寻址，执行写操作 从机应答在函数内部实现
	I2CWriteByte(addr);//写内部字节地址，告诉器件要从哪个地方开始读数据
	I2CStart();//重启总线
	I2CWriteByte((IC_Addr << 1) | 0x01);//后续操作为读操作，从地址addr开始读数据
	while (len > 1)
	{
		*buf++ = I2CReadByte();//从总线上读一个字节数据
		SendAck(0);//主机读多个字节，发NACK 发1 如果还继续读就发ACK 发0
		len--;
	}
	*buf = I2CReadByte();//从总线上读一个字节数据
	SendAck(1);//主机只读一个字节，发NACK 发1 如果还继续读就发ACK 发0
	I2CStop();
}

/********************************************************************
函数名：E2Write
功  能：写len个字节到从机器件地址为IC_Addr的内部字节地址addr开始的一段字节地址中
参  数：IC_Addr-从机器件地址  addr-器件内部字节地址
				buf-待写入数据缓冲区  len-待写入数据的字节个数
返回值：无
********************************************************************/
void E2Write(unsigned char IC_Addr, unsigned char addr, unsigned char *buf, unsigned char len)
{
	while (len > 0)
	{
		do{
				I2CStart();//启动总线
				if (!(I2CWriteByte(IC_Addr << 1)))//器件寻址，执行写操作 从机应答在函数内部实现
				{
					break;
				}
				I2CStop();
		}  while (1);//为了防止死循环，可以增加一个i变量做累加判断，如果超过一定的时间还没有响应，退出循环
		I2CWriteByte(addr++);//写内部字节地址，告诉器件要从哪个地方开始读数据
		I2CWriteByte(*buf++);//写数据
		I2CStop();//发完Stop后，器件才会把数据进行擦写，搬运到非易失区，
							//这段时间里面器件不再响应主机的操作
//		DelayXms(10);
		len--;
	}
}

/********************************************************************
函数名：E2WritePage
功  能：按页写（8字节一页）写len个字节到从机器件地址为IC_Addr的内部字节地址addr开始的一段字节地址中
参  数：IC_Addr-从机器件地址  addr-器件内部字节地址
				buf-待写入数据缓冲区  len-待写入数据的字节个数
返回值：0-写入字节个数超过存储空间的字节数  1-正常写入
********************************************************************/
unsigned char E2WritePage(unsigned char IC_Addr, unsigned char addr, unsigned char *buf, unsigned char len)
{
	if ((Max_addr - addr) < len)//如果待写入的字节数len大于剩余的存储空间字节数，则直接返回，不执行写入
		return 0;
	while (len > 0)//e.g. 10字节写入
	{
		do{
				I2CStart();//启动总线
				if (!(I2CWriteByte(IC_Addr << 1)))//器件寻址，执行写操作 从机应答在函数内部实现
				{
					break;
				}
				I2CStop();
		}  while (1);//为了防止死循环，可以增加一个i变量做累加判断，如果超过一定的时间还没有响应，退出循环
		I2CWriteByte(addr);//写内部页起始字节地址，告诉器件要从哪个地方开始读数据
		while (len > 0)
		{
			I2CWriteByte(*buf++);//写数据
			addr++;//每写入一个字节，字节地址addr++
			len--;
			if ((addr & PageByte) == 0)
			{
				break;
			}
		}
		I2CStop();//发完Stop后，器件才会把数据进行擦写，搬运到非易失区，
							//这段时间里面器件不再响应主机的操作
	}
	return 1;
}
