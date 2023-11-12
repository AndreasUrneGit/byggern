/*
 * GccApplication2.c
 *
 * Created: 17.10.2023 08:54:01
 * Author : andreurn
 */ 

#define DEBUG 0

#define CONTROL_PERIOD (20.0 / 1000.0)
#define IR_PERIOD (50.0 / 1000.0)
#define CONTROL_TC_CHANNEL 0
#define IR_TC_CHANNEL 1
#define K_P 8
#define K_I 5
#define K_D 0.2
#define PID_MAX_OUTPUT 4095
#define PID_MIN_OUTPUT -4095

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
#include "tc_interrupt.h"
#include "timer.h"

extern uint8_t servo_reference;

void test_light ( void ){
	set_bit(PIOA->PIO_PER, 20);
	set_bit(PIOA->PIO_OER, 20);
	set_bit(PIOA->PIO_SODR, 20);
}

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
	PID_controller_init(K_P, K_I , K_D, CONTROL_PERIOD, PID_MAX_OUTPUT, PID_MIN_OUTPUT);
	
	test_light();
	
	printf("Entering loop");
	
	init_TCn( CONTROL_TC_CHANNEL, CONTROL_PERIOD );
	init_TCn( IR_TC_CHANNEL, IR_PERIOD );

    while (1){
		
		
		if(DEBUG){
			change_motor_speed(PID_controller(get_motor_position(), servo_reference));
			printf("Encoder value: %u\n\r", get_motor_position());
			printf("Servo ref: %u\n\r", servo_reference);
			delay_ms(20);
		}
    }
}
