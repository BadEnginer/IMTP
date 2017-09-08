#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "as5048/as5048.h"
#include "timers/timer_vi.h"
#include "viS/Vi_S.h"
#include "LCD/lcd_lib_2.h"
#include "L6470/L6470.h"
#define STEP_TO_MM 0.000313
#define STEP_MM 3
#define STEP_SERVA (STEP_MM/STEP_TO_MM)
#define MAX_SPEED 1000
#define turnToCM 63
#define turnToDM turnToCM*10
#define turnToM turnToCM*100
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
	int16_t		step;
	int16_t		turn;
	int8_t		statusButtonL;
	int8_t		statusButtonR;
	int8_t		statusButtonAll;
	int32_t		test;
}SystemStatus;
extern SystemStatus system;
void work_LCD();
void work_Button();
void work_hall();
void work_choiceDirect();
void work_angle();
void work_serva_R();
void work_serva_L();

void initButton();
void initOS();

TaskQueue qTasks;
Task task_LCD;
Task task_Button;
Task task_halls;
Task task_choiceDirect;
Task task_angle;
Task task_serva_R;
Task task_serva_L;




#endif /* MAIN_H_ */