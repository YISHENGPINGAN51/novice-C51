#include "menu.h"

extern int TEMPbuf[];

void Startmenu()
{
	LCDShowStr(1, 0, "The DAS of TEMP");
	LCDShowStr(6, 1, "V1.0");
}

void SubMenuOne()
{
	LCDShowStr(0, 0, "CH0:");//第一行 显示DS18B20 #1
	ShowTempData(TEMPbuf, 0);
	LCDShowStr(0, 1, "CH1:");//第二行 显示DS18B20 #2
	ShowTempData(TEMPbuf, 1);
}

void SubMenuTwo()
{
	LCDShowStr(0, 0, "CH2:");//第二个界面 第一行 显示DS18B20 #3
	ShowTempData(TEMPbuf, 2);
	LCDShowStr(0, 1, "CH3:");
	ShowTempData(TEMPbuf, 3);//第二个界面 第二行 显示DS18B20 #4
}

void ShowTempData(int *buf, unsigned char num)
{
	int temp;        //读取到的当前温度值
	float tmp;
	temp = *(buf + num);  //buf[num]
	if (temp < 0)       //当温度值为负数
	{
		if (num % 2)//奇数
	  	LCDWriteCmd(0xC5);    //写地址 C5表示初始地址 第二行
		else
			LCDWriteCmd(0x85);    //写地址 85表示初始地址 第一行
		LCDWriteData('-');    //显示负
		temp = ~temp;  //补码存放，取反加一求原码
		temp = temp + 1;
		tmp = temp;
		temp = tmp * 0.0625 * 100;  //小数点后保留两位
	}
	else//温度为正数的时候
	{
		if (num % 2)//奇数
	  	LCDWriteCmd(0xC5);    //写地址 C5表示初始地址 第二行
		else
			LCDWriteCmd(0x85);    //写地址 85表示初始地址 第一行
		LCDWriteData(' ');    //显示空
		tmp = temp;              //正数
		temp = tmp * 0.0625 * 100;  //小数点后保留两位
	}
	if (temp >= 10000)//如果温度大于等于100℃
	{
		if (num % 2)//奇数
	  	LCDWriteCmd(0xC7);    //写地址 C7表示初始地址 第二行
		else
			LCDWriteCmd(0x87);    //写地址 87表示初始地址 第一行
		LCDWriteData('0' + temp / 10000);    //百位
		LCDWriteData('0' + temp % 10000 / 1000);    //十位
		LCDWriteData('0' + temp % 1000 / 100);    //个位
		LCDWriteData('.');    //显示  ‘.'
		LCDWriteData('0' + temp % 100 / 10);    //显示小数点
		LCDWriteData('0' + temp % 10);    //显示小数点
	}
	else //温度小于100
	{
		if (temp >= 1000)//如果温度大于等于10℃
		{
			if (num % 2)//奇数
	  	LCDWriteCmd(0xC7);    //写地址 C7表示初始地址 第二行
		else
			LCDWriteCmd(0x87);    //写地址 87表示初始地址 第一行
			LCDWriteData('0' + temp % 10000 / 1000);    //十位
			LCDWriteData('0' + temp % 1000 / 100);    //个位
			LCDWriteData('.');    //显示  ‘.'
			LCDWriteData('0' + temp % 100 / 10);    //显示小数点
			LCDWriteData('0' + temp % 10);    //显示小数点
			LCDWriteData(' ');    //数据对齐，清除原有的显示
		}
		else
		{
			if (num % 2)//奇数
	  	LCDWriteCmd(0xC7);    //写地址 C7表示初始地址 第二行
		else
			LCDWriteCmd(0x87);    //写地址 87表示初始地址 第一行
			LCDWriteData('0' + temp % 1000 / 100);    //个位
			LCDWriteData('.');    //显示  ‘.'
			LCDWriteData('0' + temp % 100 / 10);    //显示小数点
			LCDWriteData('0' + temp % 10);    //显示小数点
			LCDWriteData(' ');    //数据对齐，清除原有的显示
			LCDWriteData(' ');    //数据对齐，清除原有的显示
		}
	}
}
