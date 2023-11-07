/*
 * dac.h
 *
 * Created: 07.11.2023 15:34:37
 *  Author: andreurn
 */ 


#ifndef DAC_H_
#define DAC_H_


#include <stdint.h>
#include "bit_macros.h"
#include "sam.h"

void dac_init();
void dac_write(uint16_t digital_value);


#endif /* DAC_H_ */