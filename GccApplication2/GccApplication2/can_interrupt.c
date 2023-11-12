/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "can_interrupt.h"

#define DEBUG_INTERRUPT 0

extern uint8_t servo_reference;
extern uint8_t playing;

/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval 
 */
void CAN0_Handler( void )
{
	//cli();
	//if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			can_receive(&message, 1);

		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			can_receive(&message, 2);
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}

		//if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
		if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
		if(DEBUG_INTERRUPT)printf("\n\n\r");
		for (int i = 0; i < message.data_length; i++)
		{
			if(DEBUG_INTERRUPT)printf("%d  ", message.data[i]);
		}
		
		if(message.data[5]){
			calibrate_motor_encoder();
		}
		
		playing = message.data[4];
		
		if(playing){
			servo_reference = message.data[0];
			change_head_angle(message.data[2]);
			
			if(message.data[3] > 100){
				solenoid_shoot();
			}
		}
		
	}
	
	if(can_sr & CAN_SR_MB0)
	{
		//if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();
}
