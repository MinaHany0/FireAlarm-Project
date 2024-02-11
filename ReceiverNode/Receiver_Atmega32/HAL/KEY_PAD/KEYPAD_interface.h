/*
 * KEYPAD_interface.h
 *
 * Created: 10/23/2023 11:26:32 PM
 *  Author: Mina
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include "../../MCAL/DIO/dio_interface.h"

void KEYPAD_Init(void);
void KEYPAD_Read(u8* key);

#endif /* KEYPAD_INTERFACE_H_ */