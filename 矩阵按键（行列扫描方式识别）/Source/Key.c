#include "Key.h"

unsigned char Key_Scan()
{
	static unsigned char KeyNum = 22;
	//第一列输出低电平，检测第一列的四行
	KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
	KEYOUT1 = 0; KEYOUT2 = 1; KEYOUT3 = 1; KEYOUT4 = 1;
	
	if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
	{
		DelayXms(10);
		if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
		{
			if (!KEYIN1)
				KeyNum = 1;
			if (!KEYIN2)
				KeyNum = 2;
			if (!KEYIN3)
				KeyNum = 3;
			if (!KEYIN4)
				KeyNum = 4;
		}  while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
	}
	
	//第二列输出低电平，检测第二列的四行
	KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
	KEYOUT1 = 1; KEYOUT2 = 0; KEYOUT3 = 1; KEYOUT4 = 1;
	
	if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
	{
		DelayXms(10);
		if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
		{
			if (!KEYIN1)
				KeyNum = 5;
			if (!KEYIN2)
				KeyNum = 6;
			if (!KEYIN3)
				KeyNum = 7;
			if (!KEYIN4)
				KeyNum = 8;
		}  while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
	}
	
	//第三列输出低电平，检测第三列的四行
	KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
	KEYOUT1 = 1; KEYOUT2 = 1; KEYOUT3 = 0; KEYOUT4 = 1;
	
	if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
	{
		DelayXms(10);
		if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
		{
			if (!KEYIN1)
				KeyNum = 9;
			if (!KEYIN2)
				KeyNum = 0;
			if (!KEYIN3)
				KeyNum = 10;
			if (!KEYIN4)
				KeyNum = 11;
		}  while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
	}
	
	//第四列输出低电平，检测第四列的四行
	KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
	KEYOUT1 = 1; KEYOUT2 = 1; KEYOUT3 = 1; KEYOUT4 = 0;
	
	if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
	{
		DelayXms(10);
		if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
		{
			if (!KEYIN1)
				KeyNum = 12;
			if (!KEYIN2)
				KeyNum = 13;
			if (!KEYIN3)
				KeyNum = 14;
			if (!KEYIN4)
				KeyNum = 15;
		}  while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
	}
	
	return KeyNum;
}

//unsigned char Key_Scan()
//{
//	static unsigned char KeyNum = 22;
//	//第一列输出低电平，检测第一列的四行
//	KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
//	KEYOUT1 = 0; KEYOUT2 = 1; KEYOUT3 = 1; KEYOUT4 = 1;
//	
//	if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
//	{
//		DelayXms(10);
//		if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
//		{
//			if (!KEYIN1)
//				KeyNum = 1;
//			if (!KEYIN2)
//				KeyNum = 2;
//			if (!KEYIN3)
//				KeyNum = 3;
//			if (!KEYIN4)
//				KeyNum = 4;
//		}  while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
//	}
//	
//	//第二列输出低电平，检测第二列的四行
//	KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
//	KEYOUT1 = 1; KEYOUT2 = 0; KEYOUT3 = 1; KEYOUT4 = 1;
//	
//	if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
//	{
//		DelayXms(10);
//		if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
//		{
//			if (!KEYIN1)
//				KeyNum = 5;
//			if (!KEYIN2)
//				KeyNum = 6;
//			if (!KEYIN3)
//				KeyNum = 7;
//			if (!KEYIN4)
//				KeyNum = 8;
//		}  while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
//	}
//	
//	//第三列输出低电平，检测第三列的四行
//	KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
//	KEYOUT1 = 1; KEYOUT2 = 1; KEYOUT3 = 0; KEYOUT4 = 1;
//	
//	if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
//	{
//		DelayXms(10);
//		if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
//		{
//			if (!KEYIN1)
//				KeyNum = 9;
//			if (!KEYIN2)
//				KeyNum = 10;
//			if (!KEYIN3)
//				KeyNum = 11;
//			if (!KEYIN4)
//				KeyNum = 12;
//		}  while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
//	}
//	
//	//第四列输出低电平，检测第四列的四行
//	KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
//	KEYOUT1 = 1; KEYOUT2 = 1; KEYOUT3 = 1; KEYOUT4 = 0;
//	
//	if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
//	{
//		DelayXms(10);
//		if (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
//		{
//			if (!KEYIN1)
//				KeyNum = 13;
//			if (!KEYIN2)
//				KeyNum = 14;
//			if (!KEYIN3)
//				KeyNum = 15;
//			if (!KEYIN4)
//				KeyNum = 16;
//		}  while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
//	}
//	
//	return KeyNum;
//}