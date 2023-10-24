/*
 * PWM.c
 *
 * Created: 24.10.2023 10:05:25
 *  Author: andreurn
 */ 

#include "PWM.h"

static const uint32_t CPRD = PWM_PERIOD * PWM_CLK_FREQ;



void pwm_init(){
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;// Aktivere periferals
	
	while(!(PMC->PMC_PCSR1 & PMC_PCSR1_PID36)){
		
	}
	
	PIOC->PIO_PER |= PIO_PC19;
	
	PIOC->PIO_OER |= PIO_PC19;
	
	PIOC->PIO_PDR |= PIO_PDR_P19; //Disable PIO pin 19 == PIN44
	
	PIOC->PIO_ABSR |= PIO_ABSR_P19; //AB Peripheral select B
	
	//MCK = 84 000 000
	
	//PWM_CLK set clock, clock prescaler and divider 2mhz
	PWM->PWM_CLK = PWM_CLK_DIVA(42); //PWM CLK at 2MHz
	//polarity PWM_CMRx Clock source for specific channel
	PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL; // starts at high level polarity and activates clock a
	//PWM_CPRDx channel period register, periode = CPRD * FREQ / PRESCALAR
	PWM->PWM_CH_NUM[5].PWM_CPRD = PWM_CPRD_CPRD(CPRD);
	
	PWM->PWM_ENA = PWM_ENA_CHID5; // Enable register Channel ID 5

}

void pwm_set_dutycycle(double dutycycle){
	
	if (dutycycle < PWM_MIN_DUTY_CYCLE){
		dutycycle = PWM_MIN_DUTY_CYCLE;
	}
	else if (dutycycle > PWM_MAX_DUTY_CYCLE){
		dutycycle = PWM_MAX_DUTY_CYCLE;
	}
	//this drives the servo and will be the singular way we controll the system 
	 
	//uint32_t clk_dutycycle =  ;
	//PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CPOL;
	REG_PWM_CDTY5 = 1/((PWM_PERIOD-dutycycle*PWM_PERIOD)*PWM_CLK_FREQ);
	//uint32_t clk_dutycycle = (uint32_t)(dutycycle / (PWM_FREQ));

}