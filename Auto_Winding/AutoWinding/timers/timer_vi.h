#ifndef _TIMER_VI_H
#define _TIMER_VI_H

#include <avr/io.h>

#define F_CPU 16000000UL
#define F_CTC 3000000UL // Частоат что мы хотим получить
#define N_DIV 1	// Делитель таймера
#define F_OCR ((F_CPU/(F_CTC * 2 * N_DIV)) - 1) // Формула расчета

#define F_CPU_0 16000000UL
#define F_CTC_0 1000UL // Частоат что мы хотим получить
#define N_DIV_0 1024	// Делитель таймера
#define F_OCR_0 ((F_CPU_0/(F_CTC_0 * 2 * N_DIV_0)) - 1) // Формула расчета

typedef enum {DIV_0,DIV_1,DIV_8,DIV_64,DIV_256,DIV_1024} DIV_TIMER;

void initTime0(DIV_TIMER div);
void initTime1(DIV_TIMER div);
void init_CTC_Time1();

#endif