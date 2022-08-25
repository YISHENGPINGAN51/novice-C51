#ifndef __UART2_H_
#define __UART2_H_

#include <reg51.h>
#include <stdio.h>

/*ÉùÃ÷SFR UART2 */
sfr AUXR  = 0x8e;           //Auxiliary register
sfr S2CON = 0x9a;           //UART2 control register
sfr S2BUF = 0x9b;           //UART2 data buffer
sfr BRT   = 0x9c;           //Baudrate generator
sfr IE2   = 0xaf;           //Interrupt control 2

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3

void Uart2Init(void);
void sendByte2(unsigned char dat);
void sendString2(unsigned char *dat);

#endif
