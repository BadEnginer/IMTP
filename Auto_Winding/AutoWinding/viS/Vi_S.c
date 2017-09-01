#include "Vi_S.h"

void InitVI_OS(TaskQueue* pTaskQueue)//, частота работы)
{
	total_time = 0;
	pTaskQueue->tail = 0; // Обноляет всю очередь
}

void InitTask(Task* pTask, TP pFunc, uint16_t timer)
{
	pTask->time = timer;	// Итерируем время отсюда
	pTask->run = 0;
	pTask->str_time = timer; // Запоминаем время тут
	pTask->state = IDLE; // Что бы не запустилась пока 
	pTask->pFunc = pFunc; // Любая функция 
}

uint8_t RunTask(TaskQueue* pTaskQueue,Task* pTask, TASK_STATE new_state, uint16_t timer)
{
	pTask->state = new_state; 
	//if (timer != 0 )// Почему ?
		pTask->time = timer;  
	for(uint8_t i = 0; i <= pTaskQueue->tail ; i++)
		if(pTaskQueue->pTasks[i]->pFunc == pTask->pFunc)
			{
				pTaskQueue->pTasks[i] = pTask; // А может и не надо вдруг одна задача в разных потоках
				return 2; // Дефайн а то что это ? 
			} 
		else if((pTaskQueue->tail) <= TASK_QUEUE_SIZE)
			{
				pTaskQueue->pTasks[pTaskQueue->tail] = pTask;
				pTaskQueue->tail++;
				return 1;
			}
	return 255; 
}

void ServerTime(TaskQueue* pTaskQueue) // ПОработать над названием а то что это за хуйня
{ 
	if (pTaskQueue->tail > 0)
	{
		for (uint8_t i = 0; i < pTaskQueue->tail; i++)
		{
			if (pTaskQueue->pTasks[i]->run != 0 ) // Тоже дефайн не ? 
				continue;
			if(pTaskQueue->pTasks[i]->time != 0)
				pTaskQueue->pTasks[i]->time--;
			if((pTaskQueue->pTasks[i]->time == 0) && (pTaskQueue->pTasks[i]->state != IDLE))
			{
				pTaskQueue->pTasks[i]->run = 1 ;
				if(pTaskQueue->pTasks[i]->state == CONTINUOUS)
					pTaskQueue->pTasks[i]->time = pTaskQueue->pTasks[i]->str_time;
					
			}
		}
	}
	
}
void TaskManager(TaskQueue* pTaskQueue)
{
	
	TP GoToTask;
	if (pTaskQueue->tail > 0)
	{
		for (uint8_t i = 0; i < pTaskQueue->tail; i++)
		{
			if ((pTaskQueue->pTasks[i]->run != 0) && (pTaskQueue->pTasks[i]->state != IDLE))
			{
				GoToTask = pTaskQueue->pTasks[i]->pFunc;
				GoToTask();
				pTaskQueue->pTasks[i]->run = 0;
				if(pTaskQueue->pTasks[i]->state == DISPOSABLE)
					pTaskQueue->pTasks[i]->state = IDLE;
			}
		}	
	}
	else return;
}
