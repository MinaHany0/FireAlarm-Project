/*
 * ext_int_interface.h
 *
 * Created: 10/22/2023 2:22:22 PM
 *  Author: Mina
 */ 
#include "../std_types.h"
#include "../bit_math.h"
#include "../DIO/dio_interface.h"
#include "../GIE/gie_interface.h"

#ifndef EXT_INT_INTERFACE_H_
#define EXT_INT_INTERFACE_H_

#define EXT_INT_ON_LOW_LEVEL	0
#define EXT_INT_ON_ANY_CHANGE	1
#define EXT_INT_ON_FALLING_EDGE	2	
#define EXT_INT_ON_RISING_EDGE	3

#define EXT_INT_0_INDEX			0
#define EXT_INT_1_INDEX			1
#define EXT_INT_2_INDEX			2


#define INT0_PORT				PORT_D
#define INT0_PIN				PIN_2
		
#define INT1_PORT				PORT_D
#define INT1_PIN				PIN_3

#define INT2_PORT				PORT_B
#define INT2_PIN				PIN_2
	

void ext_init	 ( u8 ext_int_num, void (*ptr)(void), u8 ext_int_sense);

#endif /* EXT_INT_INTERFACE_H_ */