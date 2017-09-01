#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include "as5048/as5048.h"
#include "timers/timer_vi.h"
#include "viS/Vi_S.h"
uint16_t time = 0;
TaskQueue qTasks;
Task	tIplus;
Task	tUplus;
Task	tYplus;

ISR(TIMER0_COMP_vect){
	time++;
	 ServerTime(&qTasks);
}

void Iplus(){
	static uint16_t Ip=0;
	Ip++;
	RunTask(&qTasks, &tUplus, CONTINUOUS, 5);
	RunTask(&qTasks, &tYplus, CONTINUOUS, 100);
}
void Uplus(){
	static uint8_t i = 0;
	static uint16_t Up[10]={0};
	Up[i] = time;
	i++;
	if(i>9)
		i = 0;
}
void Yplus(){
	static uint16_t Yp=0;
	Yp = (i2cRead(AS5048_ADR,AS5048_ANGLE_HI) << 6);
}

int main(){
	initI2C();
	initTime0(DIV_64,CTC,249,EN_OCF);
	InitVI_OS(&qTasks); // Инициализирует весь деспетчер
	InitTask(&tIplus, Iplus, 10);
	InitTask(&tUplus, Uplus, 5);
	InitTask(&tYplus, Yplus, 10); 
	RunTask(&qTasks, &tIplus, DISPOSABLE, 10);

	
	sei();
	while (1){
		
		TaskManager(&qTasks);
	}
}