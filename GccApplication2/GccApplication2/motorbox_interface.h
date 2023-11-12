/*
 * motorbox_interface.h
 *
 * Created: 10.11.2023 10:46:04
 *  Author: oystebw
 */ 


#ifndef MOTORBOX_INTERFACE_H_
#define MOTORBOX_INTERFACE_H_

#define ENCODER_DATA_MASK 0b111111110

#include <stdint.h>
#include "sam.h"

#include "dac.h"
#include "bit_macros.h"
#include "timer.h"
#include "PWM.h"
#include "printf-stdarg.h"
#include "tc_interrupt.h"
#include <stdlib.h>


typedef enum {LEFT, RIGHT} MOTOR_DIRECTION;

void motor_init();

void enable_motor();
void disable_motor();

void change_motor_direction(MOTOR_DIRECTION direction);
void change_motor_speed(int16_t speed);

int16_t get_motor_position();
char MJ2_read();

void solenoid_shoot();
void change_head_angle(uint8_t reference);


#endif /* MOTORBOX_INTERFACE_H_ */