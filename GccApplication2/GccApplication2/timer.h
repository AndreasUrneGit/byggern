/*
 * timer.h
 *
 * Created: 10.11.2023 15:08:01
 *  Author: oystebw
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#define FREQ_CPU 84000000
#define IRQ_priority_SysTick 0

#include <stdint.h>
#include "sam.h"

void delay_ms(uint16_t ms);
void delay_us(uint16_t us);



#endif /* TIMER_H_ */