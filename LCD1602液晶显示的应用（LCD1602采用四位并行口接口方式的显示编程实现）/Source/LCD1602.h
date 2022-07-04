#ifndef __LCD1602_H_
#define __LCD1602_H_

#include <reg51.h>
#include "delay.h"

#define LCD1602_4PINS //��������� LCD1602_4PINS ����ʹ��4λ���нӿڷ�ʽ
                      //����ʹ��8λ���нӿڷ�ʽ

//IO�ӿڵ�����
#define LCD1602_DB P0
sbit LCD1602_RS = P2^5;
sbit LCD1602_RW = P2^6;
sbit LCD1602_EN = P2^7;

//unsigned char code str[];

//LCD1602ָ��
//��ʾģʽָ��
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//   0   0   1  DL   N   F   *   *
// DL = 1��8λ���ݽӿڣ� DL = 0��4λ���ݽӿڡ�
// N  = 1��������ʾ��    N  = 0��������ʾ��
// F  = 1��5*10�����ַ���F  = 0��5*8�����ַ���
#define LCD_MODE_PIN8         0x38  //8λ���ݿڣ����У�5*8����
#define LCD_MODE_PIN4         0x28  //4λ���ݿڣ����У�5*8����

#define LCD_SCREEN_CLR        0x01  //����
#define LCD_CURSOR_RST        0x02  //��긴λ

//��ʾ���ؿ���ָ��
#define LCD_DIS_CUR_BLK_ON    0x0F  //��ʾ������꿪�������˸
#define LCD_DIS_CUR_ON        0x0E  //��ʾ������꿪����겻��˸
#define LCD_DIS_ON            0x0C  //��ʾ�������أ���겻��˸
#define LCD_DIS_OFF           0x08  //��ʾ�أ����أ���겻��˸

//��ʾģʽ����
#define LCD_CURSOR_RIGHT      0x06  //������ƣ���ʾ���ƶ�
#define LCD_CURSOR_LEFT       0x04  //������ƣ���ʾ���ƶ�
#define LCD_DIS_MODE_LEFT     0x07  //������AC����������ƽ��
#define LCD_DIS_MODE_RIGHT    0x05  //������AC�Լ�������ƽ��

//��꣬��ʾ�ƶ�ָ��
#define LCD_CUR_MOVE_LEFT     0x10  //�������
#define LCD_CUR_MOVE_RIGHT    0x14  //�������
#define LCD_DIS_MOVE_LEFT     0x18  //��ʾ����
#define LCD_DIS_MOVE_RIGHT    0x1C  //��ʾ����

//CGRAM��ַ
#define LCD_SET_CGRAM_ADDR    0x40

void LCDReadBF();//��æ���
void LCDWriteCmd(unsigned char cmd);//д����
void LCDWriteData(unsigned char dat);//д����
void LCDInit();//��ʼ��
void LCDSetPosition(unsigned char x, unsigned char y);//ȷ����ʾλ��
void LCDShowStr(unsigned char x, unsigned char y, unsigned char *str);//��ʾ�����ַ�����
void LCDWriteCGRAM(unsigned char *str);//��ʾ�û��Զ����ַ�����(1) ���޸�
void LCDSetChar(unsigned char x, unsigned char y, unsigned char pos, unsigned char *str);//��ʾ�û��Զ����ַ�����(2)
unsigned char IntegerToStr(long dat, unsigned char *str);

// CGRAM ��ַ���ã�character generator RAM (0~3FH)
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//   0   1  A5  A4  A3  A2  A1  A0

// DDRAM ��ַ����
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//   1  A6  A5  A4  A3  A2  A1  A0
// N = 0��������ʾ A6 ~ A0 = 00H ~ 4FH
// N = 1������     A6 ~ A0 = 00H ~ 27H
//        ����     A6 ~ A0 = 40H ~ 67H

// ��BF��ACֵ��BF:Busy Flag��
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//  0   1  BF  A6  A5  A4  A3  A2  A1  A0

// д����
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//  1   0  A7  A6  A5  A4  A3  A2  A1  A0

// д����
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//  0   0  A7  A6  A5  A4  A3  A2  A1  A0
#endif
