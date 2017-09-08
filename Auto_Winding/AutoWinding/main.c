#include "main.h"

int main(){	
	memset(&system, 0, sizeof(system));
	initI2C();
	initSPI();
	initTime0(DIV_64,CTC,249,EN_OCF);
	initLCD();
	initOS();
	initButton();
	initL6470();
	sei();
	while (1){
		TaskManager(&qTasks);
	}
}

void menu(){
	
}





