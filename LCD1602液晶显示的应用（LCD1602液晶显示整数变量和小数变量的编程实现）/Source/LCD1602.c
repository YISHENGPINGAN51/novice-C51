#include "LCD1602.h"

/*****************************************************
��������LCDReadBF
��  �ܣ�1602��æ���
��  ������
����ֵ����
*****************************************************/
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

/*****************************************************
��������LCDWriteCmd
��  �ܣ�LCD1602дָ��
��  ����cmd ��дָ��
����ֵ����
*****************************************************/
void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//�ȴ�æ��⣬��æʱ����
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

/*****************************************************
��������LCDWriteData
��  �ܣ�LCD1602д����
��  ����dat ��д������
����ֵ����
*****************************************************/
void LCDWriteData(unsigned char dat)
{
	LCDReadBF();//�ȴ�æ��⣬��æʱ����
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

/*****************************************************
��������LCDInit
��  �ܣ�LCD1602��ʼ��
��  ������
����ֵ����
*****************************************************/
void LCDInit()
{
	LCDWriteCmd(LCD_MODE_PIN8);//��ʾģʽ���� 2�� 5*8����
	LCDWriteCmd(LCD_DIS_ON);//��ʾ��������
	LCDWriteCmd(LCD_CURSOR_RIGHT);//�������
	LCDWriteCmd(LCD_SCREEN_CLR);//����
}

/*****************************************************
��������LCDSetPosition
��  �ܣ�������ʾλ��  DDRAM��ַ
��  ����x-��  y-��  x:0-15  y:0-1
����ֵ����
*****************************************************/
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

/*****************************************************
��������LCDShowStr
��  �ܣ���ʾ�ַ�
��  ����x-��  y-��  *str-����ʾ�ַ�����
����ֵ����
*****************************************************/
void LCDShowStr(unsigned char x, unsigned char y, unsigned char *str)
{
	LCDSetPosition(x, y);
	while (*str != '\0')
	{
		LCDWriteData(*str++);
	}
}

/*****************************************************
��������LCDWriteCGRAM
��  �ܣ���ʾ�Զ����ַ�
��  ����*str-�Զ����ַ�����
����ֵ����
*****************************************************/
void LCDWriteCGRAM(unsigned char *str)
{
	unsigned char i;
	LCDWriteCmd(LCD_SET_CGRAM_ADDR);//�趨 CGRAM ��ַ
	for (i = 0; i < 8; i++)
	{
		LCDWriteData(*str++);//д���Զ���ͼ��
	}
	LCDWriteCmd(0xC0);//�趨��Ļ�ϵ���ʾλ��
	LCDWriteData(0x00);//�� CGRAM ��ȡ���Զ���ͼ����ʾ
}

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
		LCDWriteCmd(LCD_SET_CGRAM_ADDR + pos*8 + i);
		LCDWriteData(*(str+i));
	}
	//��ʾ
	LCDSetPosition(x, y);//������ʾλ�� DDRAM
	LCDWriteData(0x00 + pos);//��ʾ����
}
