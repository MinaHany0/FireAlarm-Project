/*
 * led_program.c
 *
 * Created: 10/20/2023 1:43:35 PM
 *  Author: Mina
 */ 

#include "led_interface.h"

void LED_init	 (u8 portID, u8 pinID){
	DIO_void_SetPinDirection (portID, pinID, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue	  (portID,pinID, LOGIC_LOW);
}
void LED_turn_on (u8 portID, u8 pinID){
	DIO_void_SetPinValue	  (portID,pinID, LOGIC_HIGH);
}
void LED_turn_off(u8 portID, u8 pinID){
	DIO_void_SetPinValue	  (portID,pinID, LOGIC_LOW);
}
void LED_toggle  (u8 portID, u8 pinID){
	DIO_void_togglePinValue  (portID, pinID);
}
void BUZZER_init	 (void){
	DIO_void_SetPinDirection (BUZZER_PORT, BUZZER_PIN, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue	  (BUZZER_PORT,BUZZER_PIN, LOGIC_LOW);
}

void BUZZER_turn_on (void){
	DIO_void_SetPinValue	  (BUZZER_PORT,BUZZER_PIN, LOGIC_HIGH);
}
void BUZZER_turn_off (void){
	DIO_void_SetPinValue	  (BUZZER_PORT,BUZZER_PIN, LOGIC_LOW);
}