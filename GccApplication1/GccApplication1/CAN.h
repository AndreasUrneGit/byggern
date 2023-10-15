/*
 * CAN.h
 *
 * Created: 10.10.2023 09:30:54
 *  Author: andreurn
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "CAN_controller.h"

typedef struct {
	unsigned int id;
	uint8_t length;
	char data[8];
} CAN_msg;

void CAN_init(uint8_t mode);
void CAN_transmit(CAN_msg* message);
CAN_msg CAN_receive();


#endif /* CAN_H_ */