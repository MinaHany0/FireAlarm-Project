 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 
/****************INCLUDES**************************/
#include "MCAL/WDT/WDT_interface.h"
#include "HAL/LED/led_interface.h"

/****************GLOBAL VARIABLES******************/
volatile u8 OC0_Flag = 0;
/****************PROTOTYPES************************/
void red_led(void);
void blue_led(void);
void yellow_led(void);
/****************MAIN FUNCTION*********************/
int main(void){
	
	LED_init(LED_RED_PORT,LED_RED_PIN);
	LED_init(LED_BLUE_PORT,LED_BLUE_PIN);
	LED_init(LED_YELLOW_PORT,LED_YELLOW_PIN);
	while(1)
	{
		
		red_led();
		blue_led();
		yellow_led();
		
	}
}

/**********HELPER FUNCTIONS************************/
void red_led(void){
	WDT_Enable(time_2100_msec);
	LED_turn_on(LED_RED_PORT,LED_RED_PIN);
	_delay_ms(850);
	LED_turn_off(LED_RED_PORT,LED_RED_PIN);
	_delay_ms(850);
	WDT_Disable();
}
void blue_led(void){
	WDT_Enable(time_2100_msec);
	LED_turn_on(LED_BLUE_PORT,LED_BLUE_PIN);
	_delay_ms(850);
	LED_turn_off(LED_BLUE_PORT,LED_BLUE_PIN); 
	_delay_ms(850);
	WDT_Disable();
 }
void yellow_led(void){
	WDT_Enable(time_2100_msec);
	LED_turn_on(LED_YELLOW_PORT,LED_YELLOW_PIN);
	_delay_ms(850);
	LED_turn_off(LED_YELLOW_PORT,LED_YELLOW_PIN);
	_delay_ms(850);
	WDT_Disable();
}