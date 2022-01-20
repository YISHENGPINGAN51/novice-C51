#include <reg51.h>
#include <intrins.h>

void timer0_Init();
unsigned char timerCnt;
unsigned char temp = 0xfe;

void main()
{
	timer0_Init();
	while (1)
	{
		if (1 == TF0)
		{
			TF0 = 0;
			TH0 = (65536 - 20000) / 256;//重新赋初值  便于产生下一次的20ms定时
			TL0 = (65536 - 20000) % 256;
			//1S = 1000ms / 20ms = 50次
			timerCnt++;
			if (timerCnt >= 50)
			{
				timerCnt = 0;
				P1 = temp;
				temp = _crol_(temp, 1);
			}
		}
	}
}

void timer0_Init()
{
	//1、设置TMOD 确定工作方式 定时/计数   哪一种工作方式 工作方式1   GATE 0
	TMOD = 0X01;//GATE  C/T  M1  M0  GATE  C/T  M1  M0
	//2、定时初值的计算  (eg: 20ms  12M)
	TH0 = (65536 - 20000) / 256;
	TL0 = (65536 - 20000) % 256;
	//3、打开定时/计数器
	TR0 = 1;//启动定时计数器
}