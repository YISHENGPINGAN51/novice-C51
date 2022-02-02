#ifndef __UART_H_
#define __UART_H_

#include <reg51.h>
#include <stdio.h>

extern unsigned char recv_data;
extern unsigned char recv_flag;

void UartInit(void);
void sendByte(unsigned char dat);
void sendString(unsigned char *dat);
char putchar(char c);

#endif
