#include "CycleBuff.h"

void InitBuff(CycleBuff* buff,uint8_t* pBuff,uint8_t max_sym,TYPE_DATA type_data)
{
	CleanBuffer(buff);
	buff->max_char = max_sym - 1; // Ибо если есть хоть один элемент это не 0 а 1
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
// локальная и глобальная что лучше 
void PutData(CycleBuff* buff, const uint8_t* data)//положить символ в буфер
{
	
	memcpy(&buff->data[(buff->tail * buff->std)], data, buff->std);    //помещаем данные в память
	buff->count++;               				   //инкрементируем счетчик символов
	buff->tail++;                			       //и индекс хвоста буфера
	if ((buff->tail) > (buff->max_char)) // Проверяем индекс если выше мах. обнуляем
		buff->tail = 0;
	if ((buff->count) > (buff->max_char+1)) // Если символов много
	{
		buff->count--; // Анти инкрементируем
		buff->head++; // Удаляем последний символ
		if ((buff->head) > (buff->max_char)) // Проверка индекса если превышает обноляем
			buff->head = 0;
	}
	
}

//взять символ из буфера
uint8_t* GetData(CycleBuff* buff)
{
	static uint8_t *temp = 0; 
	if ((buff->count) > 0)	 //если буфер не пустой
	{
		temp = &buff->data[(buff->head * buff->std)];	  // Временное хранилище
		buff->count--;                                    //уменьшаем счетчик символов
		buff->head++;									  //инкрементируем индекс головы буфера
		if (buff->head >= (buff->max_char)+1)
			buff->head = 0;
	}
	return (temp);
}

float AveregBuff(CycleBuff* buff,void* answer) // Считает среднее из буфера и возврощает скорость изменения
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