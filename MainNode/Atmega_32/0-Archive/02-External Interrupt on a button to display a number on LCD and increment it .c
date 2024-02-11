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

volatile u32 x = 888;

void EXT0_interruptHandler(void){
}
void EXT1_interruptHandler(void){
	x++;
}
void EXT2_interruptHandler(void){
}



int main(void)
{
	
	ext_callback( EXT0_interruptHandler, EXT_INT_0_INDEX );
	ext_callback( EXT1_interruptHandler, EXT_INT_1_INDEX );
	ext_callback( EXT2_interruptHandler, EXT_INT_2_INDEX );
	ext_init	 ( EXT_INT_0_INDEX, EXT_INT_ON_FALLING_EDGE);
	ext_init	 ( EXT_INT_1_INDEX, EXT_INT_ON_FALLING_EDGE);
	ext_init	 ( EXT_INT_2_INDEX, EXT_INT_ON_FALLING_EDGE);
	GIE_Enable();
	
	seg_7_void_init();
	//lcd_void_init_4bit();
	//lcd_void_send_char('A');
	
	
	
	
	
    while(1)
    {
		
		seg_7_void_write_val(x);
		
		
	}
	return 0;
}