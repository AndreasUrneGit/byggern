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
#include "SPI.h"


int main(void){
    // enable global interrupt flags
	//interrupt_init();
	SRAM_init();
	ADC_init();
	oled_init_program();
	SRAM_test();
	menu_init();
	//SPI_init();
	
	oled_reset();
	
	menu_print();
	
	/*
	while(1){
		printf("Er vi i loopen?");
		printf(SPI_Read());
		_delay_ms(100);
	}
	*/
	while(1){
		ADC_sample(&joystick_x, &joystick_y, &slider_right, &slider_left);
		if(joystick_handle()){
			menu_navigate(joystick_position, glob_current_menu);
			menu_print();
		}
		
		_delay_ms(1);
	}
}