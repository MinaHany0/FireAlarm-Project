 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 

#include "MCAL/DIO/dio_interface.h"
#include "MCAL/GIE/gie_interface.h"
#include "MCAL/EXT_INT/ext_int_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "HAL/LED/led_interface.h"
#include "HAL/BUTTON/btn_interface.h"
#include "HAL/SEV_SEG/sev_seg_interface.h"
#include "HAL/LCD/lcd_interface.h"

int main(void){

	ADC_Init();
	lcd_void_init_4bit();
	f32 result_adc = 0;
	u8 str[11];
	u8 start_text[] = "ADC result = ";
	
	
	lcd_void_send_string_pos(start_text, 1, 1);
	
	while(1)
	{
		ADC_Result(ADC_CHANNEL_0, 5, &result_adc);
		lcd_convert_f32_to_str(result_adc , str);
		lcd_void_send_string_pos(str, 1, 15);
		_delay_ms(500);
		
	}
	return 0;
}