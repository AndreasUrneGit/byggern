/*
 * CAN.h
 *
 * Created: 10.10.2023 09:30:54
 *  Author: andreurn
 */ 


#ifndef CAN_H_
#define CAN_H_

#define CAN_enable_SPI clear_bit(PORTB, PB4)
#define CAN_disable_SPI set_bit(PORTB, PB4)

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

#include "bit_macros.h"
#include "SPI.h"
#include "mcp2515.h"

typedef struct {
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} CAN_msg; 

void CAN_Init();
uint8_t CAN_Read(uint8_t);
void CAN_Write(uint8_t, uint8_t);
void CAN_RequestToSend(uint8_t);
uint8_t CAN_ReadStatus();
void CAN_BitModify(uint8_t, uint8_t, uint8_t);
void CAN_Reset();
void CAN_Transmit(CAN_msg);
CAN_msg CAN_Receive();



#endif /* CAN_H_ */