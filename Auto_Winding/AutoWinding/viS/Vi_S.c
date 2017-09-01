#include "Vi_S.h"

void InitVI_OS(TaskQueue* pTaskQueue)//, ������� ������)
{
	total_time = 0;
	pTaskQueue->tail = 0; // �������� ��� �������
}

void InitTask(Task* pTask, TP pFunc, uint16_t timer)
{
	pTask->time = timer;	// ��������� ����� ������
	pTask->run = 0;
	pTask->str_time = timer; // ���������� ����� ���
	pTask->state = IDLE; // ��� �� �� ����������� ���� 
	pTask->pFunc = pFunc; // ����� ������� 
}

uint8_t RunTask(TaskQueue* pTaskQueue,Task* pTask, TASK_STATE new_state, uint16_t timer)
{
	pTask->state = new_state; 
	//if (timer != 0 )// ������ ?
		pTask->time = timer;  
	for(uint8_t i = 0; i <= pTaskQueue->tail ; i++)
		if(pTaskQueue->pTasks[i]->pFunc == pTask->pFunc)
			{
				pTaskQueue->pTasks[i] = pTask; // � ����� � �� ���� ����� ���� ������ � ������ �������
				return 2; // ������ � �� ��� ��� ? 
			} 
		else if((pTaskQueue->tail) <= TASK_QUEUE_SIZE)
			{
				pTaskQueue->pTasks[pTaskQueue->tail] = pTask;
				pTaskQueue->tail++;
				return 1;
			}
	return 255; 
}

void ServerTime(TaskQueue* pTaskQueue) // ���������� ��� ��������� � �� ��� ��� �� �����
{ 
	if (pTaskQueue->tail > 0)
	{
		for (uint8_t i = 0; i < pTaskQueue->tail; i++)
		{
			if (pTaskQueue->pTasks[i]->run != 0 ) // ���� ������ �� ? 
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
