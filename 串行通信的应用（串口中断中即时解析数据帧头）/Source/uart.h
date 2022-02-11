#ifndef __UART_H_
#define __UART_H_

#include <reg51.h>
#include <stdio.h>

#define MAX_REV_NUM  20

extern unsigned char recv_buf[MAX_REV_NUM];
extern unsigned char recv_cnt;
extern unsigned char recv_flag;
extern unsigned int led_data;
extern unsigned int led_cnt;
extern unsigned int beep_cnt;

void UartInit(void);
void sendByte(unsigned char dat);
void sendString(unsigned char *dat);
char putchar(char c);
void clr_recvbuffer(unsigned char *buf);

#endif
