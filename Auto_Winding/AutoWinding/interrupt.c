#include "main.h"

ISR(TIMER0_COMP_vect){
	system.timeSys++;
	ServerTime(&qTasks);
}