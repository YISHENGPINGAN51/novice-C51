#include "Key.h"

unsigned char Key_Scan()
{
	unsigned char KeyNum = 0;
	
	KEY1 = 1;
	KEY2 = 1;
	KEY3 = 1;
	KEY4 = 1;
	
	/*if (!KEY1)           //1、判断是否有按键按下
	{
		DelayXms(10);      //2、延时消抖  时间一般5-10ms
		if (!KEY1)         //3、再次判断按键是否按下
		{
			KeyNum = 1;      //4、键值的软件编码，赋一个键值，不直接做按键功能
		}  while (!KEY1);  //5、松手等待
	}
	
	if (!KEY2)           //1、判断是否有按键按下
	{
		DelayXms(10);      //2、延时消抖  时间一般5-10ms
		if (!KEY2)         //3、再次判断按键是否按下
		{
			KeyNum = 2;      //4、键值的软件编码，赋一个键值，不直接做按键功能
		}  while (!KEY2);  //5、松手等待
	}
	
	if (!KEY3)           //1、判断是否有按键按下
	{
		DelayXms(10);      //2、延时消抖  时间一般5-10ms
		if (!KEY3)         //3、再次判断按键是否按下
		{
			KeyNum = 3;      //4、键值的软件编码，赋一个键值，不直接做按键功能
		}  while (!KEY3);  //5、松手等待
	}
	
	if (!KEY4)           //1、判断是否有按键按下
	{
		DelayXms(10);      //2、延时消抖  时间一般5-10ms
		if (!KEY4)         //3、再次判断按键是否按下
		{
			KeyNum = 4;      //4、键值的软件编码，赋一个键值，不直接做按键功能
		}  while (!KEY4);  //5、松手等待
	}*/
	if (!KEY1 || !KEY2 || !KEY3 || !KEY4)
	{
		DelayXms(10);
		if (!KEY1 || !KEY2 || !KEY3 || !KEY4)
		{
			if (!KEY1)
				KeyNum = 1;
			if (!KEY2)
				KeyNum = 2;
			if (!KEY3)
				KeyNum = 3;
			if (!KEY4)
				KeyNum = 4;
		}  while (!KEY1 || !KEY2 || !KEY3 || !KEY4);
	}
	
	return KeyNum;
}