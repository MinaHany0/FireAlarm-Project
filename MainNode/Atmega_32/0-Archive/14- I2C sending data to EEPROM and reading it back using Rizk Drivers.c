 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 
/****************INCLUDES**************************/
#include "MCAL/NTI_EXT_EEPROM/EXT_EEPROM_int.h"
#include "MCAL/NTI_EXT_EEPROM/TWI_int.h"
#include "HAL/LCD/lcd_interface.h"
/****************GLOBAL VARIABLES******************/
u8 data_send = 'A';
u8 data_read = 'z';
/****************PROTOTYPES************************/
/****************MAIN FUNCTION*********************/
int main(void){
	
	M_TWI_void_Init();
	lcd_init_4bit();
	lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(500);
	while(1)
	{	
		H_EXT_EEPROM_void_Init();
		H_EXT_EEPROM_void_Write(10,data_send);
		_delay_ms(10);
		data_read = H_EXT_EEPROM_void_Read(10);

		lcd_send_char_pos(data_read,2,1);
		_delay_ms(500);
		data_send++;
	}
	return 0;
}
/**********HELPER FUNCTIONS************************/
