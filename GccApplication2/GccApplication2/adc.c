/*
 * adc.c
 *
 * Created: 07.11.2023 15:27:37
 *  Author: andreurn
 */ 

#include "adc.h"

IR_sensor IR;

void adc_init(){
	ADC->ADC_MR = ADC_MR_FREERUN;
	ADC->ADC_CHER = ADC_CHDR_CH0;
	PMC->PMC_PCR = (PMC_PCR_EN) | (37);
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;
	
	while(!(PMC->PMC_PCSR1 & PMC_PCSR1_PID37)){

	}
	
	ADC->ADC_CR = ADC_CR_START;
}

uint16_t adc_read(){
	return ADC->ADC_CDR[0];
}