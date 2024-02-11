/*
 * led_interface.h
 *
 * Created: 10/20/2023 1:44:20 PM
 *  Author: Mina
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/*********************************INCLUDES*************************************************/
#include "../../MCAL/DIO/dio_interface.h"
#include "led_config.h"
/*********************************MACRO DECLARATIONS***************************************/
/*********************************MACRO FUNCTIONS******************************************/
/*********************************DATA TYPE DEFINITIONS************************************/
/*********************************FUNCTION INTERFACE DECLARATION***************************/

void LED_init	 (u8 portID, u8 pinID);
void LED_turn_on (u8 portID, u8 pinID);
void LED_turn_off(u8 portID, u8 pinID);
void LED_toggle  (u8 portID, u8 pinID);
void BUZZER_init		(void);
void BUZZER_turn_on		(void);
void BUZZER_turn_off	(void);

#endif /* LED_INTERFACE_H_ */