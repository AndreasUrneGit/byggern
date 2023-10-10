/*
 * CAN.c
 *
 * Created: 10.10.2023 09:31:24
 *  Author: andreurn
 */ 

#include "CAN.h"


void CAN_Init(){
	uint8_t val = 2;
	
	SPI_init();
	CAN_Reset();
	
	val = CAN_ReadStatus();
	/*
	if(val != MODE_CONFIG){
		printf("MCP2515 is not in Config mode! Its config bits are %2d\n", val);
	}*/
	//loopback mode
	CAN_BitModify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	//set to normal operating modus
	
	
	//see if there are other factors
	
}

uint8_t CAN_Read(uint8_t can_address){
	CAN_enable_SPI;

	// Send initiate read instruction
	SPI_MasterTransmit(MCP_READ);
	SPI_MasterTransmit(can_address);
	uint8_t r_msg = SPI_Read();
	// Send 8 bit address
	// -> data stored in the register will be shifted out on the SO pin

	CAN_disable_SPI;

	return r_msg;
}

void CAN_Write(uint8_t address, uint8_t data){
	CAN_enable_SPI;
	
	SPI_MasterTransmit(MCP_WRITE);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	
	CAN_disable_SPI;
}

void CAN_RequestToSend(uint8_t location){
	CAN_enable_SPI;
	
	if(location < 9 && location > 0){
		SPI_MasterTransmit(0b10000000 | location);	
	}
	else{
		printf("\n\rInvalid CAN request to send");
	}
	
	CAN_disable_SPI;
}

uint8_t CAN_ReadStatus(){
	CAN_enable_SPI;
	
	SPI_MasterTransmit(MCP_READ_STATUS);
	uint8_t r_status = SPI_Read();
	printf("The status is %u\n\r", r_status);
	CAN_disable_SPI;
	return r_status;
}

void CAN_BitModify(uint8_t address_byte, uint8_t mask_byte, uint8_t data_byte){
	CAN_enable_SPI;
	
	SPI_MasterTransmit(MCP_BITMOD);
	SPI_MasterTransmit(address_byte);
	SPI_MasterTransmit(mask_byte);
	SPI_MasterTransmit(data_byte);
	
	CAN_disable_SPI;
}

void CAN_Reset(){
	CAN_enable_SPI;
	
	SPI_MasterTransmit(MCP_RESET);
	
	CAN_disable_SPI;
	
	_delay_ms(10);
}

void CAN_Transmit(CAN_msg msg){
	CAN_enable_SPI;
	
	unsigned int id = msg.id;
	uint8_t id_high = id >> 3;
	uint8_t id_low = id << 5;
	
	CAN_Write(MCP_TXB0SIDH, id_high);
	CAN_Write(MCP_TXB0SIDL, id_low);
	CAN_Write(MCP_TXB0DLC, msg.length);
	
	for(int x = 0; x < msg.length; x++){
		CAN_Write(MCP_TXB0Dm + x, msg.data[x]);
	}
	
	SPI_MasterTransmit(MCP_RTS_TX0);
	
	CAN_BitModify(30, 0b1000, 0b1000);
	
	CAN_disable_SPI;
}

CAN_msg CAN_Receive(){
	CAN_enable_SPI;
	
	CAN_msg received_message;
	
	uint8_t id_high = CAN_Read(MCP_RXB0SIDH);
	uint8_t id_low = CAN_Read(MCP_RXB0SIDL);
	
	received_message.id = (id_high << 8) | id_low;
	
	uint8_t length = CAN_Read(MCP_RXB0DLC);
	
	received_message.length = (length & 0b1111);
	
	for(int x = 0; x < length; x++){
		received_message.data[x] = CAN_Read(MCP_RXB0Dm + x);
	}
	
	CAN_BitModify(MCP_CANINTF, 1, 0);
	
	CAN_disable_SPI;
	return received_message;
}
