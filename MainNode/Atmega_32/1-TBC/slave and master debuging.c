 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 
/****************INCLUDES**************************/
#include "MCAL/I2C/I2C_interface.h"
#include "HAL/LED/led_interface.h"
/****************GLOBAL VARIABLES******************/
u8 data_to_send = 'A';
/****************PROTOTYPES************************/
/****************MAIN FUNCTION*********************/
int main(void){
	I2C_MI_Init_Master();
	while(1){
		I2C_MI_Send_Start_Condition();
		I2C_MI_Send_Slave_Address_Write(0b0101010);
		I2C_MI_Send_Master_Send_Byte(data_to_send);
		I2C_MI_Send_Stop_Condition();
	}
}
/**********HELPER FUNCTIONS************************/
