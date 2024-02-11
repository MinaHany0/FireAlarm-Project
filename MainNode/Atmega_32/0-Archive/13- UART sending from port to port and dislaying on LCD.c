 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 
/****************INCLUDES**************************/
#include "MCAL/DIO/dio_interface.h"
#include "HAL/LCD/lcd_interface.h"
#
/****************GLOBAL VARIABLES******************/
/****************PROTOTYPES************************/
u8 cal = 50;
u8 receive = 0;
u8 lcd_str[4];
/****************MAIN FUNCTION*********************/
int main(void){
	lcd_init_4bit();
	lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	DIO_void_SetPortDirection(PORT_C,DIO_DIRECTION_OUTPUT);
	DIO_void_SetPortDirection(PORT_D,DIO_DIRECTION_INPUT);
	while(1)
	{	
		DIO_void_SetPortValue(PORT_C,cal);
		cal++;
		_delay_ms(1000);
		DIO_void_ReadPortValue(PORT_D, &receive);
		lcd_convert_u8_to_str(receive,lcd_str);
		lcd_send_string_pos(lcd_str,1,1);
	}
}
/**********HELPER FUNCTIONS************************/
