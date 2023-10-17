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

void ADC_sample(uint8_t* joystick_x, uint8_t* joystick_y, uint8_t* slider_right, uint8_t* slider_left){
	volatile char* adc_addr = (char*)0x1400;
	*joystick_x = adc_addr[0];
	*joystick_y = adc_addr[0];
	*slider_right = adc_addr[0];
	*slider_left = adc_addr[0];
	
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