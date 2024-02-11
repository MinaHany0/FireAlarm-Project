 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 

#include "MCAL/GIE/gie_interface.h"
#include "MCAL/EXT_INT/ext_int_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "HAL/LCD/lcd_interface.h"

/****************GLOBAL VARIABLES******************/
u8 str_LCD_text_1[]= "TEMP READING IS:";
u8 str_LCD_text_2[]= "LDR READING IS:";
u8 max_ref_value = 100;
u8 min_ref_value = 0;
u16 LDR_value	 = 0;
u8 str_LDR_value [11];
u8 str_temp_value[11];
u8 clear_read[] = "                    ";
f32 temp_value = 0.0;
/****************GLOBAL VARIABLES******************/

/****************PROTOTYPES******************/
void ext_int_InterruptHandler(void);
/****************PROTOTYPES******************/

int main(void){
	ADC_Init();
	lcd_void_init_4bit();
	lcd_void_send_command(LCD_CMD_CLEAR_DISPLAY);
	lcd_void_send_string_pos(str_LCD_text_1,1,1);
	lcd_void_send_string_pos(str_LCD_text_2,3,1);
	ext_callback(ext_int_InterruptHandler,EXT_INT_0_INDEX);
	ext_init(EXT_INT_0_INDEX, EXT_INT_ON_RISING_EDGE);           /// changed to rising
	GIE_Enable();
	while(1)
	{
		ADC_Result_LM35(ADC_CHANNEL_1, &temp_value);
		lcd_convert_f32_to_str(temp_value, str_temp_value);
		lcd_void_send_string_pos(str_temp_value,2,1);
		_delay_ms(5);
	}
	return 0;
}

void ext_int_InterruptHandler(void){
	ADC_auto_trigger_SelectInt0AndReturnFreeRunning(ADC_CHANNEL_0, &LDR_value);
	LDR_value = ((max_ref_value-min_ref_value)*LDR_value / 1024)+ min_ref_value;
	lcd_convert_u16_to_str(LDR_value, str_LDR_value);
	lcd_void_send_string_pos(clear_read, 4,1);
	lcd_void_send_string_pos(str_LDR_value, 4,1);
	lcd_void_send_char_pos('%', 4,4);
	lcd_void_send_command(0xC0);
}