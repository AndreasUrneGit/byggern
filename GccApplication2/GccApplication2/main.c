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
#include "motorbox_interface.h"
#include "PID.h"

uint8_t servo_ref = 0;

int main(void){
    /* Initialize the SAM system */
	SystemInit();
	// disable watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	
	configure_uart();
	
	uint32_t can_br = (SMP << 24) | (BRP << 16) | (SJW << 12) | ((PROSEG - 1) << 8) | ((PS1 - 1) << 4) | (PS2 - 1);
	
	can_init_def_tx_rx_mb(can_br);
	pwm_init();
	dac_init();
	adc_init();
	motor_init();
	
	
	set_bit(PIOA->PIO_PER, 19);
	set_bit(PIOA->PIO_PER, 20);
	set_bit(PIOA->PIO_OER, 19);
	set_bit(PIOA->PIO_OER, 20);
	
	set_bit(PIOA->PIO_SODR, 19);
	set_bit(PIOA->PIO_SODR, 20);
	
	
	printf("Entering loop");
	
	PID_controller_init(100, 10, 0, 0.02, 4095, -4095);
	
	
    while (1){
		change_motor_speed(PID_controller(servo_ref, get_motor_position()));
		delay_ms(20);
		printf("servo_ref: %u\n\r", servo_ref);
    }
}
