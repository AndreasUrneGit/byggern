/*
 * timer.c
 *
 * Created: 10.11.2023 15:07:49
 *  Author: oystebw
 */ 

#include "timer.h"

volatile uint32_t wait = 0;

static void SysTick_init_us(uint16_t period){
	SysTick->LOAD = ((period * 84) & SysTick_LOAD_RELOAD_Msk) - 1;
	
	SysTick->VAL = 0;
	
	NVIC_SetPriority(SysTick_IRQn, IRQ_priority_SysTick);
	
	SysTick->CTRL = (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
	
}

void delay_ms(uint16_t ms){
	wait = ms;
	SysTick_init_us(1000);
	while(wait){
		
	}
}

void delay_us(uint16_t us){
	wait = us;
	SysTick_init_us(1);
	while(wait){
		
	}
}

void SysTick_Handler(){
	if(wait){
		wait--;
	}
	else{
		SysTick->CTRL = 0;
	}
}