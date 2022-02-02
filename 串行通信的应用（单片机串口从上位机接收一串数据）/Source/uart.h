#ifndef __UART_H_
#define __UART_H_

#include <reg51.h>
#include <stdio.h>

#define MAX_REV_NUM 15
#define REV_CNT     10

extern unsigned char recv_buf[];
extern unsigned char recv_flag;
extern unsigned char recv_length;
void UartInit(void);
void sendByte(unsigned char dat);
void sendString(unsigned char *dat);
char putchar(char c);

#endif
