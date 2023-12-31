/*
 * joystick.h
 *
 * Created: 03.10.2023 08:55:00
 *  Author: andreurn
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdlib.h>
#include <stdint.h>

#define FROM_NEUTRAL_HIGH 250
#define FROM_NEUTRAL_LOW 1
#define TO_NEUTRAL_HIGH 230
#define TO_NEUTRAL_LOW 20

typedef enum {Neutral = 0, Right, Left} JoystickPosition;
typedef enum {false, true} bool;

typedef struct{
	uint8_t joystick_x;
	uint8_t button_left;
	uint8_t slider_right;
	uint8_t button_right;
	}GAMEBOARD_VALUES;
	


bool joystick_handle();

void joystick_print();


#endif /* JOYSTICK_H_ */