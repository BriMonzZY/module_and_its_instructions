#include "status_transmit.h"





void Init_To_Manual(void)
{
	staSystem = MANUAL;
	LCD_Clear(WHITE);
}



void Init_To_Auto1(void)
{
	staSystem = AUTO1;
	LCD_Clear(WHITE);
}

void Init_To_Auto2(void)
{
	staSystem = AUTO2;
	LCD_Clear(WHITE);
}

void Init_To_Follow(void)
{
	staSystem = FOLLOW;
	LCD_Clear(WHITE);
}


void Auto1_To_Init(void)
{
	staSystem = INIT;
	LCD_Clear(WHITE);
}

void Auto2_To_Init(void)
{
	staSystem = INIT;
	LCD_Clear(WHITE);
}

void Follow_To_Init(void)
{
	staSystem = INIT;
	LCD_Clear(WHITE);
}

void Manual_To_Init(void)
{
	staSystem = INIT;
	LCD_Clear(WHITE);
}
