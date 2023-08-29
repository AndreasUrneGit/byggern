/*
 * ATmega162_programdriver.h
 *
 * Created: 29.08.2023 16:20:41
 *  Author: andreurn
 */ 
#include <avr/io.h>
//#include <stdint.h>

#define BAUD 9600
#define F_CPU 4915200UL
#define MYUBRR F_CPU/16/BAUD-1

#ifndef ATMEGA162_PROGRAMDRIVER_H_
#define ATMEGA162_PROGRAMDRIVER_H_
void USART_Init( unsigned int ubrr );
void USART_Transmit(unsigned char data);
unsigned char USART_Receive( void );
void USART_Flush( void );

#endif /* ATMEGA162_PROGRAMDRIVER_H_ */