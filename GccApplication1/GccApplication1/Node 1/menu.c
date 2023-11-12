/*
 * menu.c
 *
 * Created: 03.10.2023 09:27:16
 *  Author: andreurn
*/ 

#include "menu.h"

char* main_menu_str [3] = {"Play", "Highscore", "Calibrate"};

void menu_navigate(JoystickPosition joystick_pos, Menu current_menu){
	uint8_t menu_length = get_menu_length(current_menu);
	
	joystick_print();
	switch (joystick_pos){
		case Left:
			if (glob_current_menu_item == 0){
				glob_current_menu_item = menu_length;
				break;
			}
			glob_current_menu_item -= 1;
			break;
		case Right:
			if (glob_current_menu_item == menu_length){
				glob_current_menu_item = 0;
				break;
			}
			glob_current_menu_item += 1;
			break;
		case Neutral:
			break;
		
	}
	
}

void menu_print(){
	oled_reset();
	oled_print("\t", 4);
	oled_print("Main menu\n\n\r", 8);
	for (uint8_t i = 0; i <= glob_menu_length.main_menu; i++){
		uint8_t font_size = 5;
		if (i == glob_current_menu_item){
			font_size = 8;
		}
		
		oled_print("\t",4);
		oled_print(main_menu_str[i],font_size);
		oled_print("\n\r",font_size);
	}
	oled_goto_line(2 + glob_current_menu_item);
	oled_print("->", 8);
}

 
uint8_t get_menu_length(Menu current_menu){
	switch (current_menu){
		case main_menu:
			return glob_menu_length.main_menu;
	}
}


void menu_init(){
	glob_menu_length.main_menu = 2;
	glob_current_menu_item = 0;
	glob_current_menu = main_menu;
}

