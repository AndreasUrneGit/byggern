/*
 * game.c
 *
 * Created: 12.11.2023 12:10:20
 *  Author: andreurn
 */ 




#include "game.h"
#define CANINTF_MASK 1

CAN_msg send_message = {1, 6, 0b000000};
extern Game game;
extern GAMEBOARD_VALUES Gameboard_values;
//static CAN_msg recieve_message;


void game_playing( void ){
	//initialiser arduiono og spill
	
	send_message.data[0] = 0;
	send_message.data[1] = 0;
	send_message.data[2] = 0;
	send_message.data[3] = 0;
	send_message.data[4] = 1;
	send_message.data[0] = 0;
	CAN_transmit(&send_message);
	
	game.goals = 0;
	
	oled_reset();
	oled_print("Goals: ", 8);
	char buff[1];
	char* result = itoa(game.goals, buff, 10);
	oled_print(result, 8);
	
	
		
	while (game.playing){
		//adc sample -> send til node 2
		ADC_sample(&Gameboard_values);
		
		// bygge CAN-melding
		send_message.data[0] = Gameboard_values.joystick_x;
		send_message.data[1] = Gameboard_values.button_left;
		send_message.data[2] = Gameboard_values.slider_right;
		send_message.data[3] = Gameboard_values.button_right;
		
		// sende melding
		CAN_transmit(&send_message);
		
		// check for goal if new CAN message from node 2
		if (mcp_2515_read(MCP_CANINTF) & CANINTF_MASK){
			printf("We have recieved a goal!! \n\r");
			CAN_receive();
			game.goals++;
			
			oled_reset();
			oled_print("Goals: ", 8);
			char buff[1];
			char* result = itoa(game.goals, buff, 10);
			oled_print(result, 8);

		}

		
		// should we exit this state?
		if (game.goals > game.over || (Gameboard_values.button_left > 250)){
			game.playing = 0;
		}
		_delay_ms(20);
	}
	
	//deaktivere arduino og spill
	send_message.data[4] = 0;
	CAN_transmit(&send_message);
}



/*
		if(joystick_handle()){
			menu_navigate(joystick_position, glob_current_menu);
			menu_print();
		}
		*/

