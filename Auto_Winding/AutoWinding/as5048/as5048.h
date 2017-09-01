#ifndef AS5058_H
#define AS5058_H

#include "../i2c_vi/i2c_vi.h"

#define AS5048_ADR		0b10000000						// address write
#define AS5048_MAG_HI	0xFC							// address
#define AS5048_GAIN		0xFA
#define AS5048_MAG_LO	0xFD							// address
#define AS5048_ANGLE_HI	0xFE							// address
#define AS5048_ANGLE_LO	0xFF							// address
#define ZERO_POS_HI 	0x16							// address
#define ZERO_POS_LO		0x17							// address

uint16_t	getPosition();
void  	setZero();
void	setZeroPos(uint8_t ,uint8_t);			
float	AS5058ReadAng();

#endif // AS5058_H