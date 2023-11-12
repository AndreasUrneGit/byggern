/*
 * CAN_controller.c
 *
 * Created: 15.10.2023 17:03:52
 *  Author: oystebw
 */ 

#include "CAN_controller.h"

void mcp_2515_init(uint8_t mode){
	spi_init();
	mcp_2515_reset();
	
	/* 
	Frequency of the crystal (F_osc) = 16MHz
	Buss baud rate (F_br) = 125 KHz
	Baudrate Prescalar = F_osc/2F_br
	time quantum (T_q) = 2*T_osc
	*/

	uint8_t BRP = CAN_FREQ / (2 * 16 * BAUDRATE);
	
	mcp_2515_write(MCP_CNF3, WAKFIL_DISABLE | (PS2 - 1));
	mcp_2515_write(MCP_CNF2, BTLMODE | SAMPLE_3X | ((PS1 - 1) << 3) | (PROSEG - 1));
	mcp_2515_write(MCP_CNF1, SJW4 | (BRP-1));
	
	_delay_ms(100);
	
	//enables reading of a can bit flag for IR sensor
	mcp_2515_bit_modify(MCP_CANINTE, 1, 1);

	printf("%x\r\n", mcp_2515_read(MCP_CNF1));
	printf("%x\r\n", mcp_2515_read(MCP_CNF2));
	printf("%x\r\n", mcp_2515_read(MCP_CNF3));
	
	
	mcp_2515_set_mode(mode);
}

void mcp_2515_reset(){
	CAN_enable_SPI;
	
	spi_write(MCP_RESET);
	
	CAN_disable_SPI;
	
	_delay_ms(10);
}

void mcp_2515_write(uint8_t address, uint8_t data){
	CAN_enable_SPI;
	
	spi_write(MCP_WRITE);
	spi_write(address);
	spi_write(data);
	
	CAN_disable_SPI;
}

uint8_t mcp_2515_read(uint8_t address){
	CAN_enable_SPI;

	spi_write(MCP_READ);
	spi_write(address);
	uint8_t msg = spi_read();

	CAN_disable_SPI;

	return msg;
}

uint8_t mcp_2515_read_status(){
	CAN_enable_SPI;
	
	spi_write(MCP_READ_STATUS);
	uint8_t status = spi_read();
	
	CAN_disable_SPI;
	
	return status;
}

void mcp_2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	CAN_enable_SPI;
	
	spi_write(MCP_BITMOD);
	spi_write(address);
	spi_write(mask);
	spi_write(data);
	
	CAN_disable_SPI;
}

void mcp_2515_request_to_send(uint8_t buffer){
	CAN_enable_SPI;
	
	spi_write(MCP_RTS_TX + (0b1 << buffer));
	
	CAN_disable_SPI;
}

void mcp_2515_set_mode(uint8_t mode){
	mcp_2515_write(MCP_CANCTRL, mode);
}