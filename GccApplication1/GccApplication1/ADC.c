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

void ADC_test(){
	volatile char* adc_addr = (char*)0x1400;
	uint8_t data;
	
	
	data = adc_addr[0];
	printf("%8d\r\t", data);
	data = adc_addr[0];
	printf("%8d\t", data);
	data = adc_addr[0];
	printf("%8d\t", data);
	data = adc_addr[0];
	printf("%8d\n\n", data);
	
	adc_addr[0] = 0;
}