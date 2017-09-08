#include "../main.h"

void work_angle(){
	int32_t temp=0;
	system.angleBob = getPositionAver(4);
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