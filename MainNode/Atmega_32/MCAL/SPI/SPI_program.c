/*
 * SPI_program.c
 *
 * Created: 10/31/2023 3:06:04 PM
 *  Author: Mina
 */ 
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"

static void (*SPI_InterruptHandler)(void) = NULL;

void SPI_Master_Init(void){
		/*leave interrupt disabled as polling will be used*/
		/*leave clock polarity and phase as default*/
		/*use normal speed as default so no change*/
		/*set MOSI ,SS and SCK as output pins , MISO is overridden by HW*/
		DIO_void_SetPinDirection(SPI_PORT,MOSI_PIN,DIO_DIRECTION_OUTPUT);
		DIO_void_SetPinDirection(SPI_PORT,SCK_PIN,DIO_DIRECTION_OUTPUT);
		//DIO_void_SetPinDirection(SPI_PORT,SS_PIN,DIO_DIRECTION_INPUT);
		/* remove previous settings in SPCR */
		SPCRbits->SPCR = 0x00;
		/*choose as master*/
		SPCRbits->MSTR = SPI_MSTR_ENABLE;
		/*set to send least significant first*/
		SPCRbits->DORD = 1;
		/*prescaler is set to div by 16*/
		SPCRbits->SPR0 = 1;
		/*enable PI Module*/
		SPCRbits->SPE = SPI_ENABLE;
}

void SPI_Slave_Init(void){
	/*leave interrupt disabled as polling will be used*/
	/*leave clock polarity and phase as default*/
	/*use normal speed as default so no change*/
	/* set MISO as o/p all others are overridden by HW */
	DIO_void_SetPinDirection(SPI_PORT,MISO_PIN,DIO_DIRECTION_OUTPUT);
	/* remove previous settings in SPCR */
	SPCRbits->SPCR = 0x00;
	/*set to send least significant first*/
	SPCRbits->DORD = 1;
	/*prescaler is set to div by 16*/
	SPCRbits->SPR0 = 1;
	SPCRbits->SPE = SPI_ENABLE;
	
	SPCRbits->SPIE = 0;
	#if SPI_INTERRUPT  == SPI_INTERRUPT_ENABLE
	SPCRbits->SPIE = 1;
	#endif
}

void SPI_Transmit(u8 value){
	*SPDR = value;
	while( 0 == (SPSRbits->SPIF) )
	;
}

void SPI_Receive(u8* value){
	while( 0 == (SPSRbits->SPIF) )
	;
	//THE SET HAS NO USE AS SETTING IS NOT DONE BY WRITING ONE
	//CLEARING FLAG IS DONE BY READING STATUS REGISTER AND THEN ACCESSING SPDR REG
	*value = *SPDR;
}

void SPI_Callback(void (*ptr)(void)){
	SPI_InterruptHandler = ptr;
}


/*	SPI COMPLETE INTERRUPT VECTOR	*/
void __vector_12() __attribute__((signal));
void __vector_12(){
	GIE_Disable();
	if(SPI_InterruptHandler)
	{
		SPI_InterruptHandler();
	}
	GIE_Enable();
}