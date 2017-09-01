#ifndef CONFIG_AS5058_H

#define CONFIG_AS5058_H

#define F_CPU 16000000UL									// Clock
#define F_I2C 100000UL  					    		// Speed I2C
#define TWBR_VALUE (((F_CPU)/(F_I2C)-16)/2)				// calculation i2c 
#define T_SEC(D)	(1.0/(F_CPU/D))						// Time in sec
#if ((TWBR_VALUE > 255) || (TWBR_VALUE == 0))			// limitation i2c speed
#error "TWBR value is not correct"
#endif
#define AS5048_R		0b10000001						// address read
#define AS5048_W		0b10000000						// address write
#define AS5048_MAG_HI	0xFC							// address
#define AS5048_GAIN		0xFA
#define AS5048_MAG_LO	0xFD							// address
#define AS5048_ANGLE_HI	0xFE							// address
#define AS5048_ANGLE_LO	0xFF							// address
#define ZERO_POS_HI 	0x16							// address
#define ZERO_POS_LO		0x17							// address

typedef  unsigned char uc;
typedef  unsigned short int unsi;

// #if 0
// typedef  union bFloat
// {	
// 	unsigned char		  C_Angel[8];
// 	float			      F_Angel[2];
// };
//#endif

#endif