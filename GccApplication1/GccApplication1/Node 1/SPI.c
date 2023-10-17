/*
 * SPI.c
 *
 * Created: 10.10.2023 08:48:34
 *  Author: andreurn
 */ 

#include "SPI.h"

void spi_init(void){
	/* Set SCL, MOSI & PB4 to output, MISO and the rest to input */

	set_bit(DDRB, PB5);
	set_bit(DDRB, PB7);
	set_bit(DDRB, PB4);
	set_bit(PORTB, PB4);
	
	/* Enable SPI, set it in Master and set clock*/

	set_bit(SPCR, SPE);
	set_bit(SPCR, MSTR);
	set_bit(SPCR, SPR0);
	
}

void spi_write(uint8_t data){
	/* Start transmission */

	SPDR = data;
	/* Wait for transmission complete */
	loop_until_bit_is_set(SPSR, SPIF);

}

uint8_t spi_read(){
	
	SPDR = 0xFF;
	
	loop_until_bit_is_set(SPSR, SPIF);
	
	return SPDR;
}