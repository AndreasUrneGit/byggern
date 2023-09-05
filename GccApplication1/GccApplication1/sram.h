/*
 * IncFile1.h
 *
 * Created: 05.09.2023 10:57:17
 *  Author: andreurn
 */ 


#ifndef SRAM_H
#define SRAM_H

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "bit_macros.h"

void SRAM_test(void);

void SRAM_latch_test(void);

void SRAM_init();

#endif