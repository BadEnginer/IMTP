#include "../main.h"

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