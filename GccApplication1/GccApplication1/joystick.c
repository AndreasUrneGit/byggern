/*
 * joystick.c
 *
 * Created: 03.10.2023 08:55:21
 *  Author: andreurn
 */ 

#include "joystick.h"

bool joystick_handle(){
	switch(joystick_position){
		case Neutral:
			if(joystick_y > FROM_NEUTRAL_HIGH){
				joystick_position = Up;
				return true;
			}
			if(joystick_y < FROM_NEUTRAL_LOW){
				joystick_position = Down;
				return true;
			}
			if(joystick_x > FROM_NEUTRAL_HIGH){
				joystick_position = Right;
				return true;
			}
			if(joystick_x < FROM_NEUTRAL_LOW){
				joystick_position = Left;
				return true;
			}
			return false;
		
		case Up:
			if(joystick_y < TO_NEUTRAL_HIGH){
				joystick_position = Neutral;
			}
			return false;
			
		case Down:
			if(joystick_y > TO_NEUTRAL_LOW){
				joystick_position = Neutral;
			}
			return false;
		
		case Right:
			if(joystick_x < TO_NEUTRAL_HIGH){
				joystick_position = Neutral;
			}
			return false;
		
		case Left:
			if(joystick_x > TO_NEUTRAL_LOW){
				joystick_position = Neutral;
			}
			return false;
		
	}
}

void joystick_print(){
	switch(joystick_position){
		case Up:
			printf("\n\rOpp");
			break;
		case Down:
			printf("\n\rNed");
			break;
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