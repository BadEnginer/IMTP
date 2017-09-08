#include "../main.h"
void initButton(){
	DDRB |=(1<<PB1)|(1<<PB2)|(1<<PB3);
	PORTB|=(1<<PB1)|(1<<PB2)|(1<<PB3);
}

void work_Button(){
	uint8_t Button1 = !((1 << PB1) & PINB);
	uint8_t Button2 = !((1 << PB2) & PINB);
	static uint8_t status = 0;
	if((Button1 == 1 || Button2 == 1)&&status==0)
	status = 1;
	if((Button1 == 1 || Button2 == 1)&&status==1){
		status = 2;
		system.DD = !system.DD;
		system.statusButtonAll = !system.statusButtonAll;
	}
	if(!(Button1 == 1 || Button2 == 1)&&status==2)
	status = 0;
}