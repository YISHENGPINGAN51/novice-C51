#include "menu.h"

extern int TEMPbuf[];

void Startmenu()
{
	LCDShowStr(1, 0, "The DAS of TEMP");
	LCDShowStr(6, 1, "V1.0");
}

void SubMenuOne()
{
	LCDShowStr(0, 0, "CH0:");//��һ�� ��ʾDS18B20 #1
	ShowTempData(TEMPbuf, 0);
	LCDShowStr(0, 1, "CH1:");//�ڶ��� ��ʾDS18B20 #2
	ShowTempData(TEMPbuf, 1);
}

void SubMenuTwo()
{
	LCDShowStr(0, 0, "CH2:");//�ڶ������� ��һ�� ��ʾDS18B20 #3
	ShowTempData(TEMPbuf, 2);
	LCDShowStr(0, 1, "CH3:");
	ShowTempData(TEMPbuf, 3);//�ڶ������� �ڶ��� ��ʾDS18B20 #4
}

void ShowTempData(int *buf, unsigned char num)
{
	int temp;        //��ȡ���ĵ�ǰ�¶�ֵ
	float tmp;
	temp = *(buf + num);  //buf[num]
	if (temp < 0)       //���¶�ֵΪ����
	{
		if (num % 2)//����
	  	LCDWriteCmd(0xC5);    //д��ַ C5��ʾ��ʼ��ַ �ڶ���
		else
			LCDWriteCmd(0x85);    //д��ַ 85��ʾ��ʼ��ַ ��һ��
		LCDWriteData('-');    //��ʾ��
		temp = ~temp;  //�����ţ�ȡ����һ��ԭ��
		temp = temp + 1;
		tmp = temp;
		temp = tmp * 0.0625 * 100;  //С���������λ
	}
	else//�¶�Ϊ������ʱ��
	{
		if (num % 2)//����
	  	LCDWriteCmd(0xC5);    //д��ַ C5��ʾ��ʼ��ַ �ڶ���
		else
			LCDWriteCmd(0x85);    //д��ַ 85��ʾ��ʼ��ַ ��һ��
		LCDWriteData(' ');    //��ʾ��
		tmp = temp;              //����
		temp = tmp * 0.0625 * 100;  //С���������λ
	}
	if (temp >= 10000)//����¶ȴ��ڵ���100��
	{
		if (num % 2)//����
	  	LCDWriteCmd(0xC7);    //д��ַ C7��ʾ��ʼ��ַ �ڶ���
		else
			LCDWriteCmd(0x87);    //д��ַ 87��ʾ��ʼ��ַ ��һ��
		LCDWriteData('0' + temp / 10000);    //��λ
		LCDWriteData('0' + temp % 10000 / 1000);    //ʮλ
		LCDWriteData('0' + temp % 1000 / 100);    //��λ
		LCDWriteData('.');    //��ʾ  ��.'
		LCDWriteData('0' + temp % 100 / 10);    //��ʾС����
		LCDWriteData('0' + temp % 10);    //��ʾС����
	}
	else //�¶�С��100
	{
		if (temp >= 1000)//����¶ȴ��ڵ���10��
		{
			if (num % 2)//����
	  	LCDWriteCmd(0xC7);    //д��ַ C7��ʾ��ʼ��ַ �ڶ���
		else
			LCDWriteCmd(0x87);    //д��ַ 87��ʾ��ʼ��ַ ��һ��
			LCDWriteData('0' + temp % 10000 / 1000);    //ʮλ
			LCDWriteData('0' + temp % 1000 / 100);    //��λ
			LCDWriteData('.');    //��ʾ  ��.'
			LCDWriteData('0' + temp % 100 / 10);    //��ʾС����
			LCDWriteData('0' + temp % 10);    //��ʾС����
			LCDWriteData(' ');    //���ݶ��룬���ԭ�е���ʾ
		}
		else
		{
			if (num % 2)//����
	  	LCDWriteCmd(0xC7);    //д��ַ C7��ʾ��ʼ��ַ �ڶ���
		else
			LCDWriteCmd(0x87);    //д��ַ 87��ʾ��ʼ��ַ ��һ��
			LCDWriteData('0' + temp % 1000 / 100);    //��λ
			LCDWriteData('.');    //��ʾ  ��.'
			LCDWriteData('0' + temp % 100 / 10);    //��ʾС����
			LCDWriteData('0' + temp % 10);    //��ʾС����
			LCDWriteData(' ');    //���ݶ��룬���ԭ�е���ʾ
			LCDWriteData(' ');    //���ݶ��룬���ԭ�е���ʾ
		}
	}
}
