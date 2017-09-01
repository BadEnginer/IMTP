#include "i2c_vi.h"

void initI2C(){
	TWBR = TWBR_VALUE;								// speed inst
	TWSR = 0;
}

void  i2cWrite(uint8_t reg,uint8_t data){
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
	TWDR = reg;										
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

uint8_t i2cRead(uint8_t reg){
	
	volatile 	uint8_t data=0xFF;

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
	TWDR = reg;										
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