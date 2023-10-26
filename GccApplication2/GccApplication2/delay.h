/*
 * delay.h
 *
 * Created: 26.10.2023 14:17:43
 *  Author: oystebw
 */ 


#ifndef DELAY_H_
#define DELAY_H_

#define CPU_FREQ 84000000

void delay_ms(int ms){
	for(int x = 0; x < ms * CPU_FREQ / 10000; x++){
		asm("nop");
	}
}

#endif /* DELAY_H_ */