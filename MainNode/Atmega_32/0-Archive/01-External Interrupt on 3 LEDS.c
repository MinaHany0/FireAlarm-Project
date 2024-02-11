 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 



#include "MCAL/DIO/dio_interface.h"
#include "HAL/LED/led_interface.h"
//#include "HAL/BUTTON/btn_interface.h"
#include "HAL/SEV_SEG/sev_seg_interface.h"
//#include "HAL/LCD/lcd_interface.h"
#include "MCAL/GIE/gie_interface.h"
#include "MCAL/EXT_INT/ext_int_interface.h"



void EXT0_interruptHandler(void){
	_delay_ms(500);
	LED_toggle (LED_YELLOW_PORT, LED_YELLOW_PIN);
}
void EXT1_interruptHandler(void){
	_delay_ms(500);
	LED_toggle (LED_BLUE_PORT, LED_BLUE_PIN);
}
void EXT2_interruptHandler(void){
	_delay_ms(500);
	LED_toggle (LED_RED_PORT, LED_RED_PIN);
}

int main(void)
{
	LED_init	(LED_YELLOW_PORT, LED_YELLOW_PIN);
	LED_init	(LED_BLUE_PORT, LED_BLUE_PIN);
	LED_init	(LED_RED_PORT, LED_RED_PIN);
	seg_7_void_init();
	
	
	LED_turn_on	(LED_YELLOW_PORT, LED_YELLOW_PIN);
	LED_turn_on	(LED_BLUE_PORT, LED_BLUE_PIN);
	LED_turn_on	(LED_RED_PORT, LED_RED_PIN);
	
	
	ext_callback( EXT0_interruptHandler, EXT_INT_0_INDEX );
	ext_init	 ( EXT_INT_0_INDEX, EXT_INT_ON_FALLING_EDGE);
	
	ext_callback( EXT1_interruptHandler, EXT_INT_1_INDEX );
	ext_init	 ( EXT_INT_1_INDEX, EXT_INT_ON_FALLING_EDGE);
	
	ext_callback( EXT2_interruptHandler, EXT_INT_2_INDEX );
	ext_init	 ( EXT_INT_2_INDEX, EXT_INT_ON_FALLING_EDGE);
	
	GIE_Enable();

	volatile int x = 0;
	
    while(1)
    {
		x++;
		
	}
	return 0;
}