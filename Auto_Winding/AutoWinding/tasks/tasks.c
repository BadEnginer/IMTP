#include "../main.h"

void initOS(){
	InitVI_OS(&qTasks); // Инициализирует весь деспетчер
	InitTask(&task_LCD, work_LCD,  100);
	InitTask(&task_halls, work_hall,  25);
	InitTask(&task_choiceDirect, work_choiceDirect,  0);
	InitTask(&task_angle, work_angle, 25);
	InitTask(&task_serva_R, work_serva_R,  0);
	InitTask(&task_serva_L, work_serva_L,  0);
	InitTask(&task_Button, work_Button, 50);
	RunTask(&qTasks,&task_Button,CONTINUOUS,0);
	RunTask(&qTasks,&task_choiceDirect,CONTINUOUS,0);
	RunTask(&qTasks, &task_LCD, CONTINUOUS, 0);
	RunTask(&qTasks, &task_halls, CONTINUOUS, 0);
	RunTask(&qTasks, &task_angle, CONTINUOUS, 0);
}