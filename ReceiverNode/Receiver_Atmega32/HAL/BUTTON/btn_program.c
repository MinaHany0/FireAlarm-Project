/*
 * btn_program.c
 *
 * Created: 10/20/2023 3:33:36 PM
 *  Author: Mina
 */ 
/*********************************INCLUDES*************************************************/
#include "btn_interface.h"
/*********************************FUNCTION INTERFACE **************************************/
void button_void_init(btn_t* _btn){
	DIO_void_SetPinDirection(_btn->portID, _btn->pinID, DIO_DIRECTION_INPUT);
};
u8 button_u8_ReadVal(btn_t* _btn){
	u8 button_val_1 = BUTTON_RELEASED;
	u8 button_val_2 = BUTTON_RELEASED;
	u8 button_val_3 = BUTTON_RELEASED;
	button_val_1 = DIO_void_GetBitValue(_btn->portID,_btn->pinID);
	if(BUTTON_PRESSED == button_val_1){
		_delay_ms(100);
		button_val_2 = DIO_void_GetBitValue(_btn->portID,_btn->pinID);
		if(BUTTON_PRESSED == button_val_2){
			button_val_3 = BUTTON_PRESSED;
		}else{
			button_val_3 = BUTTON_RELEASED;
		}
	}
	return button_val_3;
};