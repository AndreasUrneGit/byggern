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
#include "CAN.h"


int main(void){
    // enable global interrupt flags
	//interrupt_init();
	USART_init(MYUBRR);
	SRAM_init();
	ADC_init();
	//oled_init_program();
	//menu_init();
	CAN_init(MODE_NORMAL);
	
	CAN_msg message = {1, 4, "Hello!"};
	
	while(1){
		ADC_sample(&joystick_x, &joystick_y, &slider_right, &slider_left);
		/*
		if(joystick_handle()){
			menu_navigate(joystick_position, glob_current_menu);
			menu_print();
		}
		*/
		
		message.data[0] = joystick_x;
		message.data[1] = joystick_y;
		message.data[2] = slider_right;
		message.data[3] = slider_left;
		
		printf("%u\t%u\t%u\t%u\n\r", joystick_x, joystick_y, slider_right, slider_left);
		
		CAN_transmit(&message);
		
		_delay_ms(10);
	}
}