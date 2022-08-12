#include "Relay.h"

//继电器上电初始化
void Relay_Init(void)
{
	RELAY0 = 1;
	RELAY1 = 0;
	RELAY2 = 0;
	RELAY3 = 0;
	RELAY4 = 0;
}

void Relay0_ON(void)
{
	RELAY0 = 0;
}

void Relay0_OFF(void)
{
	RELAY0 = 1;
}

void Relay1_ON(void)
{
	RELAY1 = 1;
}

void Relay1_OFF(void)
{
	RELAY1 = 0;
}

void Relay2_ON(void)
{
	RELAY2 = 1;
}

void Relay2_OFF(void)
{
	RELAY2 = 0;
}
void Relay3_ON(void)
{
	RELAY3 = 1;
}

void Relay3_OFF(void)
{
	RELAY3 = 0;
}
void Relay4_ON(void)
{
	RELAY4 = 1;
}

void Relay4_OFF(void)
{
	RELAY4 = 0;
}