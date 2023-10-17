/*
 * CAN.c
 *
 * Created: 10.10.2023 09:31:24
 *  Author: andreurn
 */ 

#include "CAN.h"


void CAN_init(uint8_t mode){
	
	mcp_2515_init(mode);
	
}


void CAN_transmit(CAN_msg* msg){
	
	mcp_2515_write(MCP_TXB0SIDH, msg->id >> 3);
	mcp_2515_write(MCP_TXB0SIDL, msg->id << 5);
	mcp_2515_write(MCP_TXB0DLC, msg->length);
	
	for(int x = 0; x < msg->length; x++){
		mcp_2515_write(MCP_TXB0Dm + x, msg->data[x]);
	}
	
	mcp_2515_request_to_send(0);
	
}


CAN_msg CAN_receive(){
	
	CAN_msg received_message;
	
	uint8_t id_high = mcp_2515_read(MCP_RXB0SIDH) << 3;
	uint8_t id_low = mcp_2515_read(MCP_RXB0SIDL) >> 5;
	
	received_message.id = id_high + id_low;
	
	uint8_t length = mcp_2515_read(MCP_RXB0DLC);
	
	received_message.length = length;
	
	for(int x = 0; x < length; x++){
		received_message.data[x] = mcp_2515_read(MCP_RXB0Dm + x);
	}
	
	// tells the MCP that the buffer is read
	mcp_2515_bit_modify(MCP_CANINTF, 1, 0);
	
	return received_message;
}
