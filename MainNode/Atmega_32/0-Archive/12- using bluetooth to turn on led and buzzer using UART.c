 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 
/****************INCLUDES**************************/
#include "MCAL/UART/UART_interface.h"
#include "HAL/LED/led_interface.h"
/****************GLOBAL VARIABLES******************/
u8 bt = 0;
/****************PROTOTYPES************************/
/****************MAIN FUNCTION*********************/
int main(void){
	UART_Init(9600);
	LED_init(LED_RED_PORT, LED_RED_PIN);
	LED_init(LED_BLUE_PORT, LED_BLUE_PIN);
	LED_init(LED_GREEN_PORT, LED_GREEN_PIN);
	LED_init(LED_YELLOW_PORT, LED_YELLOW_PIN);
	DIO_void_SetPinDirection(PORT_C, PIN_6,DIO_DIRECTION_OUTPUT);
	while(1)
	{
		UART_Recieve(&bt);
		if('F' == bt){
			DIO_void_SetPinValue(PORT_C, PIN_6,LOGIC_HIGH);
		}
		else if('B' == bt){
			DIO_void_SetPinValue(PORT_C, PIN_6,LOGIC_LOW);
		}
		if('L' == bt){
			LED_turn_on(LED_RED_PORT, LED_RED_PIN);
			LED_turn_on(LED_BLUE_PORT, LED_BLUE_PIN);
			LED_turn_on(LED_GREEN_PORT, LED_GREEN_PIN);
			LED_turn_on(LED_YELLOW_PORT, LED_YELLOW_PIN);
		}
		else if('R' == bt){
			LED_turn_off(LED_RED_PORT, LED_RED_PIN);
			LED_turn_off(LED_BLUE_PORT, LED_BLUE_PIN);
			LED_turn_off(LED_GREEN_PORT, LED_GREEN_PIN);
			LED_turn_off(LED_YELLOW_PORT, LED_YELLOW_PIN);
		}	
	}
}
/**********HELPER FUNCTIONS************************/
