/*
 * EEPROM.c
 *
 * Created: 7/9/2023 3:58:56 PM
 *  Author: Rizk
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "I2C_Interface.h"

#include "EEPROM_Private.h"
#include "EEPROM_Interface.h"
#include "EEPROM_Config.h"


u8 EEPROM_WRITE_DATA(u16 Address , u8 data)
{
	/*     Send Start Condition      */
         I2C_Send_Start_Condition();

	/*     Send Fixed Address      */
       I2C_Send_Slave_Address_Write((EEPROM_FIXED_ADDRESS)|(EEPROM_A2_VALUE<<2)|((Address>>8)&3));

	/*     Send  Address     */
       I2C_Send_Master_Send_Byte((u8)Address);
	   
	/*     Send data     */
	I2C_Send_Master_Send_Byte(data);	  	
	   
	/*     Send Stop Condition     */	   
       I2C_Send_Stop_Condition();	  
	   return 1; 
}

u8 EEPROM_READ_DATA(u16 Address , u8 * data)
{
	/*     Send Start Condition      */
	    I2C_Send_Start_Condition();

	/*     Send Fixed Address with write      */
	    I2C_Send_Slave_Address_Write((EEPROM_FIXED_ADDRESS)|(EEPROM_A2_VALUE<<2)|((Address>>8)&3));	
		
	/*     Send Actual Address     */
	    I2C_Send_Master_Send_Byte((u8)Address);	
		
	/*     Send Repeated Start Condition      */		
		I2C_Send_Repeated_Start_Condition();
	/*     Send Fixed Address with Read      */		
		I2C_Send_Slave_Address_Read((EEPROM_FIXED_ADDRESS)|(EEPROM_A2_VALUE<<2)|((Address>>8)&3));
	/*Read Data*/	
		I2C_Send_Master_Read_Byte(data);
	/*        STOP CONDITION          */
	I2C_Send_Stop_Condition();
	return 1;
}
