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
	
	uint8_t i = 0;
	
	while(1){
		oled_goto_column(i++);
		oled_goto_line(i / 20);
		oled_putchar('V');
		oled_putchar('i');
		oled_putchar(' ');
		oled_putchar('e');
		oled_putchar('r');
		oled_putchar(' ');
		oled_putchar('f');
		oled_putchar('e');
		oled_putchar('r');
		oled_putchar('d');
		oled_putchar('i');
		oled_putchar('g');
		oled_putchar('e');
		
		if(i == 128){
			i = 0;
		}
		
		_delay_ms(100);
		oled_reset();
	}
}