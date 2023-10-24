/*
 * PWM.h
 *
 * Created: 24.10.2023 10:05:38
 *  Author: andreurn
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "bit_macros.h"
#include "sam.h"

#define CPU_FREQ 84000000
#define PWM_DIVA_PRESCALER 42
#define PWM_CLK_FREQ (CPU_FREQ / PWM_DIVA_PRESCALER)
#define PWM_PERIOD (1.0 / 50)
#define PWM_MIN_DUTY_CYCLE (0.9 / 20)
#define PWM_MAX_DUTY_CYCLE (2.1 / 20)

void pwm_init();
void pwm_set_dutycycle(double dutycycle);

#endif /* PWM_H_ */