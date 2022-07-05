#include "menu.h"

extern unsigned char sec, min, hour;

void Startmenu()
{
	LCDShowStr(4, 0, "LCD CLOCK");
	LCDShowStr(2, 1, "Beijing Time");
}

void LCDShowSec()
{
	LCDSetPosition(10, 1);
	LCDWriteData(sec/10 + '0');
	LCDWriteData(sec%10 + '0');
}

void LCDShowMin()
{
	LCDSetPosition(7, 1);
	LCDWriteData(min/10 + '0');
	LCDWriteData(min%10 + '0');
	LCDWriteData(':');
}

void LCDShowHour()
{
	LCDSetPosition(4, 1);
	LCDWriteData(hour/10 + '0');
	LCDWriteData(hour%10 + '0');
	LCDWriteData(':');
}
