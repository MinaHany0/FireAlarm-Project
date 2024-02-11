/*
 * UART_program.c
 *
 * Created: 10/30/2023 11:48:50 AM
 *  Author: Mina
 */ 

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

static void UART_UBBR_Equation (u16 baudrate, u16* ptr);
static void (*RX_InterruptHandler)(void) = NULL;
static void (*TX_InterruptHandler)(void) = NULL;

	
void UART_Init(u16 baudrate){
	u16 UBRR_result = 0;
	/*configure equation based on Synch mode and speed*/
	UART_UBBR_Equation (baudrate, &UBRR_result);
	UBRRL = (u8)UBRR_result;
	UBRRH = (u8)(UBRR_result >> 8);
	/*enable receiver & Transmitter*/
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	/*	enable interrupt according to config file	*/
	#if UART_INTERRUPT_ENABLE == INT_ENABLE
	UCSRB |= (1 << RXCIE) | (1 << TXCIE);
	#endif
	
	UCSRC = 0x86;
}

void UART_Recieve(volatile u8* value){
	/*check if there are unread data in receiver buffer*/
	while(0 == GET_BIT(UCSRA,RXC));
	/*put value in pointer*/
	*value = UDR;
	/*clear flag*/
	SET_BIT(UCSRA,RXC);
}

void UART_Transmit(u8 value){
	/*check if transmit buffer is ready */
	while(0 == GET_BIT(UCSRA,UDRE));
	/*put value in pointer*/
	UDR = value;
	/*clear flag*/
	SET_BIT(UCSRA,UDRE);
}

void UART_TX_Callback( void(*ptr)(void) ){
	TX_InterruptHandler = ptr;
}
void UART_RX_Callback( void(*ptr)(void) ){
	RX_InterruptHandler = ptr;
}

static void UART_UBBR_Equation (u16 baudrate, u16* ptr){
	if(0 == GET_BIT(UCSRA, U2X) || 0 == GET_BIT(UCSRC, UMSEL)){
		*ptr = ((u64)(F_CPU) / (u64)(16ul * (u64)baudrate)) -1;
	}
	else{/*NOTHING*/}
	/******configure rest of equations*****************************/
}

/*	RX COMPLETE INTERRUPT VECTOR	*/
void __vector_13() __attribute__((signal));
void __vector_13(){
	GIE_Disable();
	if(RX_InterruptHandler)
	{
		RX_InterruptHandler();
	}
	GIE_Enable();
}

/*	TX COMPLETE INTERRUPT VECTOR	*/
void __vector_15() __attribute__((signal));
void __vector_15(){
	GIE_Disable();
	if(TX_InterruptHandler)
	{
		TX_InterruptHandler();
	}
	GIE_Enable();
}