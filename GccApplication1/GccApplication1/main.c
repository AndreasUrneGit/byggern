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
#include "joystick.h"
#include "menu.h"


int main(void){
    // enable global interrupt flags
	//interrupt_init();
	SRAM_init();
	ADC_init();
	oled_init_program();
	SRAM_test();
	menu_init();
	
	oled_reset();
	
	menu_print();
	
	set_bit(DDRB, PB5);
	set_bit(DDRB, PB7);
	set_bit(DDRB, PB4);
	set_bit(SPCR, SPE);
	set_bit(SPCR, MSTR);
	set_bit(SPCR, SPR0);
	
	clear_bit(PORTB, PB4);
	SPDR = 'a';
	loop_until_bit_is_set(SPSR, SPIF);
	set_bit(PORTB, PB4);
	
	while(1){
		ADC_sample(&joystick_x, &joystick_y, &slider_right, &slider_left);
		if(joystick_handle()){
			menu_navigate(joystick_position, glob_current_menu);
			menu_print();
		}
		
		_delay_ms(1);
	}
}