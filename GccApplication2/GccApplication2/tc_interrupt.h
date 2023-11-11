/*
 * tc_interrupt.h
 *
 * Created: 11.11.2023 10:51:23
 *  Author: oystebw
 */ 


#ifndef TC_INTERRUPT_H_
#define TC_INTERRUPT_H_

#include <stdint.h>
#include "sam.h"
#include "printf-stdarg.h"
#include "PID.h"
#include "adc.h"
#include "can_controller.h"


void init_TCn( uint8_t channel, float period_s );
 
void TC0_Handler       ( void );
void TC1_Handler       ( void );



#endif /* TC_INTERRUPT_H_ */