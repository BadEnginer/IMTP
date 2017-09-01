#ifndef _VI_OS_H
#define _VI_OS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#define TASK_QUEUE_SIZE 15

typedef enum {IDLE, DISPOSABLE, CONTINUOUS}TASK_STATE; // Пусто Единожды Много
typedef void (*TP)(void);// указатель на функцию TaskPointer
uint16_t total_time;

typedef struct
{ // задача с параметрами и указателем на функцию
	uint16_t time; // как часто запускать
	uint16_t str_time; // Хранит значение времени для переода после обноления
	TASK_STATE state; // один или всегда =)
	uint8_t run; // Запускать или нет
	TP pFunc; //указатель на функцию
} Task;

typedef struct
{// Очередь для заданения задач
	Task* pTasks[TASK_QUEUE_SIZE + 1];//Очередь указателей на структуру задач
	uint8_t tail; // Количество элементов
} TaskQueue;

void InitVI_OS(TaskQueue* pTaskQueue); // Инициализирует весь деспетчер
void InitTask(Task* pTask, TP pFunc, uint16_t timer); // Настраивает конкретную задачу
uint8_t RunTask(TaskQueue* pTaskQueue, Task* pTask, TASK_STATE new_state, uint16_t new_time);// Добавляет задачу в очередь
void ServerTime(TaskQueue* pTaskQueue); // Служба часов отницает по еденице при каждом срабатывание у задач со временем
void TaskManager(TaskQueue* pTaskQueue); // Диспетчер смотрит что в очереди и если задача готова исполняет её


#endif