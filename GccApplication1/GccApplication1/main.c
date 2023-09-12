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
#include "sram.h"
#include "ADC.h"

int main(void){
    /* Replace with your application code */
	USART_init(MYUBRR);
	SRAM_init();
	ADC_init();
	SRAM_test();
	

    while (1){
	
	_delay_ms(1000);
	
    }
}