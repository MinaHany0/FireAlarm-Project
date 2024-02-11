/*
 * btn_interface.h
 *
 * Created: 10/20/2023 8:41:12 PM
 *  Author: Mina
 */ 


#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_

/*********************************INCLUDES*************************************************/
#include "../../MCAL/DIO/dio_interface.h"
#include "btn_config.h"
/*********************************MACRO DECLARATIONS***************************************/
#define BUTTON_RELEASED (0u)
#define BUTTON_PRESSED	(1u)
/*********************************MACRO FUNCTIONS******************************************/
/*********************************DATA TYPE DEFINITIONS************************************/
typedef struct{
	u8 portID :3;
	u8 pinID  :3;
}btn_t;
/*********************************FUNCTION INTERFACE DECLARATION***************************/
void button_void_init(btn_t* _btn);
u8 button_u8_ReadVal(btn_t* _btn);




#endif /* BTN_INTERFACE_H_ */