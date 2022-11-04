#include "LCD1602.h"

/*****************************************************
��������LCDReadBF
��  �ܣ�1602��æ���
��  ������
����ֵ����
*****************************************************/
#ifndef LCD1602_4PINS
void LCDReadBF()
{
	unsigned char state;
	unsigned char i;
	LCD1602_DB |= 0xFF;//����λIO��1  ����λ���ֲ���
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
#else
void LCDReadBF()
{
	unsigned char state;
	unsigned char i;
	LCD1602_DB |= 0xF0;//����λIO��1  ����λ���ֲ���
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do
	{
		LCD1602_EN = 1;
		state = LCD1602_DB & 0xF0;//������λ
		LCD1602_EN = 0;
		
		LCD1602_EN = 1;
		state |= (LCD1602_DB & 0xF0) >> 4;//������λ
		LCD1602_EN = 0;
		
		i++;
		if (i > 50)
			break;
	}  while (state & 0x80);
}
#endif

/*****************************************************
��������LCDWriteCmd
��  �ܣ�LCD1602дָ��
��  ����cmd ��дָ��
����ֵ����
*****************************************************/
#ifndef LCD1602_4PINS
void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//�ȴ�æ��⣬��æʱ����
	LCD1602_RS = 0;//����
	LCD1602_RW = 0;//д
	LCD1602_DB = cmd;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}
#else
void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//�ȴ�æ��⣬��æʱ����
	LCD1602_RS = 0;//����
	LCD1602_RW = 0;//д
	LCD1602_DB = cmd;//����λ
	DelayXms(1);
	LCD1602_EN = 1;
	LCD1602_EN = 0;
	LCD1602_DB = cmd << 4;//����λ
	DelayXms(1);
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}
#endif

/*****************************************************
��������LCDWriteData
��  �ܣ�LCD1602д����
��  ����dat ��д������
����ֵ����
*****************************************************/
#ifndef LCD1602_4PINS
void LCDWriteData(unsigned char dat)
{
	LCDReadBF();//�ȴ�æ��⣬��æʱ����
	LCD1602_RS = 1;//����
	LCD1602_RW = 0;//д
	LCD1602_DB = dat;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}
#else
void LCDWriteData(unsigned char dat)
{
	LCDReadBF();//�ȴ�æ��⣬��æʱ����
	LCD1602_RS = 1;//����
	LCD1602_RW = 0;//д
	LCD1602_DB = dat;//����λ
	DelayXms(1);
	LCD1602_EN = 1;
	LCD1602_EN = 0;
	LCD1602_DB = dat << 4;//����λ
	DelayXms(1);
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}
#endif

/*****************************************************
��������LCDInit
��  �ܣ�LCD1602��ʼ��
��  ������
����ֵ����
*****************************************************/
#ifndef LCD1602_4PINS
void LCDInit()
{
	LCDWriteCmd(LCD_MODE_PIN8);//��ʾģʽ���� 2�� 5*8����
	LCDWriteCmd(LCD_DIS_ON);//��ʾ��������
	LCDWriteCmd(LCD_CURSOR_RIGHT);//�������
	LCDWriteCmd(LCD_SCREEN_CLR);//����
}
#else
void LCDInit()
{
	//��Ӣ���ֲ�
	LCDWriteCmd(0x33);
	DelayXms(5);
	LCDWriteCmd(0x32);
	
	LCDWriteCmd(LCD_MODE_PIN4);//��ʾģʽ���� 2�� 5*8����
	LCDWriteCmd(LCD_DIS_ON);//��ʾ��������
	LCDWriteCmd(LCD_CURSOR_RIGHT);//�������
	LCDWriteCmd(LCD_SCREEN_CLR);//����
}
#endif

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

/*****************************************************
��������IntegerToStr
��  �ܣ���������ת�ַ���
��  ����dat-��������  *str-�ַ�����
����ֵ��len-�ַ�������ַ�����  ����
*****************************************************/
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
