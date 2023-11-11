/*
 * PID.h
 *
 * Created: 07.11.2023 15:58:23
 *  Author: andreurn
 */ 


#ifndef PID_H_
#define PID_H_

#include "stdint.h"
#include "printf-stdarg.h"

typedef struct {
	float k_p;
	float k_i;
	float k_d;
	float period;
	float previous_error;
	float sum_error;
	float max_output;
	float min_output;
	} PID_data;
	
	void PID_controller_init(float k_p, float k_i, float k_d, float period, float max_output, float min_output);
	void PID_controller_reset_error();
	int PID_controller(uint16_t current_value, uint16_t reference);



#endif /* PID_H_ */