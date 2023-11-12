/*
 * ATmega162_programdriver.c
 *
 * Created: 29.08.2023 16:19:57
 *  Author: andreurn
 */ 
#include "uart.h"

void USART_init(unsigned int ubrr){
	// Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// Set frame format: 8data, 2stop bit
	UCSR0C = (1<<URSEL0)| (1 << USBS0) |(3<<UCSZ00);
	
	fdevopen(USART_transmit, USART_receive);
}

void USART_transmit(unsigned char data){
	// wait for empty transmit buffer

	loop_until_bit_is_set(UCSR0A, UDRE0);
	//put data into buffer, sends the data
	UDR0 = data;
}
unsigned char USART_receive( void ){
	// Wait for data to be received

	loop_until_bit_is_set(UCSR0A, RXC0);
	// Get and return received data from buffer
	return UDR0;
}