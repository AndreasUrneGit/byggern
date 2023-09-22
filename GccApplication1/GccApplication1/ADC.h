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

void ADC_init();
void ADC_test();
void ADC_sample(uint8_t* joystick_y, uint8_t* slider_right, uint8_t* slider_left, uint8_t* joystick_x);



#endif /* ADC_H_ */