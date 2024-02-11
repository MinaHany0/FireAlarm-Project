/*
 * Receiver_Atmega32.c
 *
 * Created: 11/8/2023 11:24:22 PM
 * Author : Mina
 */ 

/****************INCLUDES**************************/
#include "MCAL/GIE/gie_interface.h"
#include "MCAL/SPI/SPI_interface.h"
#include "HAL/LED/led_interface.h"
#include "MCAL/WDT/WDT_interface.h"
#include "MCAL/NTI_EXT_EEPROM/EXT_EEPROM_int.h"
/****************MACRO VARIABLES*******************/
#define GAS_NO_FLAME_NO			1
#define GAS_NO_FLAME_YES		2
#define GAS_YES_FLAME_NO		4
#define GAS_YES_FLAME_YES		8
/****************GLOBAL VARIABLES******************/
u8 spi_counter = 0;

volatile u8 gas_state	= 0;
volatile u8 flame_state	= 0;
volatile u8 temp_val		= 24;
volatile u8 test = 0;

u8 led_counter_flag = 0;
/**********HELPER FUNCTIONS************************/
void SPI_intHandler(void);
/****************MAIN FUNCTION*********************/

int main(void)
{
	H_EXT_EEPROM_void_Init();
	gas_state = H_EXT_EEPROM_void_Read(0x10);
	LED_init(LED_BLUE_PORT,LED_BLUE_PIN);
	LED_init(LED_YELLOW_PORT,LED_YELLOW_PIN);
	LED_init(LED_GREEN_PORT,LED_GREEN_PIN);
	LED_turn_on(LED_GREEN_PORT,LED_GREEN_PIN);
	SPI_Callback(SPI_intHandler);
	SPI_Slave_Init();
	GIE_Enable();
	
    while (1) 
    {
		test = 1;
		
		if(gas_state == GAS_NO_FLAME_NO){
			LED_turn_on(LED_GREEN_PORT,LED_GREEN_PIN);
			LED_turn_off(LED_YELLOW_PORT,LED_YELLOW_PIN);
			LED_turn_off(LED_BLUE_PORT,LED_BLUE_PIN);
		}
		else if(gas_state == GAS_NO_FLAME_YES){
			LED_turn_off(LED_GREEN_PORT,LED_GREEN_PIN);
			LED_turn_off(LED_YELLOW_PORT,LED_YELLOW_PIN);
			LED_turn_on(LED_BLUE_PORT,LED_BLUE_PIN);
		}
		else if(gas_state == GAS_YES_FLAME_NO){
			LED_turn_off(LED_GREEN_PORT,LED_GREEN_PIN);
			LED_turn_on(LED_YELLOW_PORT,LED_YELLOW_PIN);
			LED_turn_off(LED_BLUE_PORT,LED_BLUE_PIN);
		}
		else if(gas_state == GAS_YES_FLAME_YES){
			LED_turn_off(LED_GREEN_PORT,LED_GREEN_PIN);
			LED_turn_on(LED_YELLOW_PORT,LED_YELLOW_PIN);
			LED_turn_on(LED_BLUE_PORT,LED_BLUE_PIN);
		}
		
		
		
		
		
		 
    }
}

void SPI_intHandler(void){
	SPI_Receive(&gas_state);	
	gas_state = gas_state;
	
	H_EXT_EEPROM_void_Write(0x10,gas_state);
}
