/*
 * gie_interface.h
 *
 * Created: 10/22/2023 2:05:12 PM
 *  Author: Mina
 */ 


#ifndef GIE_INTERFACE_H_
#define GIE_INTERFACE_H_

#include "../DIO/dio_interface.h"

void GIE_Enable(void);
void GIE_Disable(void);
void GIE_GetValue(u8* GIE_Value);
void GIE_SetValue(u8 GIE_Value);



#endif /* GIE_INTERFACE_H_ */