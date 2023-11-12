/*
 * ADC.h
 *
 * Created: 12.09.2023 14:03:48
 *  Author: andreurn
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "bit_macros.h"
#include "joystick.h"

void ADC_init();
void ADC_test();
void ADC_sample(GAMEBOARD_VALUES* values);



#endif /* ADC_H_ */