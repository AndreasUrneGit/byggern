/*
 * fsm.h
 *
 * Created: 12.11.2023 12:24:17
 *  Author: andreurn
 */ 


#ifndef FSM_H_
#define FSM_H_

#include "motorbox_interface.h"
#include "PID.h"

extern uint8_t playing;

void fsm_playing();
void fsm_waiting();



#endif /* FSM_H_ */