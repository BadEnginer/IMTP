#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "as5048/as5048.h"


int main(){
	uint16_t data = 0;
	while (0){
		data = getPosition();
		
	}
}