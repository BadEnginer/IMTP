#include "as5048.h"

//enum SCL_T0 {DIS=0,SLC8=8,SLC64=64,SLC256=256,SLC1024=1024};
#define MAX_INT 65535UL
#define DELAY_1MS 1000

// void InitCan(st_cmd_t *msg1,uint8_t addres,uint8_t cmd) {
// 	
// 	msg1->status = 0;
// 	msg1->handle = 0;
// 	msg1->id.std = addres;
// 	msg1->dlc = 8;
// 	msg1->cmd = cmd;
// 	if(!can_init(0))
// 	{
// 		while(1) {};
// 	}
// 	while(can_cmd(msg1) != CAN_CMD_ACCEPTED);
// }


// uint8_t TX_Can(st_cmd_t *message, uint8_t* array){
// 	
// 	message->pt_data = array;
// 	//while(can_cmd(message) != CAN_CMD_ACCEPTED);
// 	
// 	uint8_t can_status=can_get_status(message);
// 	if(can_status!=CAN_STATUS_NOT_COMPLETED) {
// 		can_cmd(message);
// 	}
// 	return can_status;
// 	
// }
// 
// 
// void initTime1(enum SCL_T0 T1)
// {
// 	TCNT1 = 0;
// 	TCCR1A = (0<<COM1A1)|(0<<COM1A0)|(0<<WGM11)|(0<<WGM10);
// 	TCCR1B = (0<<WGM13)|(0<<WGM12)|(0<<CS12)|(0<<CS11)|(0<<CS10);
// 	TIFR1 = (1<<TOV1);								//overflow interrupt
// 	TIMSK1 |= (1<<TOIE1);							//enable interrupt
// 	if(T1 == DIS)
// 	TCCR1B |= (0<<CS12)|(0<<CS11)|(0<<CS10);		//set divider 000-disable 001-SLC 010-SLC/8 011-SLC/64 100-SCL/256 101-SCL/1024
// 	if(T1==SLC8)
// 	TCCR1B |= (0<<CS12)|(1<<CS11)|(0<<CS10);
// 	if(T1==SLC64)
// 	TCCR1B |= (0<<CS12)|(1<<CS11)|(1<<CS10);
// 	if(T1==SLC256)
// 	TCCR1B |= (1<<CS12)|(0<<CS11)|(0<<CS10);
// 	if(T1==SLC1024)
// 	TCCR1B |= (1<<CS12)|(0<<CS11)|(1<<CS10);
// 	
// 	TCNT1 = MAX_INT - DELAY_1MS;
// }
// 
// void initTime0()
// {
// 	 TCCR0A = 0;									//set ZERO position
// 	 TCCR0A = (0<<WGM01)|(0<<WGM00);				//set MODE 00-Norm 01-PWM 10-CTC 11-FAST_PWM
// 	 TIFR0 = (1<<TOV0);								//overflow interrupt
// 	 TIMSK0 |= (1<<TOIE0);	
// 	 /*						//enable interrupt
// 	 if(T0==DIS)
// 		 TCCR0A |= (0<<CS02)|(0<<CS01)|(0<<CS00);	//set divider 000-disable 001-SLC 010-SLC/8 011-SLC/64 100-SCL/256 101-SCL/1024	
// 	 if(T0==SLC8)
// 		 TCCR0A |= (0<<CS02)|(0<<CS01)|(1<<CS00);		
// 	 if(T0==SLC64)
// 		 TCCR0A |= (0<<CS02)|(1<<CS01)|(1<<CS00);		
// 	 if(T0==SLC256)
// 		 TCCR0A |= (1<<CS02)|(0<<CS01)|(0<<CS00);		
// 	 if(T0==SLC1024)
// 	 */
// 		 TCCR0A |= (1<<CS02)|(0<<CS01)|(0<<CS00);
// 	// TCNT0 = 0;		
// }

