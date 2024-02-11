 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 
/****************INCLUDES**************************/
#include "MCAL/DIO/dio_interface.h"
#include "MCAL/TIMER0/timer0_interface.h"
#include "HAL/LED/led_interface.h"
/****************GLOBAL VARIABLES******************/
volatile u8 OC0_Flag = 0;
/****************PROTOTYPES************************/
void TIMER0_InterruptFunction(void);
/****************MAIN FUNCTION*********************/
int main(void){
	DIO_void_SetPinDirection(PORT_B, PIN_3, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue(PORT_B, PIN_3, LOGIC_HIGH);
	DIO_void_SetPinDirection(PORT_C, PIN_6, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue(PORT_C, PIN_6, LOGIC_LOW);
	LED_init(LED_RED_PORT,LED_RED_PIN);
	TMR0_Callback(TIMER0_InterruptFunction);
	TMR0_Enable_Interrupt();
	GIE_Enable();
	TMR0_Init();
	
	while(1)
	{
		
	}
}

/**********HELPER FUNCTIONS************************/
void TIMER0_InterruptFunction(void){
	if(OC0_Flag == 0){
		TMR0_Set_OCR0_Value(233);
		OC0_Flag = 1;
	}
	else if(OC0_Flag == 1){
		TMR0_Set_OCR0_Value(78);
		OC0_Flag = 0;
	}
	//DIO_void_togglePinValue(PORT_B, PIN_3);
	LED_toggle(LED_RED_PORT,LED_RED_PIN);
	DIO_void_togglePinValue(PORT_C, PIN_6);
}