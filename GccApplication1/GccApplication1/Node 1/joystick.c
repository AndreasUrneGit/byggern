/*
 * joystick.c
 *
 * Created: 03.10.2023 08:55:21
 *  Author: andreurn
 */ 

#include "joystick.h"

JoystickPosition joystick_position = Neutral;

GAMEBOARD_VALUES Gameboard_values;

bool joystick_handle(){
	//printf("%u \n\r", Gameboard_values.joystick_x);
	switch(joystick_position){
		case Neutral:
			if(Gameboard_values.joystick_x > FROM_NEUTRAL_HIGH){
				joystick_position = Right;
				return true;
			}
			if(Gameboard_values.joystick_x < FROM_NEUTRAL_LOW){
				joystick_position = Left;
				return true;
			}
			return false;
		
		case Right:
			if(Gameboard_values.joystick_x < TO_NEUTRAL_HIGH){
				joystick_position = Neutral;
			}
			return false;
		
		case Left:
			if(Gameboard_values.joystick_x > TO_NEUTRAL_LOW){
				joystick_position = Neutral;
			}
			return false;
		
	}
}

void joystick_print(){
	switch(joystick_position){
		case Right:
			printf("\n\rHøyre");
			break;
		case Left:
			printf("\n\rVenstre");
			break;
		case Neutral:
			printf("\n\rNøytral");
			break;
	}
}