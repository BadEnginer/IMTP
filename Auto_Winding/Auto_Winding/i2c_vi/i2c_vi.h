#ifndef _I2C_VI_H
#define _I2C_VI_H

#include <avr/io.h>

#ifndef F_CPU
	#define F_CPU 16000000L
#endif

#define F_I2C 100000UL  					    		// Speed I2C
#define TWBR_VALUE (((F_CPU)/(F_I2C)-16)/2)				// calculation i2c 
#define T_SEC(D)	(1.0/(F_CPU/D))						// Time in sec
#if ((TWBR_VALUE > 255) || (TWBR_VALUE == 0))			// limitation i2c speed
#error "TWBR value is not correct"
#endif

void initI2C();
void  i2cWrite(uint8_t adr,uint8_t reg,uint8_t data);
uint8_t i2cRead(uint8_t adr,uint8_t reg);


#endif //_I2C_VI_H