/*
 * CFile1.c
 *
 * Created: 15.09.2023 11:41:14
 *  Author: andreurn
 */ 


#include "interrupt.h"

void interrupt_init(){
	//enable the global interrupt
	sei();
	//Configure INT2 (PE0) as input
	clear_bit(DDRE, PE0);
	//enable external interrupt IOT0 on rising edge
	set_bit(MCUCR, ISC01);
	set_bit(MCUCR, ISC00);
	//enable INT2 in the General Interrupt Control Register (GICR)
	set_bit(GICR, INT2);
	
}

ISR(INT2_vect){

}