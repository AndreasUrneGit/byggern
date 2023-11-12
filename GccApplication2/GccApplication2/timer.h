/*
 * timer.h
 *
 * Created: 10.11.2023 15:08:01
 *  Author: oystebw
 */ 


//Denne timermodulen er inspirert av https://github.com/henrikhestnes/TTK4155-Byggern/blob/master/node2/timer.c

#ifndef TIMER_H_
#define TIMER_H_

#define FREQ_CPU 84000000
#define IRQ_priority_SysTick 0

#include <stdint.h>
#include "sam.h"
#include "printf-stdarg.h"

void delay_ms(uint16_t ms);
void delay_us(uint16_t us);
void SysTick_Handler();

#endif /* TIMER_H_ */