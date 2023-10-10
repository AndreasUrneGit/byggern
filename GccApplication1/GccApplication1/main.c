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
	oled_init_program();
	menu_init();
	CAN_Init();
	
	
	SRAM_test();
	
	oled_reset();
	
	menu_print();
	
	CAN_msg msg1;
	
	CAN_msg msg2;
	
	while(1){
		msg1.id = 0;
		msg1.length = 3;
		msg1.data[0] = 1;
		msg1.data[1] = 2;
		msg1.data[2] = 3;
		
		CAN_Transmit(msg1);
		
		_delay_ms(1);
		
		msg2 = CAN_Receive();
		
		for(int x = 0; x < msg2.length; x++){
			printf("%2d", msg2.data[x]);
		}
		_delay_ms(100);
	}
	
	while(1){
		ADC_sample(&joystick_x, &joystick_y, &slider_right, &slider_left);
		if(joystick_handle()){
			menu_navigate(joystick_position, glob_current_menu);
			menu_print();
		}
		
		_delay_ms(1);
	}
}