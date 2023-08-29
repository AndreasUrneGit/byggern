/*
 * GccApplication1.c
 *
 * Created: 29.08.2023 10:11:57
 * Author : andreurn
 */ 

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>

#include "ATmega162_programdriver.h"

int main(void){
    /* Replace with your application code */
	DDRA = 0;
	USART_Init(MYUBRR);
    while (1){
	
	USART_Transmit('H');
	PORTA ^= (1<<PA0);
	//USART_Flush();
	_delay_ms(1000);
    }
}