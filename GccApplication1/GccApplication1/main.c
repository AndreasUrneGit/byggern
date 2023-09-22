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
#include "interrupt.h"
#include "OLED.h"
#include "fonts.h"


int main(void){
    // enable global interrupt flags
	//interrupt_init();
	/* Replace with your application code */
	USART_init(MYUBRR);
	SRAM_init();
	ADC_init();
	oled_init_program();
	SRAM_test();

	oled_reset();
	
	oled_print("Jeg er stor!", 8);
	oled_goto_line(1);
	oled_goto_column(0);
	oled_print("Jeg er passe stor!", 5);
	oled_goto_line(2);
	oled_goto_column(0);
	oled_print("Jeg er liten :(", 4);
	
	while(1){
		ADC_test();
		_delay_ms(1000);
	}
}