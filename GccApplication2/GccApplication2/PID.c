/*
 * PID.c
 *
 * Created: 07.11.2023 15:58:03
 *  Author: andreurn
 */ 
#include "PID.h"

#define PID_DEBUG 0

static PID_data PID;

extern uint16_t MAX_ENCODER_VALUE;

uint8_t servo_reference;

void PID_controller_init(float k_p, float k_i, float k_d, float period, float max_output, float min_output){
	PID.k_p =k_p;
	PID.k_i =k_i;
	PID.k_d =k_d;
	
	PID_controller_reset_error();
	
	PID.period = period;
	PID.max_output = max_output;
	PID.min_output = min_output;
	
}

void PID_controller_reset_error(){
	PID.previous_error = 0;
	PID.sum_error = 0;
}

int PID_controller(uint16_t current_value, uint16_t reference){
	reference = 255 - reference;
	reference *= (MAX_ENCODER_VALUE / 255.0);
	
	float error = reference - current_value;
	PID.sum_error += error;
	
	float u_p = PID.k_p * error;
	float u_i = PID.k_i * PID.period * PID.sum_error;
	float u_d = (PID.k_d / PID.period) * (error - PID.previous_error);
	
	float u = u_p + u_i + u_d;
	
	PID.previous_error = error;
	
	if ( u > PID.max_output){
		u = PID.max_output;
	}
	else if (u < PID.min_output){
		u = PID.min_output;
	}
	
	if(PID_DEBUG){
		printf("Reference: %u\n\r", reference);
		printf("Encoder: %u\n\r", current_value);
		printf("Output: %f\n\r", u);
	}
	
	return (int) u;
}