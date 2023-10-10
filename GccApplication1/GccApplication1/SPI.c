/*
 * SPI.c
 *
 * Created: 10.10.2023 08:48:34
 *  Author: andreurn
 */ 

#include "SPI.h"

void SPI_init(void){
	/* Set SCL, MOSI & PB4 to output, MISO and the rest to input */
	set_bit(DDRB, PB5);
	set_bit(DDRB, PB7);
	set_bit(DDRB, PB4);
	clear_bit(DDRB, PB6);
	
	set_bit(PORTB, PB4);
	
	/* Enable SPI, set it in Master and set clock*/
	set_bit(SPCR, SPE);
	set_bit(SPCR, MSTR);
	set_bit(SPCR, SPR0);
}

void SPI_MasterTransmit(uint8_t data){
	/* Start transmission */

	SPDR = data;
	/* Wait for transmission complete */
	loop_until_bit_is_set(SPSR, SPIF);

}

uint8_t SPI_Read(){
	SPI_MasterTransmit(0x00);
	return SPDR;
}