#include "timer_vi.h"
// Переделать таймеры что бы задавать можно было через время в милисекундах а не делитель а то хуйня 
 //И софтварные таймеры добавить... ибо нех 
void initTime1(DIV_TIMER div)
{
	TCNT1  = 0;
	TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << WGM11) | (0 << WGM10);
	TCCR1B = (0 << WGM13) | (0 << WGM12) | (0 << CS12) | (0 << CS11) | (0 << CS10);
	//TIFR1  = (1 << TOV1);		//overflow interrupt
	//TIMSK1 |= (1 << TOIE1);		//enable interrupt
	switch(div)
	{
		case DIV_0:
			TCCR1A |= (0 << CS12) | (0 << CS11) | (0 << CS10); break; //set divider 000-disable 001-SLC 010-SLC/8 011-SLC/64 100-SCL/256 101-SCL/1024
		case DIV_1:
			TCCR1A |= (0 << CS12) | (0 << CS11) | (1 << CS10); break;
		case DIV_8:
			TCCR1A |= (0 << CS12) | (1 << CS11) | (0 << CS10); break;
		case DIV_64:
			TCCR1A |= (0 << CS12) | (1 << CS11) | (1 << CS10); break;
		case DIV_256:
			TCCR1A |= (1 << CS12) | (0 << CS11) | (0 << CS10); break;
		case DIV_1024:
			TCCR1A |= (1 << CS12) | (0 << CS11) | (1 << CS10); break;
			
		default: TCCR1A |= (0 << CS12) | (0 << CS11) | (0 << CS10);
	}
}

void initTime0(DIV_TIMER div)
{
	#define TCCR0A TCCR0
	#define TIFR0 TIFR
	#define TIMSK0 TIMSK
	TCCR0A = (1 << WGM01) | (0 << WGM00);	//set MODE 00-Norm 01-PWM 10-CTC 11-FAST_PWM
	TIFR0 |= (1 << OCF0);	//overflow interrupt OCF0 сравнение TOV0 переполнение 
	TIMSK0 |= (1 << OCIE0);	//enable interrupt
	TCNT0 = 0;
	OCR0 =  252;
	switch(div)
	{
		case DIV_0:
			TCCR0A |= (0 << CS02) | (0 << CS01) | (0 << CS00); break; //set divider 000-disable 001-SLC 010-SLC/8 011-SLC/64 100-SCL/256 101-SCL/1024
		case DIV_1:
			TCCR0A |= (0 << CS02) | (0 << CS01) | (1 << CS00); break;
		case DIV_8:
			TCCR0A |= (0 << CS02) | (1 << CS01) | (0 << CS00); break;
		case DIV_64:
			TCCR0A |= (0 << CS02) | (1 << CS01) | (1 << CS00); break;
		case DIV_256:
			TCCR0A |= (1 << CS02) | (0 << CS01) | (0 << CS00); break;
		case DIV_1024:
			TCCR0A |= (1 << CS02) | (0 << CS01) | (1 << CS00); break;
			
		default: TCCR0A |= (0 << CS02) | (0 << CS01) | (0 << CS00);
	}
	
}

void init_CTC_Time1()
{
	// Init PIN for true work
	DDRB = ((1 << DDB6)); 
	PORTB = ((1 << DDB6));
	TCNT1  = 0;
	// Init CTC mode div 
	//TCCR1A = (1 << COM1A0) | (1 << COM1B0) | (1 << COM1C0) | (0 << WGM11) | (0 << WGM10);
	TCCR1B = (0 << WGM13) | (1 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);
	//TIMSK1 |= (1 << TOIE1);		//enable interrupt
	OCR1A = F_OCR;
}