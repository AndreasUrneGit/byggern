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

void spi_init(void);
void spi_write(uint8_t data);
uint8_t spi_read(void);


#endif /* SPI_H_ */