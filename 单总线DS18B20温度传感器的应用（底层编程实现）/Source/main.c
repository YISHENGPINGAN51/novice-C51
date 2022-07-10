#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "OneWire.h"

void main()
{
	unsigned char ack;
	LCDInit();
	DelayXms(10);
	ack = OneWireRst();
	while (1)
	{
		LCDSetPosition(0, 0);
		LCDWriteData(ack + '0');
	}
}
