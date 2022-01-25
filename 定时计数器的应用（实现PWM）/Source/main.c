#include <reg51.h>

sbit PWM = P1^0;

unsigned char  PWM_Duty = 0;
unsigned char PWM_Cnt;

void Timer0Init(void);
void EX0_Init();

void main()
{
	Timer0Init();
	EX0_Init();
	EA = 1;
	while (1)
	{
		
	}
}

void Timer0Init(void)		//100΢��@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x9C;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;
	EA = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void EX0_Init()
{
	IT0 = 1;//�½��ش���
	EX0 = 1;
}
/*****************************************************************
1���жϷ�����һ����һ��û�з���ֵ�ĺ���
2���жϷ�����һ����û�в����ĺ���
3���жϷ���������������ؼ��� interrupt
4��interrupt n 0 - 4  5���ж�Դ  8*n + 0003H
0003H INT0    000BH T0    0013H INT1    001BH T1    0023H ES
5���жϷ��������ܱ����������������������
6��n�����using m (0 - 3)�����Ĵ�����
*****************************************************************/
void timer0_ISR(void) interrupt 1
{
	TR0 = 0;
	PWM_Cnt++;
	if (PWM_Cnt >= 100)
	{
		PWM_Cnt = 0;
	}
	if (PWM_Cnt <= PWM_Duty)
	{
		PWM = 1;
	}
	else
		PWM = 0;
	TL0 = 0x9C;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TR0 = 1;
}

void EX0_ISR(void) interrupt 0
{
	static unsigned char PWM_KEY;
	PWM_KEY++;
	switch (PWM_KEY)
	{
		case 1:	PWM_Duty = 25; break;
		case 2:	PWM_Duty = 50; break;
		case 3:	PWM_Duty = 75; break;
		case 4:	PWM_Duty = 80; break;
		case 5:	PWM_Duty = 100; break;
		case 6:	PWM_Duty = 0; PWM_KEY = 0; break;
		default: break;
	}
}