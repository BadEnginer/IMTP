#include "L6470.h"
#include "as5048.h"
#include "bits_macros.h"

int main(void)
{
	StatusServo status;
	SPI_Init();
	initAS5048B();
	HardHiZ();
	//SetParam(ADR_STEP_MODE, 4);
	int32_t angel = 0;
	int32_t angel_old = 0;
	int32_t angel_angel = 0;
	
	ReadStatusL6470(&status);
	while(1)
	{
		
		while(!(BitIsSet(PIND,4)));
		Move(FWD, 10000);
		ReadStatusL6470(&status);
		while(!(BitIsSet(PIND,4)));
		Move(REV, 10000);
		ReadStatusL6470(&status);
		
// 	//		angel +=	0.02*(i2c_read(AS5048_ANGLE_HI) << 6) + (i2c_read(AS5048_ANGLE_LO) & 0xF);
// 		angel_angel = (angel/10) - angel_old;
// 		angel_old = (angel/10);
// 		if(angel_angel < 0)
// 		{
// 			angel_angel = angel_angel *(-1);
// 			Move(FWD, angel_angel*25);
// 		}
// 		else
// 			Move(REV, angel_angel*25);
// 		angel = 0;
// 	//GoMark();
// 	//ReadStatusL6470(&status);
// 	//SoftStop();
// 	ReadStatusL6470(&status);
	}
}

