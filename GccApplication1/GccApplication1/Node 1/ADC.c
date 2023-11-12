/*
 * ADC.c
 *
 * Created: 12.09.2023 14:04:06
 *  Author: andreurn
 */ 
#include "ADC.h"

void ADC_init(){

	set_bit(TCCR3A, COM3A0);
	set_bit(TCCR3B, CS00);
	set_bit(TCCR3B, WGM12);
	set_bit(DDRD, PD4);
	
}

void ADC_sample(GAMEBOARD_VALUES* values){
	volatile char* adc_addr = (char*)0x1400;
	
	values->joystick_x = adc_addr[0];
	values->button_left = adc_addr[0];
	values->slider_right = adc_addr[0];
	values->button_right = adc_addr[0];
	
	adc_addr[0] = 0;
}


void ADC_test(){
	volatile char* adc_addr = (char*)0x1400;
	uint8_t data;
	
	
	data = adc_addr[0];
	printf("\r%8d", data);
	data = adc_addr[0];
	printf("%8d", data);
	data = adc_addr[0];
	printf("%8d", data);
	data = adc_addr[0];
	printf("%8d\n\n", data);
	
	adc_addr[0] = 0;
}