#include "L6470.h"
#include "as5048.h"
#include "bits_macros.h"
#include <avr/delay.h>
#include <avr/interrupt.h>
uint8_t dataRX;
uint8_t	Okey_Start;
ServoDirect direct = FWD;
//���� � �������� ���������� ���� ������ ���
#define PORT_DATA PORTA
#define PIN_DATA  PINA
#define DDRX_DATA DDRA

//���� � �������� ���������� ����������� ������ ���
#define PORT_SIG PORTC
#define PORT_SIG_EN  PORTB
#define PIN_SIG  PINC
#define PIN_SIG_EN PINB
#define DDRX_SIG DDRC
#define SPEED 15000

//������ ������� � ������� ���������� ����������� ������ ���
#define RS 6
#define RW 7
#define EN 0

#define INVERT_DIRECT(x) (x==REV)?FWD:REV
//������� ������ �������
void LcdWriteCom(unsigned char data)
{
	ClearBit(PORT_SIG, RS);	//��������� RS � 0 - �������
	PORT_DATA = data;		//����� ������ �� ���� ����������
	SetBit(PORT_SIG_EN, EN);	        //��������� E � 1
	_delay_us(2);
	ClearBit(PORT_SIG_EN, EN);	//��������� E � 0 - ������������ �����
	_delay_us(40);
}

//������� ������ ������
void LcdWriteData(unsigned char data)
{
	SetBit(PORT_SIG, RS);	        //��������� RS � 1 - ������
	PORT_DATA = data;		//����� ������ �� ���� ����������
	SetBit(PORT_SIG_EN, EN);	        //��������� E � 1
	_delay_us(2);
	ClearBit(PORT_SIG_EN, EN);	//��������� E � 0 - ������������ �����
	_delay_us(40);
}

//������� �������������
void InitLcd(void)
{
	DDRX_DATA = 0xff;
	PORT_DATA = 0xff;
	DDRX_SIG = 0xff;
	DDRB |=(1<<EN);
	PORT_SIG |= (1<<RW)|(1<<RS);
	PORT_SIG_EN |=(1<<EN);
	ClearBit(PORT_SIG, RW);

	_delay_ms(40);
	LcdWriteCom(0x38); //0b00111000 - 8 ��������� ����, 2 ������
	LcdWriteCom(0xf);  //0b00001111 - �������, ������, �������� ��������
	LcdWriteCom(0x1);  //0b00000001 - ������� �������
	_delay_ms(2);
	LcdWriteCom(0x6);  //0b00000110 - ������ �������� ������, ������ ���
}
void USART_Init(void)
{
  UBRRH = 0;
  UBRRL = 51; //�������� ������ UBRR = (f_osc/16*BAUD)-1
  //RXCIE - ����. ������ ��� ������,RXEN - ����. ������, TXEN - ����. ��������.
  //TXCIE - ����.���������� ��� ��������, UDRIE - ����. ���������� ��� �������� ������
  UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);  
  //URSEL - ���������� � �������� UCSRS, UCSZ -������ ����� � 8 ���,UMSEL - 1������\0�������,
  //UPM - �������� ��������,USBS - ���� ��� 
  UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); 
}
 ISR(USART_RXC_vect)
 {
	 dataRX = UDR;
	 if(dataRX != 48)
	 {
		 Okey_Start = 1;
	 }
	 else 
	 Okey_Start = 0;
 }
int main(void)
{
//	InitVI_OS();
 
	StatusServo status;
	USART_Init();
	SPI_Init();
	initAS5048B();
	InitLcd();
	HardHiZ();
	ReadStatusL6470(&status);
	//SetParam(ADR_ABS_POS,0); // �������� ������� ��������� 
	//SetParam(ADR_KVAL_RUN, 30);// ��������� ��������� ������� 
	//SetParam(ADR_STEP_MODE, 4); // ������ ��� 0
	//SetParam(ADR_FS_SPD,1020);
	//SetParam(ADR_MAX_SPEED, 1020);
	//SetParam(ADR_FS_SPD, 1020);
	//Move(FWD,1000);
	
	//HardStop();
	//StepClock(direct);
	ReadStatusL6470(&status);
			uint8_t T = (uint8_t)direct;
	sei();
// 	int32_t angel = 0;
// 	int32_t angel_old = 0;
// 	int32_t angel_angel = 0;
		LcdWriteData('T');
	//	LcdWriteData('t');
// 		LcdWriteData('.');

	//Run(FWD,80000);
	uint8_t sym = 0;
	DDRD |= 1<<2;
	uint16_t count = 0;
	uint16_t data[200] = {0}; 
	SetParam(ADR_ABS_POS,0);
	uint8_t p = 0;
	//Run(direct,SPEED);
	while(1)
	{
		Run(direct,SPEED);
		data[count] = 0.219*((i2c_read(AS5048_ANGLE_HI) << 6) | (i2c_read(AS5048_ANGLE_LO)));
		//_delay_us(10);
		//PORTD |= (1<<2);
		//_delay_us(10);
		//PORTD &= ~(1<<2);
		ReadStatusL6470(&status);
		
		count++;
		if(count > 199)
		{
			count = 0;
			
		}

		p = PIND;
		if ((!((1 << PD7) & p))&(T==0))
		{
			SoftStop();
			T++;
			_delay_ms(1);
			p = PIND;
			if (!((1 << PD7) & p))
				direct = !direct;
				Run(direct, SPEED);
			//StepClock(direct);
		}
		if ((!((1 << PD6) & p))&(T==1))
		{
			SoftStop();
			T--;
			_delay_ms(1);
			p = PIND;
			if (!((1 << PD6) & p))
				direct = !direct;
				Run(direct, SPEED);
			//StepClock(direct);
		}
		//while(!(BitIsSet(PIND,4)));
		//Move(FWD, 4000000);
		//ReadStatusL6470(&status);
		//	GoTo(2000);
		//	ReadStatusL6470(&status);
		//	GoTo(0);
			//HardStop();
	
// 		while(status.status.statusReg.BUSY)
// 		ReadStatusL6470(&status);
//_delay_ms(100);
if (Okey_Start)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = sym;
	sym+=1;
	//Okey_Start = 0;
}

	//	ReadStatusL6470(&status);
// 		if (status.kval_acc != 255)
// 			status.abs_pos = 1;
		//while(!(BitIsSet(PIND,4)));
	//	Move(REV, 10000);
	//	ReadStatusL6470(&status);
		
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



