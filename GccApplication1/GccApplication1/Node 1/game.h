/*
 * game.h
 *
 * Created: 12.11.2023 12:10:34
 *  Author: andreurn
 */ 


#ifndef GAME_H_
#define GAME_H_

#include "CAN.h"
#include "ADC.h"
#include "joystick.h"
#include "OLED.h"
#include <stdlib.h>


typedef struct {
	uint8_t playing;
	uint8_t goals;
	uint8_t over;
} Game;


void game_playing( void );


#endif /* GAME_H_ */