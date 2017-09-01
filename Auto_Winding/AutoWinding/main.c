#define F_CPU 16000000L
#include <avr/io.h>
#include "as5048/as5048.h"


int main(){
	initI2C();
	volatile uint16_t data = 0;
	while (1){
		data = getPosition();
		
	}
}