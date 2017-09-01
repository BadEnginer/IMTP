#ifndef CONFIG_AS5058_H

#define CONFIG_AS5058_H

#define F_CPU 8000000UL									// Clock

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


#endif