/*
 * timer0_interface.h
 *
 * Created: 10/27/2023 10:38:33 AM
 *  Author: Mina
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_
/****************INCLUDES**************************/
#include "../GIE/gie_interface.h"
/****************FUNCTION PROTOTYPES**************************/
void TMR0_Init(void);
void TMR0_Disable(void);
void TMR0_Enable_Interrupt(void);
void TMR0_Clear_Flag_Disabled_Interrupt(void);
void TMR0_Callback(void(*ptr)(void));
void TMR0_delay_ms(u64 value);
void TMR0_Set_OCR0_Value(u8 value);
void TMR0_Set_TCNT0_Value(u8 value);

#endif /* TIMER0_INTERFACE_H_ */