/*
 * dac.c
 *
 * Created: 07.11.2023 15:34:46
 *  Author: andreurn
 */ 

#include "dac.h"

void dac_init(){
	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL1;
	PMC->PMC_PCR = (PMC_PCR_EN) | (38);
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	
	while(!(PMC->PMC_PCSR1 & PMC_PCSR1_PID38)){
		
	}
	
	DACC->DACC_CHER = DACC_CHER_CH1;
	
	dac_write(0);
}

void dac_write(uint16_t digital_value){
	DACC->DACC_CDR = digital_value;
	
	loop_until_bit_is_set(DACC->DACC_ISR, DACC_ISR_EOC);
}