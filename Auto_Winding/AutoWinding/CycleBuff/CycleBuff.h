#ifndef _CYCLE_BUFF_H
#define _CYCLE_BUFF_H

#include <avr/io.h>
#define SIZE_BUFF 8 //exponent 2 for filter slide mid
#define IN_POWER_2(x) (1<<x)
typedef enum {I8, I16, I32, F} TYPE_DATA;

typedef struct
{

	uint16_t tail;  		// Хвост показывает на свободный место в буффере
	uint16_t head;  		// Голова указывает на первый символ
	uint16_t count;		// Количество символов
	uint16_t max_char;   // Маусимальное число элементов
	uint8_t* data; 	//указатель на участок памяти где все храниться
	uint8_t std;
	TYPE_DATA type_data;
} CycleBuff;

void InitBuff(CycleBuff* buff,uint8_t* pBuff,uint8_t max_sym, TYPE_DATA type_data);
void CleanBuffer(CycleBuff* buff);
void PutData(CycleBuff* buff,const uint8_t* data);
uint8_t* GetData(CycleBuff* buff);
float AveregBuff(CycleBuff* buff,void*);

#endif //_CYCLE_BUFF_H
