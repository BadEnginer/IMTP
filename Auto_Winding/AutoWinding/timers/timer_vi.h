#ifndef _TIMER_VI_H
#define _TIMER_VI_H

#include <avr/io.h>

#define F_CTC 3000000UL // „астоат что мы хотим получить
#define N_DIV 1	// ƒелитель таймера
#define F_OCR ((F_CPU/(F_CTC * 2 * N_DIV)) - 1) // ‘ормула расчета

#define F_CTC_0 1000UL // Частоат что мы хотим получить
#define N_DIV_0 1024	// делитель таймера
#define F_OCR_0 ((F_CPU/(F_CTC_0 * 2 * N_DIV_0)) - 1) // формула расчета

#define TCCR0A TCCR0 // конфиги конкретные
#define TIFR0 TIFR	 // статусы 
#define TIMSK0 TIMSK // конфиги общие 
// TCNT счетный регистр тут тикает время
// OCR сравнения со счетным если одинаково то .. 

typedef enum {DIV_0,DIV_1,DIV_8,DIV_64,DIV_256,DIV_1024} DIV_TIMER;
typedef enum {NORM,PWM,CTC,FAST} TIMERS_MODE;
typedef enum {EN_TOV,EN_OCF,EN_ALL,DIS_ALL} INTERPUT_EN;
//set MODE 00-Norm 01-PWM 10-CTC 11-FAST_PWM 
void initTime0(DIV_TIMER div,TIMERS_MODE tM,uint8_t ocr0,INTERPUT_EN en);
void initTime1(DIV_TIMER div);



/*
TCCR0 - Timer/Counter Control Register
	(7) FOC - силовое переключение пина 
	(6,3) WGM00 и WGM01 - выбор режимы работы таймера 
		  00-normal - просто тикает
		  10-СТС - сброс таймера при совпадении 
		  01-11-FAST PWM и Phase Correct PWM - шимы ... с ними позже 
	(5,4) COM01 и СОМ00 как будит вести себя пин на контроллере
	(2,1,0) CS02, CS01, CS00 делитель 
			000-disable 
			001-SLC 
			010-SLC/8 
			011-SLC/64 
			100-SCL/256 
			101-SCL/1024
			остальные берут такт с выводов Т0
TIMSK - Общий регистр для всех трех таймеров разрешение прерываний 
	(0) TOIE0 прерывания при переполнении 
	(1) OCIE0 прерывания по совподению
TIFR общий для всех содержит статусы при возникновении событий
 	(0) TOV0 возникает при при переполнении 
	(1) OCF0 возникает при сравнении 

*/
#endif