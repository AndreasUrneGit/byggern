/*
 * ATmega162_programdriver.h
 *
 * Created: 29.08.2023 16:20:41
 *  Author: andreurn
 */ 

#ifndef ATMEGA162_PROGRAMDRIVER_H_
#define ATMEGA162_PROGRAMDRIVER_H_

#include <avr/io.h>
#include "bit_macros.h"
//#include <stdint.h>

#define BAUD 9600
#define F_CPU 4915200UL
#define MYUBRR F_CPU/16/BAUD-1

void USART_init( unsigned int ubrr );
void USART_transmit(unsigned char data);
unsigned char USART_receive( void );

#endif