/*
 * CAN.c
 *
 * Created: 10.10.2023 09:31:24
 *  Author: andreurn
 */ 

#include "CAN.h"

CAN_Read(){
	// lowering CS
	set_bit(PB4,1);
	// Send initiate read instruction
	SPI_MasterTransmit("00000011");
	// Send 8 bit address
	// -> data stored in the register will be shifted out on the SO pin
	clear_bit(PB4,1);
	// raising CS
}