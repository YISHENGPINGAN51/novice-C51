#include "Key.h"

unsigned char Key_Scan()
{
	unsigned char KeyNum = 0;
	
	KEY1 = 1;
	KEY2 = 1;
	KEY3 = 1;
	KEY4 = 1;
	
	/*if (!KEY1)           //1���ж��Ƿ��а�������
	{
		DelayXms(10);      //2����ʱ����  ʱ��һ��5-10ms
		if (!KEY1)         //3���ٴ��жϰ����Ƿ���
		{
			KeyNum = 1;      //4����ֵ��������룬��һ����ֵ����ֱ������������
		}  while (!KEY1);  //5�����ֵȴ�
	}
	
	if (!KEY2)           //1���ж��Ƿ��а�������
	{
		DelayXms(10);      //2����ʱ����  ʱ��һ��5-10ms
		if (!KEY2)         //3���ٴ��жϰ����Ƿ���
		{
			KeyNum = 2;      //4����ֵ��������룬��һ����ֵ����ֱ������������
		}  while (!KEY2);  //5�����ֵȴ�
	}
	
	if (!KEY3)           //1���ж��Ƿ��а�������
	{
		DelayXms(10);      //2����ʱ����  ʱ��һ��5-10ms
		if (!KEY3)         //3���ٴ��жϰ����Ƿ���
		{
			KeyNum = 3;      //4����ֵ��������룬��һ����ֵ����ֱ������������
		}  while (!KEY3);  //5�����ֵȴ�
	}
	
	if (!KEY4)           //1���ж��Ƿ��а�������
	{
		DelayXms(10);      //2����ʱ����  ʱ��һ��5-10ms
		if (!KEY4)         //3���ٴ��жϰ����Ƿ���
		{
			KeyNum = 4;      //4����ֵ��������룬��һ����ֵ����ֱ������������
		}  while (!KEY4);  //5�����ֵȴ�
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