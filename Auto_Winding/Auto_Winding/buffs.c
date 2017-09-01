#ifndef _CYCLE_BUFF_H
#define _CYCLE_BUFF_H

typedef enum {FIFO,CYCLE,STECK} TYPE_BUFF;

typedef struct
{
	uint8_t		tail;  		// Хвост показывает на свободный место в буффере
	uint8_t		head;  		// Голова указывает на символ для 
	uint8_t		count;		// Текущее количество символов 
	uint8_t		size;		// Размер буффере
	uint8_t		std;		// Размер одного элемента
	TYPE_BUFF	type_buff;  // Тип буфера фифо циклический или стек
	void*		data;		// указатель на участок памяти где все храниться
} Buff;

buffInit	(Buff *);
buffPutData	(Buff *);
buffGetData	(Buff *);
buffClear	(Buff *);
buffSize	(Buff *);
buffFull	(Buff *);
buffEmpty	(Buff *);
buffNumMax	(Buff *);
buffNumMin	(Buff *);
buffNumAverInt	(Buff *);
buffNumAverFloat(Buff *);

init
void* buffMalloc();

#endif //_CYCLE_BUFF_H