#include "Key.h"

unsigned char Key_Scan()
{
	unsigned char temp, temp2;
	static unsigned char KeyNum = 22;
	KEYPORT = 0xf0;//4���������4��������  ���д��0��  ����д��1��
	temp = KEYPORT;//����P0��
	if (temp != 0xf0)//�ж��Ƿ��м�����
	{
		DelayXms(10);
		if (temp != 0xf0)//�ٴ��ж��Ƿ��м����£�����棬���������İ�������
		{
			temp = KEYPORT & 0xf0;//ȡ����λ��ȷ���к�
			KEYPORT = 0x0f;//4�������룬4�������
			temp2 = KEYPORT & 0x0f;//����  ��ȡ����λ��ȷ���к�
		}
	}
	switch (temp + temp2)
	{
		case 0xee: KeyNum = 1; break;
		case 0xed: KeyNum = 2; break;
		case 0xeb: KeyNum = 3; break;
		case 0xe7: KeyNum = 4; break;
		case 0xde: KeyNum = 5; break;
		case 0xdd: KeyNum = 6; break;
		case 0xdb: KeyNum = 7; break;
		case 0xd7: KeyNum = 8; break;
		case 0xbe: KeyNum = 9; break;
		case 0xbd: KeyNum = 0; break;
		case 0xbb: KeyNum = 10; break;
		case 0xb7: KeyNum = 11; break;
		case 0x7e: KeyNum = 12; break;
		case 0x7d: KeyNum = 13; break;
		case 0x7b: KeyNum = 14; break;
		case 0x77: KeyNum = 15; break;
	}
	return KeyNum;
}