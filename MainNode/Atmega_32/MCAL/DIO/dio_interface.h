/*
 * dio.h
 *
 * Created: 10/20/2023 11:06:10 AM
 *  Author: Mina
 */ 


#ifndef DIO_H_
#define DIO_H_
/*********************************INCLUDES*************************************************/
#include "../bit_math.h"
#include "../std_types.h"
/*********************************MACRO DECLARATIONS***************************************/
#define PORTA		(*((volatile u8*) 0x3B))
#define PORTB		(*((volatile u8*) 0x38))
#define PORTC		(*((volatile u8*) 0x35))
#define PORTD		(*((volatile u8*) 0x32))

#define DDRA		*((volatile u8*) 0x3A)
#define DDRB		*((volatile u8*) 0x37)
#define DDRC		*((volatile u8*) 0x34)
#define DDRD		*((volatile u8*) 0x31)

#define PINA		*((volatile u8*) 0x39)
#define PINB		*((volatile u8*) 0x36)
#define PINC		*((volatile u8*) 0x33)
#define PIND		*((volatile u8*) 0x30)
/*********************************DATA TYPE DEFINITIONS************************************/
typedef enum{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
	}port_t;
	
typedef enum{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
}pin_t;

typedef enum{
	DIO_DIRECTION_INPUT,
	DIO_DIRECTION_OUTPUT,
}dio_direction_t;

typedef struct{
	port_t port;
	pin_t pin;
	dio_direction_t pin_direction;
	u8 logic :1 ;
}dio_cfg_t;
	


/*********************************MACRO FUNCTIONS******************************************/

/*********************************FUNCTION INTERFACE DECLARATION***************************/
void DIO_void_SetPortDirection( u8 portID, u8 portDir);
void DIO_void_SetPortValue	  ( u8 portID, u8 portVal);
void DIO_void_ReadPortValue	  ( u8 portID, u8* portVal);
void DIO_void_SetPinDirection ( u8 portID, u8 pinID, u8 pinDir);
void DIO_void_SetPinValue	  ( u8 portID, u8 pinID, u8 pinVal);
void DIO_void_togglePinValue  ( u8 portID, u8 pinID);
u8   DIO_void_GetBitValue(u8 PortID, u8 PinID);

#endif /* DIO_H_ */