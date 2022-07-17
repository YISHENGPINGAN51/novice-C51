#include "OneWire.h"

/*****************************************************
函数名：OneWireRst
功  能：单总线复位，获取存在脉冲
参  数：无
返回值：0-单总线应答 1-无应答
*****************************************************/
bit OneWireRst()
{
	bit ack;
	EA = 0;
	DS18B20 = 0;//拉低总线，发复位脉冲
	Delay600us();//480us - 960us 取600us
	DS18B20 = 1;
	Delay60us();//15us - 60us 取60us
	ack = DS18B20;//读取IO口 18B20的ack
	while (!DS18B20);//等待18B20释放总线，等待存在脉冲结束
	EA = 1;
	return ack;
}

/*****************************************************
函数名：WriteOneWire
功  能：单总线写一个字节
参  数：unsigned char dat
返回值：无
*****************************************************/
void WriteOneWire(unsigned char dat)
{
	unsigned char tmp;
	EA = 0;
	for (tmp = 0x01; tmp != 0; tmp <<= 1)
	{
		DS18B20 = 0;//拉低至少1us
		_nop_();
		_nop_();
		if ((dat & tmp) == 0)
			DS18B20 = 0;
		else
			DS18B20 = 1;
		Delay60us();
		DS18B20 = 1;
	}
	EA = 1;
}

/*****************************************************
函数名：ReadOneWire
功  能：单总线读一个字节
参  数：无
返回值：dat-读到的数据
*****************************************************/
unsigned char ReadOneWire()
{
	unsigned char dat;
	unsigned char tmp;
	EA = 0;
	for (tmp = 0x01; tmp != 0; tmp <<= 1)
	{
		DS18B20 = 0;
		_nop_();
		_nop_();
		DS18B20 = 1;
		_nop_();
		_nop_();
		if (!DS18B20)
			dat &= ~tmp;
		else
			dat |= tmp;
		Delay60us();
	}
	EA = 1;
	return dat;
}