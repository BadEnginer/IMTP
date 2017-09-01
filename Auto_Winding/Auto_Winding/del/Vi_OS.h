#ifndef _VI_OS_H
#define _VI_OS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#define TASK_QUEUE_SIZE 15

typedef enum {IDLE, DISPOSABLE, CONTINUOUS}TASK_STATE; // ����� �������� �����
typedef void (*TP)(void);// ��������� �� ������� TaskPointer
uint16_t total_time;

typedef struct
{ // ������ � ����������� � ���������� �� �������
	uint16_t time; // ��� ����� ���������
	uint16_t str_time; // ������ �������� ������� ��� ������� ����� ���������
	TASK_STATE state; // ���� ��� ������ =)
	uint8_t run; // ��������� ��� ���
	TP pFunc; //��������� �� �������
} Task;

typedef struct
{// ������� ��� ��������� �����
	Task* pTasks[TASK_QUEUE_SIZE + 1];//������� ���������� �� ��������� �����
	uint8_t tail; // ���������� ���������
} TaskQueue;

void InitVI_OS(TaskQueue* pTaskQueue); // �������������� ���� ���������
void InitTask(Task* pTask, TP pFunc, uint16_t timer); // ����������� ���������� ������
uint8_t RunTask(TaskQueue* pTaskQueue, Task* pTask, TASK_STATE new_state, uint16_t new_time);// ��������� ������ � �������
void ServerTime(TaskQueue* pTaskQueue); // ������ ����� �������� �� ������� ��� ������ ������������ � ����� �� ��������
void TaskManager(TaskQueue* pTaskQueue); // ��������� ������� ��� � ������� � ���� ������ ������ ��������� �


#endif