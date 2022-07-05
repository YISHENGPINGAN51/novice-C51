#ifndef __MENU_H_
#define __MENU_H_

#include "LCD1602.h"

void Startmenu();
void SubMenuOne();
void SubMenuTwo();
void SubMenuThree();
void SubMenuFour();
void AlarmSetMenu();
void ShowTempData(unsigned char x, unsigned char y, int *buf, unsigned char num);

#endif
