/*
 * KEYPAD_program.c
 *
 * Created: 10/23/2023 11:26:19 PM
 *  Author: Mina
 */ 

#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"




/* key pad thinking
	first configure rows as output low volt 0
	second configure columns as input so we can detect when they get 0 v instead of pullup 5 V
	
	configure an array for keyad to know which button was pressed
	
	loop between rows turning low one after another
	detect the low volt on column and decide which key from keypad

*/
void KEYPAD_Init(void){
	/*set row pins as low high "default mode" */
	DIO_void_SetPinDirection(KP_R1_PORT,KP_R1_PIN,DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue	(KP_R1_PORT,KP_R1_PIN,LOGIC_HIGH);
	DIO_void_SetPinDirection(KP_R2_PORT,KP_R2_PIN,DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue	(KP_R2_PORT,KP_R2_PIN,LOGIC_HIGH);
	DIO_void_SetPinDirection(KP_R3_PORT,KP_R3_PIN,DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue	(KP_R3_PORT,KP_R3_PIN,LOGIC_HIGH);
	DIO_void_SetPinDirection(KP_R4_PORT,KP_R4_PIN,DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue	(KP_R4_PORT,KP_R4_PIN,LOGIC_HIGH);
	/*set column pins as input pins*/
	DIO_void_SetPinDirection(KP_C1_PORT,KP_C1_PIN,DIO_DIRECTION_INPUT);
	DIO_void_SetPinDirection(KP_C2_PORT,KP_C2_PIN,DIO_DIRECTION_INPUT);
	DIO_void_SetPinDirection(KP_C3_PORT,KP_C3_PIN,DIO_DIRECTION_INPUT);
	DIO_void_SetPinDirection(KP_C4_PORT,KP_C4_PIN,DIO_DIRECTION_INPUT);
	
}

void KEYPAD_Read(u8* key){
	DIO_void_SetPinValue	(KP_R1_PORT,KP_R1_PIN,LOGIC_HIGH);
	DIO_void_SetPinValue	(KP_R2_PORT,KP_R2_PIN,LOGIC_HIGH);
	DIO_void_SetPinValue	(KP_R3_PORT,KP_R3_PIN,LOGIC_HIGH);
	DIO_void_SetPinValue	(KP_R4_PORT,KP_R4_PIN,LOGIC_HIGH);
	
	DIO_void_SetPinValue	(KP_R1_PORT,KP_R1_PIN,LOGIC_LOW);
	if( LOGIC_LOW == GET_BIT(KP_C1_PORT,KP_C1_PIN) ){
		*key = KP_arr[0][0];
		return;
	}
	else if( LOGIC_LOW == GET_BIT(KP_C2_PORT,KP_C2_PIN) ){
		*key = KP_arr[0][1];
		return;
	}
	else if( LOGIC_LOW == GET_BIT(KP_C3_PORT,KP_C3_PIN) ){
		*key = KP_arr[0][2];
		return;
	}
	else if( LOGIC_LOW == GET_BIT(KP_C4_PORT,KP_C4_PIN) ){
		*key = KP_arr[0][3];
		return;
	}
	DIO_void_SetPinValue	(KP_R1_PORT,KP_R1_PIN,LOGIC_HIGH);
	/****************************************************************/
	DIO_void_SetPinValue	(KP_R2_PORT,KP_R2_PIN,LOGIC_LOW);
	if( LOGIC_LOW == GET_BIT(KP_C1_PORT,KP_C1_PIN) ){
		*key = KP_arr[1][0];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C2_PORT,KP_C2_PIN) ){
		*key = KP_arr[1][1];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C3_PORT,KP_C3_PIN) ){
		*key = KP_arr[1][2];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C4_PORT,KP_C4_PIN) ){
		*key = KP_arr[1][3];
		return;
	}
	DIO_void_SetPinValue	(KP_R2_PORT,KP_R2_PIN,LOGIC_HIGH);
	/****************************************************************/
	DIO_void_SetPinValue	(KP_R3_PORT,KP_R3_PIN,LOGIC_LOW);
	if( LOGIC_LOW == GET_BIT(KP_C1_PORT,KP_C1_PIN) ){
		*key = KP_arr[2][0];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C2_PORT,KP_C2_PIN) ){
		*key = KP_arr[2][1];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C3_PORT,KP_C3_PIN) ){
		*key = KP_arr[2][2];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C4_PORT,KP_C4_PIN) ){
		*key = KP_arr[2][3];
		return;
	}
	DIO_void_SetPinValue	(KP_R3_PORT,KP_R3_PIN,LOGIC_HIGH);
	/****************************************************************/
	DIO_void_SetPinValue	(KP_R4_PORT,KP_R4_PIN,LOGIC_LOW);
	if( LOGIC_LOW == GET_BIT(KP_C1_PORT,KP_C1_PIN) ){
		*key = KP_arr[3][0];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C2_PORT,KP_C2_PIN) ){
		*key = KP_arr[3][1];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C3_PORT,KP_C3_PIN) ){
		*key = KP_arr[3][2];
		return;
	}
	if( LOGIC_LOW == GET_BIT(KP_C4_PORT,KP_C4_PIN) ){
		*key = KP_arr[3][3];
		return;
	}
	DIO_void_SetPinValue	(KP_R4_PORT,KP_R4_PIN,LOGIC_HIGH);
	
}