void  i2c_write(uc REG,uc data)
{
	//----------------START----------------------
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);				
	while(!(TWCR & (1<<TWINT)));						
	//------------------------------------------

	//------------Transmit data-----------------
	TWDR = AS5048_W;										
	TWCR = (1<<TWINT)|(1<<TWEN); 						
	while(!(TWCR & (1<<TWINT)));						
	//------------------------------------------

	//-----------Transmit data------------------
	TWDR = REG;										
	TWCR = (1<<TWINT)|(1<<TWEN); 					
	while(!(TWCR & (1<<TWINT)));					
	//------------------------------------------

	//-----------Transmit data------------------
	TWDR = data;										
	TWCR = (1<<TWINT)|(1<<TWEN); 					
	while(!(TWCR & (1<<TWINT)));					
	//------------------------------------------

	//----------------STOP----------------------
	TWCR = (1<<TWINT)|(1<<TWSTO)|(0<<TWEN);			
	//------------------------------------------
}

uc i2c_read(uc REG)
{
	
	volatile 	uc data=0xFF;

	//----------------START----------------------
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);			
	while(!(TWCR & (1<<TWINT)));					
	//-------------------------------------------

	//------------Transmit data------------------
	TWDR =AS5048_W;									
	TWCR = (1<<TWINT)|(1<<TWEN); 					
	while(!(TWCR & (1<<TWINT)));					
	//-------------------------------------------

	//-----------Transmit data-------------------
	TWDR = REG;										
	TWCR = (1<<TWINT)|(1<<TWEN); 					
	while(!(TWCR & (1<<TWINT)));					
	//-------------------------------------------

	//-----------START------------------
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);			
	while(!(TWCR & (1<<TWINT)));

	//----------Transmit data--------------------
	TWDR = AS5048_R;							 	
	TWCR = (1<<TWINT)|(1<<TWEN); 					
	while(!(TWCR & (1<<TWINT)));					
	//-------------------------------------------

	//-----------Reserv data---------------------
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	data = TWDR;
	//-----------------------------------------

	//----------------STOP---------------------
	TWCR = (1<<TWINT)|(1<<TWSTO)|(0<<TWEN);			
	//-----------------------------------------
	
	return data;
}

void  i2c_set_zero(uc Lo,uc Hi)
{
	i2c_write(ZERO_POS_LO,0);	
	i2c_write(ZERO_POS_HI,0);
	i2c_write(ZERO_POS_LO,Lo);
	i2c_write(ZERO_POS_HI,Hi);
}

void Bubble(float *angels,uc num)							
{ 
	// bubble sort ...
	uc n=num,i=0, j=0;
	
	
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

void initAS5048B()
{
	TWBR = TWBR_VALUE;								// speed inst
	TWSR = 0;
}

float AS5058_read_ang()
{
	volatile 	uc		buffI2C[100];					
	volatile 	float	ANG = 0;						
	volatile 	float	iANG = 0;
	//volatile	char	i = 1;					
for (uint8_t i = 0; i<100;i++)
	{
		for (uint32_t i = 0; i < 100000; i++);
		buffI2C[i] = i2c_read(AS5048_ANGLE_HI);
	}
			
	//buffI2C[1] = i2c_read(AS5048_ANGLE_HI);
	ANG=(buffI2C[1] << 6)+(buffI2C[0] & 0x3F);			
	iANG=ANG * 0.022;// Magic number
	i2c_set_zero(buffI2C[0],buffI2C[1])	;						
	if(iANG>359)
	iANG=0;
	return ANG;
}
float get_position(uc arr_size)
{
	float mid_position;
	float angel_mid_filter[arr_size];
	for(uint8_t i = 0; i < arr_size; i++) {
		angel_mid_filter[i]= AS5058_read_ang();
	}
	Bubble(angel_mid_filter, arr_size);
	mid_position = angel_mid_filter[arr_size / 2];
	return mid_position;
}

void shift_array(float* array, uint8_t size)
{
	for(uc i = 0; i < size - 1; i++) {
		array[i] = array[i + 1];
	}
	array[size - 1] = 0;
}

float calc_speed(float* array, float delta)
{
	float speed = 0;
	float delta_pos, delta_time; 
	if(delta != 0) {
		delta_pos = array[0] - 8*array[1] + 8*array[2] - array[3];
		delta_time = (12 * delta) / 1000;
		speed = delta_pos / delta_time;
	}
	return speed;
}