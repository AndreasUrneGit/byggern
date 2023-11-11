/*
 * adc.h
 *
 * Created: 07.11.2023 15:27:28
 *  Author: andreurn
 */ 


#ifndef ADC_H_
#define ADC_H_


#include <stdint.h>
#include "bit_macros.h"
#include "sam.h"

typedef struct {
	uint16_t current_val;
	uint16_t prev_val;
	} IR_sensor;

void adc_init();
uint16_t adc_read();

#endif /* ADC_H_ */