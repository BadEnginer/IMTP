#include "as5048.h"


void  setZeroPos(uint8_t Lo,uint8_t Hi){
	i2cWrite(AS5048_ADR,ZERO_POS_LO,0);	
	i2cWrite(AS5048_ADR,ZERO_POS_HI,0);
	i2cWrite(AS5048_ADR,ZERO_POS_LO,Lo);
	i2cWrite(AS5048_ADR,ZERO_POS_HI,Hi);
}

void setZero(){
	uint8_t Hi = i2cRead(AS5048_ADR,AS5048_ANGLE_HI);
	uint8_t Lo = i2cRead(AS5048_ADR,AS5048_ANGLE_LO);
	i2cWrite(AS5048_ADR,ZERO_POS_LO,0);	
	i2cWrite(AS5048_ADR,ZERO_POS_HI,0);
	i2cWrite(AS5048_ADR,ZERO_POS_LO,Lo);
	i2cWrite(AS5048_ADR,ZERO_POS_HI,Hi);
}

void Bubble(float *angels,uint8_t num){ 
	uint8_t n=num,i=0, j=0;
	for(i = 0 ; i < n - 1; i++)
	{
		for(j = 0 ; j < n - i - 1 ; j++)
		{
			if(angels[j] > angels[j+1])
			{
				float tmp = angels[j]; angels[j] = angels[j+1] ; angels[j+1] = tmp;
			}
		}
	}
	
}

float AS5058ReadAng(){
	volatile 	uint8_t	buffI2C[100];					
	volatile 	float	ANG = 0;						
	volatile 	float	iANG = 0;				
	for (uint8_t i = 0; i<100;i++)
		{
			for (uint32_t i = 0; i < 100000; i++);
			buffI2C[i] = i2cRead(AS5048_ADR,AS5048_ANGLE_HI);
		}
	ANG=(buffI2C[1] << 6)+(buffI2C[0]);			
	iANG=ANG * 0.0219;
	setZero(buffI2C[0],buffI2C[1])	;						
	if(iANG>359)
		iANG=0;
	return ANG;
}

uint16_t getPosition()
{
	return (0.219*((i2cRead(AS5048_ADR,AS5048_ANGLE_HI) << 6) + (i2cRead(AS5048_ADR,AS5048_ANGLE_LO))));
}
