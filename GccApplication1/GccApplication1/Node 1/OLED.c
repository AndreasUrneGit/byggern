/*
 * OLED.c
 *
 * Created: 19.09.2023 11:27:27
 *  Author: andreurn
 */ 

#include "OLED.h"

void oled_write_command(uint8_t command){
	oled_cmd = command;
}

void oled_write_data(uint8_t data){
	oled_data = data;
}

void oled_init_program()
{
	oled_write_command(0xae); // display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63~com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //Set Memory Addressing Mode
	oled_write_command(0x02);
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	oled_write_command(0xaf); // display on
	
	oled_reset();
}

void oled_goto_line(uint8_t line){
	uint8_t address = 0xB0 + line;
	oled_write_command(address);
	
	glob_current_line = line;
}

void oled_screen_on(){
	oled_write_command(0xA5);
}
void oled_screen_off(){
	oled_write_command(0xA4);
}
void oled_goto_column(uint8_t column){
	oled_write_command(column & (0b1111));
	oled_write_command(0x10 + (column >> 4));
	
	glob_current_column = column;
}
void oled_clear_screen(){
	for(int line = 0; line < 8; line++){
		oled_clear_line(line);
	}
}

void oled_reset(){
	oled_clear_screen();
	oled_goto_line(0);
	oled_goto_column(0);

}

void oled_pos(uint8_t line, uint8_t column){
	oled_goto_line(line);
	oled_goto_column(column);
}

void oled_clear_line(uint8_t line){
	oled_goto_line(line);
	for(int col = 0; col < 128; col++){
		oled_write_data(0);
	}
}

void oled_putchar(const char ch, uint8_t font_size){
	switch (ch){
		case '\n':
			oled_increment_page_index();
			break;
		case '\r':
			oled_goto_column(0);
			break;
		case '\t':
			for (int i = 0; i < 4; i++){
				oled_putchar(' ', font_size);
			}
			break;
	
	default:
		if(glob_current_column + font_size > 127){
			oled_increment_page_index();
			oled_goto_column(0);
		}
		if(font_size == 4){
			for(uint8_t column = 0; column < font_size; column++){
				oled_write_data(pgm_read_byte(&(font4[ch - 32][column])));
			}
		}
		else if(font_size == 5){
			for(uint8_t column = 0; column < font_size; column++){
				oled_write_data(pgm_read_byte(&(font5[ch - 32][column])));
			}
		}
		else{
			for(uint8_t column = 0; column < font_size; column++){
				oled_write_data(pgm_read_byte(&(font8[ch - 32][column])));
			}
		}
		glob_current_column += font_size;
	}
}

void oled_print(const char* message, uint8_t font_size){

	size_t size = strlen(message);
	
	printf("\n\r%s", message);
	
	for(uint8_t index = 0; index < size; index++){
		oled_putchar(message[index], font_size);
	}
}

void oled_increment_page_index(){
	if(glob_current_line == MAX_LINE){
		oled_goto_line(0);
		return;
	}
	oled_goto_line(glob_current_line + 1);
}
