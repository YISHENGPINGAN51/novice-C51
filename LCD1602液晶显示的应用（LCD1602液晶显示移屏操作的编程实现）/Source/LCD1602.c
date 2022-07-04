#include "LCD1602.h"

//unsigned char code str[] = { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00 };

void LCDReadBF()
{
	unsigned char state;
	unsigned char i;
	LCD1602_DB = 0xFF;//IO����1 ������
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do
	{
		LCD1602_EN = 1;
		state = LCD1602_DB;
		LCD1602_EN = 0;
		i++;
		if (i > 50)
			break;
	}  while (state & 0x80);
}

void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//�ȴ�æ��⣬��æʱ����
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

void LCDWriteData(unsigned char dat)
{
	LCDReadBF();//�ȴ�æ��⣬��æʱ����
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

void LCDInit()
{
	LCDWriteCmd(LCD_MODE_PIN8);//��ʾģʽ���� 2�� 5*8����
	LCDWriteCmd(LCD_DIS_ON);//��ʾ��������
	LCDWriteCmd(LCD_CURSOR_RIGHT);//�������
	LCDWriteCmd(LCD_SCREEN_CLR);//����
}


void LCDSetPosition(unsigned char x, unsigned char y)
{
	if (0 == y)
	{
		LCDWriteCmd(0x80 | x);
	}
	else
	{
		LCDWriteCmd(0x80 | (0x40 + x));
	}
}
	
void LCDShowStr(unsigned char x, unsigned char y, unsigned char *str)
{
	LCDSetPosition(x, y);
	while (*str != '\0')
	{
		LCDWriteData(*str++);
	}
}

//��һ�ַ���
//void LCDWriteCGRAM()
//{
//	unsigned char i;
//	LCDWriteCmd(0x40);//1�������Զ����ַ�
//	for (i = 0; i < 64; i++)
//	{
//		LCDWriteData(str[i]);
//	}
//	//2����ʾ����ַ�
//	LCDWriteCmd(0x80 | 0x00);
//	LCDWriteData(0x01);
//}

//�ڶ��ַ���
/*****************************************************
��������LCDSetChar
��  �ܣ���ʾ�Զ����ַ�
��  ����x-��  y-��  pos-CGRAMλ��  *str-�Զ����ַ�����
����ֵ����
*****************************************************/
void LCDSetChar(unsigned char x, unsigned char y, unsigned char pos, unsigned char *str)//x:0~F y:0/1 pos:0~7
{
	unsigned char i;
	//�ȹ����Զ����ַ� ȷ��λ�� CGRAM
	for (i = 0; i < 8; i++)
	{
		LCDWriteCmd(0x40 + pos*8 + i);
		LCDWriteData(*(str+i));
	}
	//��ʾ
	LCDSetPosition(x, y);//������ʾλ�� DDRAM
	LCDWriteData(0x00 + pos);//��ʾ����
}
