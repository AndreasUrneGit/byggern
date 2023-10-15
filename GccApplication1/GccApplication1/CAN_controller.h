/*
 * CAN_controller.h
 *
 * Created: 15.10.2023 17:03:30
 *  Author: oystebw
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

#define CAN_enable_SPI clear_bit(PORTB, PB4)
#define CAN_disable_SPI set_bit(PORTB, PB4)

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

#include "mcp2515.h"
#include "bit_macros.h"
#include "SPI.h"

void mcp_2515_init(uint8_t mode);
void mcp_2515_reset();
void mcp_2515_write(uint8_t address, uint8_t data);
uint8_t mcp_2515_read(uint8_t address);
uint8_t mcp_2515_read_status();
void mcp_2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void mcp_2515_request_to_send(uint8_t buffer);
void mcp_2515_set_mode(uint8_t mode);


#endif /* CAN_CONTROLLER_H_ */