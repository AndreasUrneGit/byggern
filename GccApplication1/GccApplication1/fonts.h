/*
 * fonts.h
 *
 * Created: 19.09.2023 11:34:56
 *  Author: andreurn
 */ 


#ifndef FONTS_H_
#define FONTS_H_
#include <avr/pgmspace.h>
#include <stdint.h>


// Font 8x8 - Large
const unsigned char font8[95][8];

// Font 5x7 - normal
const unsigned char font5[95][5];

// Font 4x6 - Small
const unsigned char font4[95][4];


#endif /* FONTS_H_ */