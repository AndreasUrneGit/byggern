/*
 * motorbox_interface.c
 *
 * Created: 10.11.2023 10:46:17
 *  Author: oystebw
 */ 

#define DEBUG_MOTOR 0
#include "motorbox_interface.h"

uint16_t MAX_ENCODER_VALUE;

uint8_t solenoid_out = 0;

void motor_init(){
	// PD9 is the enable motor pin
	set_bit(PIOD->PIO_PER, 9);
	set_bit(PIOD->PIO_OER, 9);
	
	// PD10 is the motor direction pin
	set_bit(PIOD->PIO_PER, 10);
	set_bit(PIOD->PIO_OER, 10);
	
	// PD0 is the encoder output enable pin (active low)
	set_bit(PIOD->PIO_PER, 0);
	set_bit(PIOD->PIO_OER, 0);
	set_bit(PIOD->PIO_SODR, 0);
	
	// PD1 is the encoder reset pin (active low)
	set_bit(PIOD->PIO_PER, 1);
	set_bit(PIOD->PIO_OER, 1);
	
	// PA3 controls the solenoid / shooter
	set_bit(PIOA->PIO_PER, 3);
	set_bit(PIOA->PIO_OER, 3);
	set_bit(PIOA->PIO_SODR, 3);
	
	// PD2 is the encoder select low byte pin
	set_bit(PIOD->PIO_PER, 2);
	set_bit(PIOD->PIO_OER, 2);
	
	// PC1->8 is the encoder data pins
	PIOC->PIO_PER |= ENCODER_DATA_MASK;
	PIOC->PIO_ODR |= ENCODER_DATA_MASK;
	
	// enable clock and power to PORT C
	PMC->PMC_PCR = PMC_PCR_EN | ID_PIOC;
	PMC->PMC_PCER0 |= (0b1 << ID_PIOC);
	
	// calibrate encoders
	calibrate_motor_encoder();
	
	if (DEBUG_MOTOR){
		printf("Max encorder value: %u \n\r", MAX_ENCODER_VALUE);
	}
}

void enable_motor(){
	set_bit(PIOD->PIO_SODR, 9);
}

void disable_motor(){
	set_bit(PIOD->PIO_CODR, 9);
}

void change_motor_direction(MOTOR_DIRECTION direction){
	if(direction == LEFT){
		set_bit(PIOD->PIO_CODR, 10);
	}
	else{
		set_bit(PIOD->PIO_SODR, 10);
	}
}

void change_motor_speed(int16_t speed){

	if(speed < 0){
		change_motor_direction(RIGHT);
		dac_write(speed * -1);
	}
	else{
		change_motor_direction(LEFT);
		dac_write(speed);
	}
}

int16_t get_motor_position(){
	int16_t result = 0;
	
	// encoder OE low (active)
	set_bit(PIOD->PIO_CODR, 0);
	
	// encoder select low pin set low to output high byte
	set_bit(PIOD->PIO_CODR, 2);
	
	delay_us(60);
	
	// high byte from encoder
	result |= (MJ2_read() << 8);
	
	// encoder select low pin set high to output low byte
	set_bit(PIOD->PIO_SODR, 2);
	
	delay_us(60);
	
	result |= MJ2_read();
	
	// encoder OE high (inactive)
	set_bit(PIOD->PIO_SODR, 0);
	
	if(result > 10000 || result < 0){
		result = 0;
	}
	
	return result;
}

char MJ2_read(){
	uint32_t inter = PIOC->PIO_PDSR;
	
	inter >>= 1;
	
	return (char)inter;
}

void solenoid_shoot(){
	if(!solenoid_out){
		set_bit(PIOA->PIO_CODR, 3);
		solenoid_out = 1;
		init_TCn(2, 0.02);
	}
}

void change_head_angle(uint8_t reference){
	pwm_set_dutycycle((0.0049 * reference + 0.8755) / 20.0);
}

void calibrate_motor_encoder(){
	enable_motor();
	change_motor_speed(-3000);
	delay_ms(2000);
	disable_motor();
	change_motor_speed(0);
	set_bit(PIOD->PIO_CODR, 1);
	delay_us(20);
	set_bit(PIOD->PIO_SODR, 1);
	
	if (DEBUG_MOTOR){
		printf("Motor position at reset: %u \n\r", get_motor_position());
	}
	
	enable_motor();
	change_motor_speed(3000);
	delay_ms(2000);
	disable_motor();
	change_motor_speed(0);
	
	MAX_ENCODER_VALUE = get_motor_position();
}