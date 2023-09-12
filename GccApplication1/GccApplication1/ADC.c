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
	
	/*
	set_bit(TCCR3A, WGM00);
	set_bit(TCCR3A, CS00);
	set_bit(TCCR3B, COM01);
	 while (1){
		PORTD ^= (1 << PD4);
		_delay_ms(1000);
	}
	*/
	
}