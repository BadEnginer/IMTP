//--------------------includ+def------------------------
#ifndef AS5058_H

#define AS5058_H
#include <avr/io.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "cnfg_as5048.h"

#define F_I2C 100000UL  					    		// Speed I2C
#define TWBR_VALUE (((F_CPU)/(F_I2C)-16)/2)				// calculation i2c
#define T_SEC(D)	(1.0/(F_CPU/D))						// Time in sec
#if ((TWBR_VALUE > 255) || (TWBR_VALUE == 0))			// limitation i2c speed
#error "TWBR value is not correct"
#endif

//void			TX_Can(pCanMessage);
long unsigned int	current_time();		
void				initTime0();
void				i2c_write(uc,uc);
unsigned char		i2c_read(uc);
void				i2c_set_zero(unsigned char,unsigned char);
//void				Bubble(float *,unsigned char);				// *angels-array angel, num- number mass, ret what return				
void				initAS5048B();
float				AS5058_read_ang();
//uint16_t			Tact(unsigned char);
#endif