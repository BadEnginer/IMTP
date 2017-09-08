#include "../main.h"

void work_LCD(){
	LCD_Clear();
	system.servStep = (system.lengthCab)/turnToM;
	LCD_Goto(0,0);
	LCD_WriteData('a');
	LCD_WriteData('g');
	LCD_WriteData(':');
	//LCDAngle(3,0,system.angleBob);
	LCDDigit(3,0,system.angleBob);
	LCD_Goto(0,1);
	LCD_WriteData('l');
	LCD_WriteData('g');
	LCD_WriteData(':');
	LCDDigit(3,1,system.servStep);
	LCD_Goto(7,1);
	if(system.statusButtonAll)
	LCD_WriteData('+');
	else
	LCD_WriteData('-');
}