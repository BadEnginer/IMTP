#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/delay.h"
#include "as5048/as5048.h"
#include "timers/timer_vi.h"
#include "viS/Vi_S.h"
#include "LCD/lcd_lib_2.h"
#include "L6470/L6470.h"
#define MAX_SPEED 1000
// PD-6 PD-7 halls PB1- PB-2 buttons

ServoDirect  DD_R = FWD;
ServoDirect  DD_L = REV;
int8_t status_r = 0;
int8_t status_l = 1;
uint16_t time = 0;
int32_t angle = 0;
int32_t lin_cab = 0;
int32_t angle_old = 0;
int32_t angle_speed = 0;
int32_t servStep = 0;
StatusServo servoStat;
void work_LCD();
void work_Butt();
void work_hall();
void work_serva();
void work_angle();
void work_serva_R();
void work_serva_L();

TaskQueue qTasks;
Task task_LCD;
Task task_Buton;
Task task_halls;
Task task_serva;
Task task_angle;
Task task_serva_R;
Task task_serva_L;

ISR(TIMER0_COMP_vect){
	 time++;
	 ServerTime(&qTasks);
}
//task_LCD(),task_Button(),task_hall(),task_serva(),task_angle()
int main(){							 

	initI2C();
	SPI_Init();
	initTime0(DIV_64,CTC,249,EN_OCF);
	InitVI_OS(&qTasks); // Инициализирует весь деспетчер
	InitTask(&task_LCD, work_LCD,  100); 
	InitTask(&task_halls, work_hall,  50); 
	InitTask(&task_serva, work_serva,  0); 
	InitTask(&task_angle, work_angle, 20); 
	InitTask(&task_serva_R, work_serva_R,  0); 
	InitTask(&task_serva_L, work_serva_L,  0); 
	RunTask(&qTasks, &task_LCD, CONTINUOUS, 0);
	RunTask(&qTasks, &task_halls, CONTINUOUS, 0);
	RunTask(&qTasks, &task_angle, CONTINUOUS, 0);
	LCD_Init();
	LCD_Goto(0,0);
	ReadStatusL6470(&servoStat);
	SetParam(ADR_ABS_POS, 0);
	sei();
	while (1){
		TaskManager(&qTasks);
	}
}




void work_LCD(){
	LCD_Clear();
	servStep = lin_cab/100;
	LCD_Goto(0,0);
	LCD_WriteData('a');
	LCD_WriteData('n');
	LCD_WriteData('g');
	LCD_WriteData(':');
	LCDAngle(4,0,angle);
	LCD_Goto(0,1);
	LCD_WriteData('s');
	LCD_WriteData('r');
	LCD_WriteData(':');
	LCDDigit(3,1,servStep);
}
void work_Button(){
	//BitIsClear(reg, bit)
}
void work_hall(){
	static int8_t status = 1;
	uint8_t var = PIND;
	if((!((1 << PD6) & var))&&(status==1)){
		status = 0;
		SoftStop();
		DD_R= (!DD_R);
		DD_L= (!DD_L);
	}
	if((!((1 << PD7) & var))&&(status == 0)){
		status = 1;
		SoftStop();
		DD_R= (!DD_R);
		DD_L= (!DD_L);
	}

}
void work_serva(){
	//Move(DD, 10000);
	//servStep = time/1000; //GetParam(ADR_STATUS);
}

void work_serva_R(){
	Move(DD_R, 10000);
	//servStep =  timestatus_l/1000;//GetParam(ADR_STATUS);
}
void work_serva_L(){
	Move(DD_L, 10000);
	//servStep =  time/1000;//GetParam(ADR_STATUS);
}
void work_angle(){
	int32_t temp=0;
	angle = getPosition();
	temp = angle - angle_old;
	if((temp < MAX_SPEED)&&(temp>(-1*MAX_SPEED))){
	angle_speed = temp;
	lin_cab +=angle_speed;
	}
	angle_old = angle;
	if((temp > 1000)){
		RunTask(&qTasks, &task_serva_R, DISPOSABLE, 0);
		status_r = 1;
	}
	
	if((temp<-1000)){
		RunTask(&qTasks, &task_serva_L, DISPOSABLE, 0);
		status_l = 1;
	}
}




