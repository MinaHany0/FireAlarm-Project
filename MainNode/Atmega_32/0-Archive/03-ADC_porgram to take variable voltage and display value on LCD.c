 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 



#include "MCAL/DIO/dio_interface.h"
#include "HAL/LED/led_interface.h"
#include "HAL/BUTTON/btn_interface.h"
#include "HAL/SEV_SEG/sev_seg_interface.h"
#include "HAL/LCD/lcd_interface.h"
#include "MCAL/GIE/gie_interface.h"
#include "MCAL/EXT_INT/ext_int_interface.h"
#include "MCAL/ADC/ADC_interface.h"



int main(void)
{
	volatile u16 adc_reading;
	volatile u8 str[6];
	ADC_Init();
	lcd_void_init_4bit();
    while(1)
    {
		ADC_Read(0, &adc_reading );
		adc_reading =  (adc_reading * 5000ul) / 1023;
		
		lcd_convert_u16_to_str(adc_reading, str);
		lcd_void_send_string_pos(str,1,1);
		_delay_ms(500);
	}
	return 0;
}