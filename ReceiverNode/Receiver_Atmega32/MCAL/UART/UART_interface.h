/*
 * UART_interface.h
 *
 * Created: 10/30/2023 11:49:07 AM
 *  Author: Mina
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../std_types.h"
#include "../bit_math.h"
#include "../DIO/dio_interface.h"
#include "../GIE/gie_interface.h"

void UART_Init(u16 baudrate);
void UART_Recieve(volatile u8* value);
void UART_Transmit(u8 value);
void UART_TX_Callback( void(*ptr)(void) );
void UART_RX_Callback( void(*ptr)(void) );

#endif /* UART_INTERFACE_H_ */