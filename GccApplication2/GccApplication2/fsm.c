/*
 * fsm.c
 *
 * Created: 12.11.2023 12:24:26
 *  Author: andreurn
 */ 

#include "fsm.h"

void fsm_playing(){
	enable_motor();
	change_motor_speed(0);
	// middle position
	pwm_set_dutycycle(1.5 / 20);
	PID_controller_reset_error();
	
	// PID controller
	NVIC_EnableIRQ(TC0_IRQn);
	// IR sampling
	NVIC_EnableIRQ(TC1_IRQn);
	
	while(playing){
		
	}
}

void fsm_waiting(){
	disable_motor();
	change_motor_speed(0);
	pwm_set_dutycycle(1.5 / 20);
	
	// PID controller
	NVIC_DisableIRQ(TC0_IRQn);
	// IR sampling
	NVIC_DisableIRQ(TC1_IRQn);
	
	while(!playing){
		
	}
}