#include "spi.h"

/*инициализация SPI*/
void SPI_Init(void)
{
  /*настройка портов ввода-вывода
  все выводы, кроме MISO выходы*/
  SPI_DDRX = (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(0<<SPI_MISO);
  SPI_PORTX = (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(1<<SPI_MISO);
   
  /*разрешение spi,старший бит вперед,мастер, режим 0*/
  SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<SPR1)|(0<<SPR0);//
  SPSR = (0<<SPI2X);
}

/*отослать байт данных по SPI*/
void SPI_WriteByte(uint8_t data)
{
   SPI_PORTX &= ~(1<<SPI_SS); 
   SPDR = data;
   while(!(SPSR & (1<<SPIF)));
   SPI_PORTX |= (1<<SPI_SS); 
}


/*отослать и получить байт данных по SPI*/
uint8_t SPI_ReadByte(uint8_t data)
{
   uint8_t report = 0;
   
	SPI_PORTX &= ~(1<<SPI_SS);

   SPDR = data;
   while(!(SPSR & (1<<SPIF)));
   report = SPDR;

	SPI_PORTX |= (1<<SPI_SS); 
  
   return report; 
}

/*отправить несколько байт данных по SPI*/
void SPI_WriteArray(uint8_t num, uint8_t *data)
{
   SPI_PORTX &= ~(1<<SPI_SS); 
   while(num--)
   {
      SPDR = *data++;
      while(!(SPSR & (1<<SPIF)));
   }
   SPI_PORTX |= (1<<SPI_SS); 
}

/*отправить и получить несколько байт данных по SPI*/
void SPI_ReadArray(uint8_t num, uint8_t *data)
{
   SPI_PORTX &= ~(1<<SPI_SS); 
   while(num--)
   {
      SPDR = *data;
      while(!(SPSR & (1<<SPIF)));
      *data++ = SPDR; 
   }
   SPI_PORTX |= (1<<SPI_SS); 
}

void SPI_ReadArraySpecial(uint8_t first_byte, uint8_t num, uint8_t *data)
{
	SPI_PORTX &= ~(1<<SPI_SS);
	data[0] = first_byte;
// 	while(num--)
// 	{
// 		SPDR = *data;
// 		while(!(SPSR & (1<<SPIF)));
// 		*data++ = SPDR;
// 	}
	for(uint8_t i = 0; i < num; i++)
	{
		SPDR = data[i];
		while(!(SPSR & (1<<SPIF)));
		data[i] = SPDR;
	}
	SPI_PORTX |= (1<<SPI_SS);
}

void SPI_WriteArraySpecial(uint8_t first_bite, uint8_t num, uint8_t *data)
{
   SPI_PORTX &= ~(1<<SPI_SS); 
   *data = first_bite;
   while(num--)
   {
      SPDR = *data++;
      while(!(SPSR & (1<<SPIF)));
   }
   SPI_PORTX |= (1<<SPI_SS); 
}