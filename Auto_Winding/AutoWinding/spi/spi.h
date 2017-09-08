#ifndef SPI_H
#define SPI_H

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include <avr/io.h>
// #include <util/delay.h>
// #include <avr/interrupt.h>
#include <stdint.h>

#define __save_interrupt() SREG
#define __restore_interrupt(var) SREG = (var)
#define __disable_interrupt() cli()
#define __enable_interrupt() sei()
#ifndef __delay_cycles
	#define __delay_cycles(var) _delay_us((unsigned int)(var)/(F_CPU/1000000))
#endif


#define SPI_PORTX   PORTB
#define SPI_DDRX    DDRB

#define SPI_MISO   6 
#define SPI_MOSI   5
#define SPI_SCK    7
#define SPI_SS     4

/*инициализация SPI модуля*/
void initSPI(void); 

/*отправить байт данных по SPI*/
void SPI_WriteByte(uint8_t data); 

/*отправить и получить байт данных по SPI*/
uint8_t SPI_ReadByte(uint8_t data);

/*отправить несколько байт данных по SPI*/
void SPI_WriteArray(uint8_t num, uint8_t *data);

/*отправить и получить несколько байт данных по SPI*/
void SPI_ReadArray(uint8_t num, uint8_t *data);

void SPI_ReadArraySpecial(uint8_t first_byte, uint8_t num, uint8_t *data);

#endif //SPI_H