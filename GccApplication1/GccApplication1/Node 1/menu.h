/*
 * menu.h
 *
 * Created: 03.10.2023 09:27:29
 *  Author: andreurn
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "joystick.h"
#include "OLED.h"

typedef enum {main_menu = 0} Menu;
typedef enum {start_game = 0, highscore, calibrate} Main_menu;
typedef struct {
	uint8_t main_menu;
} Menu_length; // Nullindeksert lengde

char* main_menu_str[3];


uint8_t glob_current_menu_item; 
Menu glob_current_menu;
Menu_length glob_menu_length;

void menu_navigate(JoystickPosition joystick_pos, Menu current_menu);
uint8_t get_menu_length(Menu current_menu);
void menu_init();
void menu_print();

#endif /* MENU_H_ */