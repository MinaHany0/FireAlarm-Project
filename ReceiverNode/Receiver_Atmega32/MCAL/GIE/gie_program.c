/*
 * gie_program.c
 *
 * Created: 10/22/2023 2:07:39 PM
 *  Author: Mina
 */ 


#include "gie_interface.h"
#include "gie_config.h"
#include "gie_private.h"

void GIE_Enable(void){
	SET_BIT(SREG, GIE_PIN_MASK);
}
void GIE_Disable(void){
	CLEAR_BIT(SREG, GIE_PIN_MASK);
}
void GIE_GetValue(u8* GIE_Value){
	*GIE_Value = GET_BIT(SREG, GIE_PIN_MASK);
}
void GIE_SetValue(u8 GIE_Value){
	if(GIE_Value == 1){
		GIE_Enable();
	}
	else if(GIE_Value == 0){
		GIE_Disable();
	}
}
