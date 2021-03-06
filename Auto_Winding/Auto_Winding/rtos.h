#ifndef RTOS_H
#define RTOS_H

/******************************************************************************************
 * �� ������ ���� ����������� ����� � ����� ChipEnable.ru                                 *
 * http://chipenable.ru/index.php/programming-avr/item/110-planirovschik.html             *
 *                                                                                        *
 * ��������� ������� �������� aka KontAr                                                  *
 * ����: 26.03.2014                                                                       *
 *                                                                                        *
 * ���������:                                                                             *
 * - �������� ����������� ����� ������                                                    *
 * - ��������� �������� ������ �� �����                                                   *
 * - ��� ��������� ���������� ������ ����������� �� ����������                            *
 * - �������� ��������� �� "�����" ������                                                 *
 * - ������� ���� ��������������� � ������ "������"                                       *
 ******************************************************************************************/

#include <commons.h>

#define MAX_TASKS      9               // ���������� �����
#define RTOS_ISR       TIMER0_OVF_vect // ������ ����������
#define TIMER_COUNTER  TCNT0           // �������-�������
#define TIMER_START    130             // ��������� ��� ������� �0


/******************************************************************************************
 * ��������� ������
 */
typedef struct task
{   
   void (*pFunc) (void);               // ��������� �� �������
   u16 delay;                          // �������� ����� ������ �������� ������
   u16 period;                         // ������ ������� ������
   u08 run;                            // ���� ���������� ������ � �������
}task;

/******************************************************************************************
 * ��������� �������
 */
void RTOS_Init (void);
void RTOS_SetTask (void (*taskFunc)(void), u16 taskDelay, u16 taskPeriod);
void RTOS_DeleteTask (void (*taskFunc)(void));
void RTOS_DispatchTask (void);

#endif
