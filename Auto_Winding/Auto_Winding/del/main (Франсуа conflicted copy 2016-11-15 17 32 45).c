#include "L6470.h"
#include "as5048.h"
#include "bits_macros.h"
#include <avr/delay.h>

//порт к которому подключена шина данных ЖКД
#define PORT_DATA PORTA
#define PIN_DATA  PINA
#define DDRX_DATA DDRA

#define WAIT_PROCESS while(!(BitIsSet(PIND,4)))

//порт к которому подключены управляющие выводы ЖКД
#define PORT_SIG PORTC
#define PIN_SIG  PINC
#define DDRX_SIG DDRC

//Номера выводов к которым подключены управляющие выводы ЖКД
#define RS 6
#define RW 7
#define EN 1

// #define MAX_NUM 11
uint32_t power(uint8_t x,uint8_t y)
{
	uint32_t temp = x;
		for(uint8_t i = 0; i < y; i++)
			temp *= temp;
}
int CountNumInNum(int data)
{
	int count = 1;//1001
	int expon = 10;
	while (data)
	{
		if (data < 10)
		break;
		data /= expon;
		count++;
	}
	return count;
}
char* GetStringChar(int32_t data,char* buff)
{
	uint8_t size = CountNumInNum(data);
	for (uint8_t i = 0, i < size; i++)
	{
		buff[i] =(char) (data/power(10,size - i)) +'0';
		data %= buff[i] * power(10,size - i);
	}
	return buff;
}


//функция записи команды
void LcdWriteCom(unsigned char data)
{
	ClearBit(PORT_SIG, RS);	//установка RS в 0 - команды
	PORT_DATA = data;		//вывод данных на шину индикатора
	SetBit(PORT_SIG, EN);	        //установка E в 1
	_delay_us(2);
	ClearBit(PORT_SIG, EN);	//установка E в 0 - записывающий фронт
	_delay_us(40);
}

//функция записи данных
void LcdWriteData(unsigned char data)
{
	SetBit(PORT_SIG, RS);	        //установка RS в 1 - данные
	PORT_DATA = data;		//вывод данных на шину индикатора
	SetBit(PORT_SIG, EN);	        //установка E в 1
	_delay_us(2);
	ClearBit(PORT_SIG, EN);	//установка E в 0 - записывающий фронт
	_delay_us(40);
}

//функция инициализации
void InitLcd(void)
{
	DDRX_DATA = 0xff;
	PORT_DATA = 0xff;
	DDRX_SIG = 0xff;
	PORT_SIG |= (1<<RW)|(1<<RS)|(1<<EN);
	ClearBit(PORT_SIG, RW);

	_delay_ms(40);
	LcdWriteCom(0x38); //0b00111000 - 8 разрядная шина, 2 строки
	LcdWriteCom(0xf);  //0b00001111 - дисплей, курсор, мерцание включены
	LcdWriteCom(0x1);  //0b00000001 - очистка дисплея
	_delay_ms(2);
	LcdWriteCom(0x6);  //0b00000110 - курсор движется вправо, сдвига нет
}


int main(void)
{
	StatusServo status;
	 	
	SPI_Init();
	initAS5048B();
	HardHiZ();
	InitLcd();
	//SetParam(ADR_STEP_MODE, 4);
	int32_t angel = 0;
	int32_t angel_old = 0;
	int32_t angel_angel = 0;
	ReadStatusL6470(&status);
	uint8_t i = 0;
	while(1)
	{
		
// 		
		i++;
		if ((i % 8) == 0)
		InitLcd();
 		LcdWriteData(i);
		_delay_ms(200);
//  		WAIT_PROCESS;
//  		Move(REV, 1);
// 		ReadStatusL6470(&status);
// 		WAIT_PROCESS;
// 		Move(FWD, 1);
// 		ReadStatusL6470(&status);
		
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






	 				