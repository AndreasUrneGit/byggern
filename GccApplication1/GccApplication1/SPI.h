/*
 * SPI.h
 *
 * Created: 10.10.2023 08:48:54
 *  Author: andreurn
 */ 


#ifndef SPI_H_
#define SPI_H_
#include <stdint.h>
#include <avr/io.h>
#include "bit_macros.h"

void SPI_init(void);
void SPI_MasterTransmit(char data);
char SPI_Read(void);


#endif /* SPI_H_ */