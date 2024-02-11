/*
 * ext_int_program.c
 *
 * Created: 10/22/2023 2:22:41 PM
 *  Author: Mina
 */ 
#include "ext_int_config.h"
#include "ext_int_interface.h"
#include "ext_int_private.h"


static void (*EXT_INT0_InterruptHandler)(void) = (void*)0;
static void (*EXT_INT1_InterruptHandler)(void) = (void*)0;
static void (*EXT_INT2_InterruptHandler)(void) = (void*)0;

static void ext_callback( void (*ptr)(void), u8 ext_int_num );

void ext_init	 ( u8 ext_int_num, void (*ptr)(void), u8 ext_int_sense){
	
	ext_callback( ptr, ext_int_num );
	
	switch(ext_int_num){
		case EXT_INT_0_INDEX: 
		DIO_void_SetPinDirection (PORT_D, PIN_2, DIO_DIRECTION_INPUT);
		DIO_void_SetPinValue	(PORT_D, PIN_2, LOGIC_HIGH);
		SET_BIT(GICR,GICR_INT0_PIN_MASK); 
		
		switch(ext_int_sense){
			case EXT_INT_ON_LOW_LEVEL: 
			CLEAR_BIT(MCUCR,ISC0_0_PIN_MASK);
			CLEAR_BIT(MCUCR,ISC0_1_PIN_MASK);
			break;
			
			case EXT_INT_ON_ANY_CHANGE: 
			SET_BIT(MCUCR,ISC0_0_PIN_MASK);
			CLEAR_BIT(MCUCR,ISC0_1_PIN_MASK);
			break;
			
			case EXT_INT_ON_FALLING_EDGE:
			CLEAR_BIT(MCUCR,ISC0_0_PIN_MASK);
			SET_BIT(MCUCR,ISC0_1_PIN_MASK);
			break;
			
			case EXT_INT_ON_RISING_EDGE:
			SET_BIT(MCUCR,ISC0_0_PIN_MASK);
			SET_BIT(MCUCR,ISC0_1_PIN_MASK);
			break;
			
			default: break;
		}
		break;
		
		case EXT_INT_1_INDEX: 
		DIO_void_SetPinDirection (PORT_D, PIN_3, DIO_DIRECTION_INPUT);
		DIO_void_SetPinValue	(PORT_D, PIN_3, LOGIC_HIGH);
		SET_BIT(GICR,GICR_INT1_PIN_MASK); 
		switch(ext_int_sense){
			case EXT_INT_ON_LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC1_0_PIN_MASK);
			CLEAR_BIT(MCUCR,ISC1_1_PIN_MASK);
			break;
			
			case EXT_INT_ON_ANY_CHANGE:
			SET_BIT  (MCUCR,ISC1_0_PIN_MASK);
			CLEAR_BIT(MCUCR,ISC1_1_PIN_MASK);
			break;
			
			case EXT_INT_ON_FALLING_EDGE:
			CLEAR_BIT(MCUCR,ISC1_0_PIN_MASK);
			SET_BIT	 (MCUCR,ISC1_1_PIN_MASK);
			break;
			
			case EXT_INT_ON_RISING_EDGE:
			SET_BIT(MCUCR,ISC1_0_PIN_MASK);
			SET_BIT(MCUCR,ISC1_1_PIN_MASK);
			break;
			
			default: break;
		}
		break;
		
		case EXT_INT_2_INDEX: 
		
		SET_BIT(GICR,GICR_INT2_PIN_MASK);
		DIO_void_SetPinDirection (PORT_B, PIN_2, DIO_DIRECTION_INPUT); 
		DIO_void_SetPinValue	(PORT_B, PIN_2, LOGIC_HIGH);
		switch(ext_int_sense){			
			case EXT_INT_ON_FALLING_EDGE:
			CLEAR_BIT(MCUCSR,ISC2_PIN_MASK);
			break;
			
			case EXT_INT_ON_RISING_EDGE:
			SET_BIT(MCUCSR,ISC2_PIN_MASK);
			break;
			
			default: break;
		}
		break;
		
		default:			  break;
	}
}
static void ext_callback( void (*ptr)(void), u8 ext_int_num ){
	switch(ext_int_num){
		case EXT_INT_0_INDEX: 
		EXT_INT0_InterruptHandler = ptr;
		break;
		case EXT_INT_1_INDEX: 
		EXT_INT1_InterruptHandler = ptr;
		break;
		case EXT_INT_2_INDEX: 
		EXT_INT2_InterruptHandler = ptr;
		break;
	}
}

void __vector_1() __attribute__((signal));
void __vector_1(){
	GIE_Disable();
	
	if(EXT_INT0_InterruptHandler){
		EXT_INT0_InterruptHandler();
	}
	
	GIE_Enable();
}
void __vector_2() __attribute__((signal));
void __vector_2(){
	GIE_Disable();
	
	if(EXT_INT1_InterruptHandler){
		EXT_INT1_InterruptHandler();
	}
	
	GIE_Enable();
}
void __vector_3() __attribute__((signal));
void __vector_3(){
	GIE_Disable();
	
	if(EXT_INT2_InterruptHandler){
		EXT_INT2_InterruptHandler();
	}
	
	GIE_Enable();
}
