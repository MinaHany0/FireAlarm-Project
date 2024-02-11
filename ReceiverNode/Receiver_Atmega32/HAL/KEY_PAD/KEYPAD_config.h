/*
 * KEYPAD_config.h
 *
 * Created: 10/23/2023 11:26:46 PM
 *  Author: Mina
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#include "../../MCAL/std_types.h"

#define KP_R1_PORT	PORT_C
#define KP_R1_PIN	PIN_5
#define KP_R2_PORT	PORT_C
#define KP_R2_PIN	PIN_4
#define KP_R3_PORT	PORT_C
#define KP_R3_PIN	PIN_3
#define KP_R4_PORT	PORT_C
#define KP_R4_PIN	PIN_2

#define KP_C1_PORT	PORT_D
#define KP_C1_PIN	PIN_7
#define KP_C2_PORT	PORT_D
#define KP_C2_PIN	PIN_6
#define KP_C3_PORT	PORT_D
#define KP_C3_PIN	PIN_5
#define KP_C4_PORT	PORT_D
#define KP_C4_PIN	PIN_3

u8 KP_arr[4][4] = {
	{'7' , '8' , '8' , '/'},
	{'4' , '5' , '6' , '*'},
	{'1' , '2' , '3' , '-'},
	{'0' , '0' , '=' , '+'}
};


#endif /* KEYPAD_CONFIG_H_ */