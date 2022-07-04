#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include <stdio.h>

unsigned char IntegerToStr(long dat, unsigned char *str);

void main()
{
	long dat = -12345678;//uli_max:4294967295  li_max:-2147483648~+2147483647
	unsigned char str[11];//eg:"4294967295\0"
	
	float num = 1.252;
	float num2 = 12.234;
	unsigned char lcdbuf[10];
	int temp;
	
	LCDInit();
	DelayXms(10);
	
	//�����������̶�������ʾ����
	IntegerToStr(dat, str);
	LCDShowStr(0, 0, str);
	
	//С������ȷ��С����λ��ʱ��ʾ����
	temp = num * 1000;
	LCDSetPosition(0, 1);
	LCDWriteData(temp / 1000 + '0');
	LCDWriteData('.');
	LCDWriteData(temp / 100 % 10 + '0');
	LCDWriteData(temp / 10 % 10 + '0');
	LCDWriteData(temp % 10 + '0');
	
	//С��������ȷ��С����λ��ʱ��ʾ����
	sprintf(lcdbuf, "%0.4f", num2);
	LCDShowStr(8,1,lcdbuf);
	while (1);
}

unsigned char IntegerToStr(long dat, unsigned char *str)
{
	unsigned char i;
	unsigned char len;
	unsigned char buf[11];
	if (dat < 0)
	{
		dat = -dat;//����Ǹ�����ȡ����ֵ
		*str++ = '-';
		len++;
	}
	do
	{
		buf[i++] = dat % 10 + '0';//�ȼ���dat % 10 + 0x30;  buf[0] = '8' buf[1] = '7' buf[2] = '6'
		dat /= 10;
	}  while (dat > 0);
	len += i;
	while (i-- > 0)
	{
		*str++ = buf[i];
	}
	*str = '\0';
	return len;
}