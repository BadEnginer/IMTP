#include "timer_vi.h"

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

void initTime0(DIV_TIMER div,TIMERS_MODE tM,uint8_t ocr0,INTERPUT_EN en){
	OCR0 =  ocr0;
	switch(tM){
		case(NORM): TCCR0A |= (0 << WGM01) | (0 << WGM00);break;
		case(PWM):  TCCR0A |= (0 << WGM01) | (1 << WGM00);break;
		case(CTC):  TCCR0A |= (1 << WGM01) | (0 << WGM00);break;
		case(FAST): TCCR0A |= (1 << WGM01) | (1 << WGM00);break;
		default:	TCCR0A |= (0 << WGM01) | (0 << WGM00);
	}
	//TIFR0 |= (1 << OCF0);	//overflow interrupt OCF0 сравнение TOV0 переполнение 
	switch(en){
		case(EN_TOV):  TIMSK0 |= (0 << OCIE0)|(1 << TOIE0);break;
		case(EN_OCF):  TIMSK0 |= (1 << OCIE0)|(0 << TOIE0);break;
		case(EN_ALL):  TIMSK0 |= (1 << OCIE0)|(1 << TOIE0);break;
		case(DIS_ALL): TIMSK0 |= (0 << OCIE0)|(0 << TOIE0);break;
		default:TIMSK0 |= (0 << OCIE0)|(0 << TOIE0);	
	}
	switch(div){
		case DIV_0:    TCCR0A |= (0 << CS02) | (0 << CS01) | (0 << CS00); break; //set divider 000-disable 001-SLC 010-SLC/8 011-SLC/64 100-SCL/256 101-SCL/1024
		case DIV_1:    TCCR0A |= (0 << CS02) | (0 << CS01) | (1 << CS00); break;
		case DIV_8:    TCCR0A |= (0 << CS02) | (1 << CS01) | (0 << CS00); break;
		case DIV_64:   TCCR0A |= (0 << CS02) | (1 << CS01) | (1 << CS00); break;
		case DIV_256:  TCCR0A |= (1 << CS02) | (0 << CS01) | (0 << CS00); break;
		case DIV_1024: TCCR0A |= (1 << CS02) | (0 << CS01) | (1 << CS00); break;	
		default:	   TCCR0A |= (0 << CS02) | (0 << CS01) | (0 << CS00);
	}
	
}
