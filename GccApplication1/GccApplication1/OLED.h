/*
 * OLED.h
 *
 * Created: 19.09.2023 11:27:45
 *  Author: andreurn
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdlib.h>
#include <stdint.h>

#define oled_cmd  (*(volatile char*) 0x1000)
#define oled_data (*(volatile char*) 0x1200)

extern const uint8_t font8[95][8];

void oled_init_program(void);
void oled_write_command(uint8_t command);
void oled_write_data(uint8_t data);
void oled_reset();
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_pos(uint8_t line, uint8_t column);
void oled_clear_line(uint8_t line);
// ikke implementerte funksjoner som burde skrives ut:
void oled_home();
void oled_putchar(char ch);


void oled_screen_on();
void oled_screen_off();
void oled_clear_screen();



#endif /* OLED_H_ */