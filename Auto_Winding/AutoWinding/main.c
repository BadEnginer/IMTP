#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "util/delay.h"
#include "as5048/as5048.h"
#include "timers/timer_vi.h"
#include "viS/Vi_S.h"
#include "LCD/lcd_lib_2.h"
#include "L6470/L6470.h"
#define MAX_SPEED 1000
// PD-6 PD-7 halls PB1- PB-2 buttons
typedef struct {
	StatusServo servoStatus;
	ServoDirect	DD;
	int8_t		statusHall;
	int8_t		statusHallR;
	int8_t		statusHallL;
	uint32_t	timeSys;
	int16_t		angleBob;
	int32_t		lengthCab;
	int32_t		angleOld;
	int32_t		angleSpeed;
	int32_t		servStep;
	int16_t	step;
	int16_t	turn;
}SystemStatus;
volatile SystemStatus system;
void work_LCD();
void work_Butt();
void work_hall();
void work_choiceDirect();
void work_angle();
void work_serva_R();
void work_serva_L();

TaskQueue qTasks;
Task task_LCD;
Task task_Buton;
Task task_halls;
Task task_choiceDirect;
Task task_angle;
Task task_serva_R;
Task task_serva_L;

ISR(TIMER0_COMP_vect){
	 system.timeSys++;
	 ServerTime(&qTasks);
}
//task_LCD(),task_Button(),task_hall(),task_serva(),task_angle()
int main(){		
	memset(&system, 0, sizeof(system));
	initI2C();
	SPI_Init();
	initTime0(DIV_64,CTC,249,EN_OCF);
	InitVI_OS(&qTasks); // Инициализирует весь деспетчер
	InitTask(&task_LCD, work_LCD,  100); 
	InitTask(&task_halls, work_hall,  25); 
	InitTask(&task_choiceDirect, work_choiceDirect,  0); 
	InitTask(&task_angle, work_angle, 20); 
	InitTask(&task_serva_R, work_serva_R,  0); 
	InitTask(&task_serva_L, work_serva_L,  0); 
	RunTask(&qTasks,&task_choiceDirect,CONTINUOUS,25);
	RunTask(&qTasks, &task_LCD, CONTINUOUS, 0);
	RunTask(&qTasks, &task_halls, CONTINUOUS, 0);
	RunTask(&qTasks, &task_angle, CONTINUOUS, 0);
	LCD_Init();
	LCD_Goto(0,0);
	ReadStatusL6470(&system.servoStatus);
	SetParam(ADR_ABS_POS, 0);
	sei();
	while (1){
		TaskManager(&qTasks);
	}
}




void work_LCD(){
	LCD_Clear();
	system.servStep = (system.lengthCab)/100;
	LCD_Goto(0,0);
	LCD_WriteData('a');
	LCD_WriteData('g');
	LCD_WriteData(':');
	//LCDAngle(3,0,system.angleBob);
	LCDDigit(3,0,system.step);
	LCD_Goto(0,1);
	LCD_WriteData('l');
	LCD_WriteData('g');
	LCD_WriteData(':');
	LCDDigit(3,1,system.turn);
}
void work_Button(){
	//BitIsClear(reg, bit)
}
void work_hall(){
	uint8_t hallR = !((1 << PD6) & PIND);
	uint8_t hallL = !((1 << PD7) & PIND);
	switch((system.statusHall)){
		case 0: 
			if(hallL==1)
				system.statusHall = 1;
			else if(hallR==1)
				system.statusHall = 1;
			else { system.statusHallL = 0;system.statusHallR = 0;}
			break;
		case 1:
			if(hallL==1)
				system.statusHallL = 1;
			if(hallR==1)
				system.statusHallR = 1;
			system.statusHall = 0;
			break;
	}
}
void work_choiceDirect(){
	static int8_t status = 0;
	if(((system.statusHallL == 1) || (system.statusHallR == 1)) && status == 0){
		SoftStop();
		status = 1;
	}
	if(status==1){
		system.DD = !(system.DD);
		status = 2;
	}
	if(system.statusHallL == 0 && system.statusHallR == 0 && status == 2)
		status = 0;

}

void work_serva_R(){
	system.step++;
	Move(system.DD, 30000);
}
void work_serva_L(){
	system.step--;
	Move(!(system.DD), 30000);
}
void work_angle(){
	int32_t temp=0;
	system.angleBob = getPosition();
	temp = system.angleBob - system.angleOld;
	if((temp < MAX_SPEED)&&(temp>(-1*MAX_SPEED))){
		system.angleSpeed = temp;
		system.lengthCab +=system.angleSpeed;
	}
	system.angleOld = system.angleBob;
	if((temp > 1000)){
		system.turn++;
		RunTask(&qTasks, &task_serva_R, DISPOSABLE, 0);
	}
	
	if((temp<-1000)){
		system.turn--;
		RunTask(&qTasks, &task_serva_L, DISPOSABLE, 0);
	}
}




