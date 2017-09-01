#include "CycleBuff.h"

void InitBuff(CycleBuff* buff,uint8_t* pBuff,uint8_t max_sym,TYPE_DATA type_data)
{
	CleanBuffer(buff);
	buff->max_char = max_sym - 1; // ��� ���� ���� ���� ���� ������� ��� �� 0 � 1
	buff->data = pBuff;	
	buff->type_data = type_data;
	switch(type_data)
	{
		case I8:
			buff->std = sizeof(int8_t);
			break;
		case I16:
			buff->std = sizeof(int16_t);
			break;
		case I32:
			buff->std = sizeof(int32_t);
			break;
		case F:
			buff->std = sizeof(float);
			break;
		default:
			buff->std = sizeof(int8_t);	
	}
}

void CleanBuffer(CycleBuff* buff)
{
	buff->tail = 0;
	buff->head = 0;
	buff->count = 0;
}
// ��������� � ���������� ��� ����� 
void PutData(CycleBuff* buff, const uint8_t* data)//�������� ������ � �����
{
	
	memcpy(&buff->data[(buff->tail * buff->std)], data, buff->std);    //�������� ������ � ������
	buff->count++;               				   //�������������� ������� ��������
	buff->tail++;                			       //� ������ ������ ������
	if ((buff->tail) > (buff->max_char)) // ��������� ������ ���� ���� ���. ��������
		buff->tail = 0;
	if ((buff->count) > (buff->max_char+1)) // ���� �������� �����
	{
		buff->count--; // ���� ��������������
		buff->head++; // ������� ��������� ������
		if ((buff->head) > (buff->max_char)) // �������� ������� ���� ��������� ��������
			buff->head = 0;
	}
	
}

//����� ������ �� ������
uint8_t* GetData(CycleBuff* buff)
{
	static uint8_t *temp = 0; 
	if ((buff->count) > 0)	 //���� ����� �� ������
	{
		temp = &buff->data[(buff->head * buff->std)];	  // ��������� ���������
		buff->count--;                                    //��������� ������� ��������
		buff->head++;									  //�������������� ������ ������ ������
		if (buff->head >= (buff->max_char)+1)
			buff->head = 0;
	}
	return (temp);
}

float AveregBuff(CycleBuff* buff,void* answer) // ������� ������� �� ������ � ���������� �������� ���������
{
	int32_t tempInt = 0;
	float tempFlt = 0;
	float	answerFloat = 0;
	int32_t answerInt = 0;
	static float speed_data = 0;
	if (buff->type_data == F)
		for(uint8_t i = 0; i <= (buff->max_char); i++)
		{
			memcpy(&tempFlt, ((buff->data)+(i*buff->std)), buff->std);
			answerFloat += tempFlt; 
		}
	else
		for(uint8_t i = 0; i <= (buff->max_char); i++)
		{
			memcpy(&tempInt, ((buff->data)+(i*buff->std)), buff->std);
			answerInt += tempInt;
		}
	if(buff->type_data == F) 
	{
		answerFloat = (answerFloat / (buff->count));
		*(float*)answer = answerFloat;
		return (answerFloat - speed_data);
	}
	else
	{
		answerInt = (answerInt / (buff->count));
		*(int32_t*)answer = answerInt;
		return (float) (answerInt - (int32_t)speed_data);
	}
}