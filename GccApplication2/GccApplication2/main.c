/*
 * GccApplication2.c
 *
 * Created: 17.10.2023 08:54:01
 * Author : andreurn
 */ 


#include "sam.h"
#include "bit_macros.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "PWM.h"
#include "dac.h"
#include "adc.h"
#include "delay.h"


int main(void){
    /* Initialize the SAM system */
	SystemInit();
	configure_uart();
	
	uint32_t can_br = (SMP << 24) | (BRP << 16) | (SJW << 12) | ((PROSEG - 1) << 8) | ((PS1 - 1) << 4) | (PS2 - 1);
	
	//can_init_def_tx_rx_mb(can_br);
	pwm_init();
	dac_init();
	adc_init();
	
	// disable watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
	
	set_bit(PIOA->PIO_PER, 19);
	set_bit(PIOA->PIO_PER, 20);
	set_bit(PIOA->PIO_OER, 19);
	set_bit(PIOA->PIO_OER, 20);
	
	set_bit(PIOA->PIO_SODR, 19);
	set_bit(PIOA->PIO_SODR, 20); 
	
	
	printf("Entering loop");
	
	set_bit(PIOD->PIO_PER, 9);
	set_bit(PIOD->PIO_OER, 9);
	set_bit(PIOD->PIO_SODR, 9);
	
	set_bit(PIOD->PIO_PER, 10);
	set_bit(PIOD->PIO_OER, 10);
	
    while (1){
		printf("ADC: %u\n\r", adc_read());
    }
}
