/*
 * CFile1.c
 *
 * Created: 10/20/2023 11:05:36 AM
 *  Author: Mina
 */ 

#include "dio_interface.h"

void DIO_void_SetPortDirection( u8 portID, u8 portDir){
	switch(portID){
		case PORT_A:
		if(DIO_DIRECTION_OUTPUT == portDir){
			DDRA = 0xFF;
			}else if(DIO_DIRECTION_INPUT == portDir){
			DDRA = 0x00;
		}
		break;
		case PORT_B:
		if(DIO_DIRECTION_OUTPUT == portDir){
			DDRB = 0xFF;
			}else if(DIO_DIRECTION_INPUT == portDir){
			DDRB = 0x00;
		}
		break;
		case PORT_C:
		if(DIO_DIRECTION_OUTPUT == portDir){
			DDRC = 0xFF;
			}else if(DIO_DIRECTION_INPUT == portDir){
			DDRC = 0x00;
		}
		break;
		case PORT_D:
		if(DIO_DIRECTION_OUTPUT == portDir){
			DDRD = 0xFF;
			}else if(DIO_DIRECTION_INPUT == portDir){
			DDRD = 0x00;
		}
		break;
		default: break;
	}
}
void DIO_void_SetPortValue( u8 portID, u8 portVal){
	if(portID == PORT_A){
		PORTA = portVal;
	}
	else if(portID == PORT_B){
		PORTB = portVal;
	}
	else if(portID == PORT_C){
		PORTC = portVal;
	}
	else if(portID == PORT_D){
		PORTD = portVal;
	}	
}

void DIO_void_ReadPortValue( u8 portID, u8* portVal){
	if(portID == PORT_A){
		*portVal = PINA;
	}
	else if(portID == PORT_B){
		*portVal = PINB;
	}
	else if(portID == PORT_C){
		*portVal = PINC;
	}
	else if(portID == PORT_D){
		*portVal = PIND;
	}
}

void DIO_void_SetPinDirection( u8 portID, u8 pinID, u8 pinDir){
	switch(portID){
		case PORT_A: 
			if(DIO_DIRECTION_OUTPUT == pinDir){
				SET_BIT(DDRA, pinID);
			}
			else if(DIO_DIRECTION_INPUT == pinDir){
				CLEAR_BIT(DDRA, pinID);
			}
			break;
			
		case PORT_B:
			if(DIO_DIRECTION_OUTPUT == pinDir){
				SET_BIT(DDRB, pinID);
			}
			else if(DIO_DIRECTION_INPUT == pinDir){
				CLEAR_BIT(DDRB, pinID);
			}
			break;
		case PORT_C:
			if(DIO_DIRECTION_OUTPUT == pinDir){
				SET_BIT(DDRC, pinID);
			}
			else if(DIO_DIRECTION_INPUT == pinDir){
				CLEAR_BIT(DDRC, pinID);
			}
			break;
		case PORT_D:
			if(DIO_DIRECTION_OUTPUT == pinDir){
				SET_BIT(DDRD, pinID);
			}
			else if(DIO_DIRECTION_INPUT == pinDir){
				CLEAR_BIT(DDRD, pinID);
			}
			break;
		default: break;
	}
}

void DIO_void_SetPinValue	( u8 portID, u8 pinID, u8 pinVal){
	switch(portID){
		case PORT_A:
			if(pinVal == LOGIC_HIGH){
				SET_BIT(PORTA, pinID);
			}
			else if(pinVal == LOGIC_LOW){
				CLEAR_BIT(PORTA, pinID);
			}
			break;
		case PORT_B:
			if(pinVal == LOGIC_HIGH){
				SET_BIT(PORTB, pinID);
			}
			else if(pinVal == LOGIC_LOW){
				CLEAR_BIT(PORTB, pinID);
			}
			break;
		case PORT_C:
			if(pinVal == LOGIC_HIGH){
				SET_BIT(PORTC, pinID);
			}
			else if(pinVal == LOGIC_LOW){
				CLEAR_BIT(PORTC, pinID);
			}
			break;
		case PORT_D:
			if(pinVal == LOGIC_HIGH){
				SET_BIT(PORTD, pinID);
			}
			else if(pinVal == LOGIC_LOW){
				CLEAR_BIT(PORTD, pinID);
			}
			break;
		default: 
			break;
	}
}
void DIO_void_togglePinValue	( u8 portID, u8 pinID){
	switch(portID){
		case PORT_A: TOGGLE_BIT(PORTA, pinID); break;
		case PORT_B: TOGGLE_BIT(PORTB, pinID); break;
		case PORT_C: TOGGLE_BIT(PORTC, pinID); break;
		case PORT_D: TOGGLE_BIT(PORTD, pinID); break;
		default: break;
	}
}
u8 DIO_void_GetBitValue(u8 PortID, u8 PinID){
	u8 value = 0;
	switch(PortID){
		case PORT_A: value = GET_BIT(PINA, PinID); break;
		case PORT_B: value = GET_BIT(PINB, PinID); break;
		case PORT_C: value = GET_BIT(PINC, PinID); break;
		case PORT_D: value = GET_BIT(PIND, PinID); break;
		default: break;
	}
	return value;
}
