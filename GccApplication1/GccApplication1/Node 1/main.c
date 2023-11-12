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
#include "game.h"

Game game = {0,0,5};
	
extern JoystickPosition joystick_position;

extern GAMEBOARD_VALUES Gameboard_values;

extern CAN_msg send_message;

int main(void){
    // enable global interrupt flags
	//interrupt_init();
	USART_init(MYUBRR);
	SRAM_init();
	ADC_init();
	oled_init_program();
	menu_init();
	CAN_init(MODE_NORMAL);
	menu_print();
	
	while(1){
		
		if (game.playing){
			game_playing();
			menu_print();
		}
		
		else{
			ADC_sample(&Gameboard_values);
			if(joystick_handle()){
				menu_navigate(joystick_position, glob_current_menu);
				menu_print();
			}
			
			if (Gameboard_values.button_right > 200 && glob_current_menu_item == start_game){
				game.playing = 1;
				ADC_sample(&Gameboard_values);
			}
			if (Gameboard_values.button_right > 200 && glob_current_menu_item == calibrate){
				send_message.data[5] = 1;
				CAN_transmit(&send_message);
				send_message.data[5] = 0;
				_delay_ms(1000);
				ADC_sample(&Gameboard_values);
			}
		}
		
		_delay_ms(20);
	}
}
