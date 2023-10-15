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
	CAN_init(MODE_LOOPBACK);
	
	CAN_msg msg = {69, 6, "Hello"};
		
	CAN_msg msg2 = {71, 7, "Oystein"};
	
	CAN_transmit(&msg);
	
	CAN_msg received = CAN_receive();
	
	CAN_transmit(&msg2);
	
	CAN_msg r2 = CAN_receive();
	
	printf("Message received! With length %d and id %d. The message is: %s\r\n", received.length, received.id, received.data);
	
	printf("Message received! With length %d and id %d. The message is: %s\r\n", r2.length, r2.id, r2.data);
	
	while(1){

		_delay_ms(1000);
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