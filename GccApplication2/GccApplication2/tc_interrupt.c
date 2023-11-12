/*
 * tc_interrupt.c
 *
 * Created: 11.11.2023 10:51:07
 *  Author: oystebw
 */ 

#include "tc_interrupt.h"

#define DEBUG_TC0_INTERRUPT 0
#define DEBUG_TC1_INTERRUPT 1
#define DEBUG_TC2_INTERRUPT 1
#define IRQ_TC0_PRIORITY 2
#define CAN_MSG_ID 2
#define CAN_MSG_DATA_LENGTH 1
#define CAN_MSG_DATA 1
#define CAN_NODE1_MAIL_ID 0
extern uint8_t servo_reference;
extern IR_sensor IR;
extern uint8_t solenoid_out;

const CAN_MESSAGE goal = {CAN_MSG_ID, CAN_MSG_DATA_LENGTH, 0b00000001};

void init_TCn( uint8_t channel, float period_s ){
	
	//riktig klokkesyklus 84 MHz -> satt periode i s
	//WAVSEL = 10, teller opp til RC og setter interupt, resets når den kommer til RC
	TC0->TC_CHANNEL[channel].TC_CMR |= TC_CMR_WAVSEL_UP_RC | TC_CMR_WAVE;
	
	//setter riktig periode i RA registeret
	TC0->TC_WPMR = TC_WPMR_WPKEY_PASSWD;
	TC0->TC_CHANNEL[channel].TC_RC = 42000000 * period_s;
	TC0->TC_WPMR = TC_WPMR_WPKEY_PASSWD | 1;
	TC0->TC_CHANNEL[channel].TC_IER = TC_IER_CPCS; 
	TC0->TC_CHANNEL[channel].TC_IDR = ~TC_IDR_CPCS;
	
	
	
	PMC->PMC_PCR = (PMC_PCR_EN) | (27 + channel); //enable pin
	PMC->PMC_PCER0 |= (1 << (27 + channel)); //aktivere periferals
	while (!(PMC->PMC_PCSR0 & (1 << (27 + channel)))) {
		
	}
	//enable clock
	TC0->TC_CHANNEL[channel].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN;
	
	NVIC_EnableIRQ(TC0_IRQn + channel);
	NVIC_SetPriority(TC0_IRQn + channel, IRQ_TC0_PRIORITY - channel);
}

void TC0_Handler       ( void ){
	//cli();
	//noen mikrosekund mistes i get_motor_position() pga delay (40 us + linjer)
	uint16_t motor_position = (uint16_t)get_motor_position();
	change_motor_speed(PID_controller(motor_position, servo_reference));
	
	if (DEBUG_TC0_INTERRUPT){
		printf("Encoder value: %u\n\r", motor_position);
		printf("Servo ref: %u\n\r", 255 - servo_reference);
	}
	
	TC0->TC_CHANNEL[0].TC_SR;
	NVIC_ClearPendingIRQ(ID_TC0);
}

void TC1_Handler       ( void ){
	
	IR.prev_val = IR.current_val;
	IR.current_val = adc_read();
	
	if (IR.prev_val > 1800 && IR.current_val < 1800){
		
		can_send(&goal, CAN_NODE1_MAIL_ID);
		
		if (DEBUG_TC1_INTERRUPT){
			printf("GOAL \n\r");
		}
	}

	
	TC0->TC_CHANNEL[1].TC_SR;
	NVIC_ClearPendingIRQ(ID_TC1);
}



void TC2_Handler       ( void ){
	
	
	if (DEBUG_TC2_INTERRUPT){
			printf("Shot \n\r");
	}
	
	set_bit(PIOA->PIO_SODR, 3);
	solenoid_out = 0;

	
	TC0->TC_CHANNEL[2].TC_SR;
	NVIC_ClearPendingIRQ(ID_TC2);
	
	NVIC_DisableIRQ(TC2_IRQn);
}