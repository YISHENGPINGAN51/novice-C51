#include "Key.h"

unsigned char Key_Scan()
{
	unsigned char KeyNum = 0;
	
	START = 1;
	STOP = 1;
	DOWN = 1;
	UP = 1;
	
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
	if (!START || !STOP || !DOWN || !UP)
	{
		DelayXms(10);
		if (!START || !STOP || !DOWN || !UP)
		{
			if (!START)
				KeyNum = 1;
			if (!STOP)
				KeyNum = 2;
			if (!DOWN)
				KeyNum = 3;
			if (!UP)
				KeyNum = 4;
		}  while (!START || !STOP || !DOWN || !UP);
	}
	
	return KeyNum;
}