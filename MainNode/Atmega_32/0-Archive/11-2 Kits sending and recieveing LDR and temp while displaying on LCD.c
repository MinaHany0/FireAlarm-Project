 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 
/****************INCLUDES**************************/
#include "MCAL/UART/UART_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "HAL/LCD/lcd_interface.h"
/****************GLOBAL VARIABLES******************/
u16 LDR_value = 0;
u8 uart_receiver = 0;
u8 str_LCD_text_1[]= "TEMP READING IS:";
u8 max_ref_value = 100;
u8 min_ref_value = 0;
u8 clear_read[] = "                    ";
u8 lcd_line_1[] = "Temperature =";
u8 lcd_line_3[] = "LDR Value =";
u8 lcd_line_2[4];
u8 lcd_line_4[4];
/****************PROTOTYPES************************/
/****************MAIN FUNCTION*********************/
int main(void){
	lcd_init_4bit();
	lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	lcd_send_string_pos(lcd_line_1, 1,1);
	lcd_send_string_pos(lcd_line_3, 3,1);
	ADC_Init();
	UART_Init(9600);
	
	while(1)
	{
		ADC_Read(ADC_CHANNEL_0, &LDR_value);
		LDR_value = ((max_ref_value-min_ref_value)*LDR_value / 1024)+ min_ref_value;
		UART_Transmit( (u8)LDR_value );
		lcd_convert_u8_to_str((u8)LDR_value,lcd_line_4);
		
		
		UART_Recieve(&uart_receiver);
		lcd_convert_u8_to_str((u8)uart_receiver,lcd_line_2);
		
		
		lcd_send_string_pos(lcd_line_2, 2, 1);
		lcd_send_string_pos(lcd_line_4, 4, 1);
	}
}
/**********HELPER FUNCTIONS************************/
