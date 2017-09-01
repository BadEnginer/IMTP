#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/delay.h"
#include "as5048/as5048.h"
#include "timers/timer_vi.h"
#include "viS/Vi_S.h"
#include "LCD/lcd_lib_2.h"
uint16_t time = 0;
TaskQueue qTasks;
Task	tIplus;
Task	tUplus;
Task	tYplus;

ISR(TIMER0_COMP_vect){
	time++;
	 //ServerTime(&qTasks);
}

int main(){
	initI2C();
	LCD_Init();
	LCD_Goto(0,0);
	uint16_t i = getPosition();
	char c[10] = {0};
	
	initTime0(DIV_64,CTC,249,EN_OCF);
	InitVI_OS(&qTasks); // Инициализирует весь деспетчер
	RunTask(&qTasks, &tIplus, DISPOSABLE, 0);
	sei();
	while (1){
		_delay_ms(100);
		i = getPosition();
		LCD_Goto(0,0);
		c[0] = (i/1000) + '0';
			i %=1000;
		c[1] = (i/100) + '0';
			i %=100;
		c[2] = (i/10)+'0';
			i %=10;
		c[3] = i+'0';
		LCD_WriteData(c[0]);
		LCD_WriteData(c[1]);
		LCD_WriteData(c[2]);
		LCD_WriteData('.');
		LCD_WriteData(c[3]);
		//TaskManager(&qTasks);
	}
}