/*
 * I2C_program.c
 *
 * Created: 11/4/2023 9:32:27 AM
 *  Author: Mina
 */ 

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"

void CalcBaudRate(void){
	/*mask the reg for changing the value of prescaler*/
	/*calculate baud rate and pass to register*/
	TWSR &= 0xFC;
	TWSR |= I2C_PRESCALER_VALUE;
	TWBR = ((F_CPU / (u64)I2C_FREQ)-16)/((u64)2* ((u64)4 ^ (u8)(TWSR & 0x03) )  );
}

void I2C_MI_Init_Master(void){
	/* configure the baud rate generator unit	*/
	/* config acknowledge bit if enabled		*/
	/* enable I2C								*/
	
	CalcBaudRate();
	#if ACKNOWLEDGE_ENABLE == ACK
	SET_BIT(TWCR,TWEA);
	#endif
	SET_BIT(TWCR,TWEN);
}

void I2C_MI_Init_Slave(void){
	/* configure address of master & general call	*/
	/* config acknowledge bit if enabled			*/
	/* enable I2C									*/

	TWAR = DEVICE_ADDRESS << 1 | GEN_CALL;
	#if ACKNOWLEDGE_ENABLE == ACK
	SET_BIT(TWCR,TWEA);
	#endif
	SET_BIT(TWCR,TWEN);
}

void I2C_MI_Send_Start_Condition(void){
/* send TWSTA start condition in TWCR							*/
/* clear TWI flag as no operation is done if it is set			*/
/* poll on flag to check if start done successfully				*/
/* must clear TWSTA condition when transmit has been sent		*/
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTA);
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
	CLEAR_BIT(TWCR,TWSTA);
}

void I2C_MI_Send_Repeated_Start_Condition(void){
	I2C_MI_Send_Start_Condition();
}

void I2C_MI_Send_Slave_Address_Write(u8 slave_add){
	/* poll of flag to check last process done successfully		*/
	/* write SLA + R/W	in TWDR									*/
	/* clear flag to start transmission							*/
	/*	specific value to be written in TWCR -- IGNORED FOR NOW	*/
	/*	poll on flag and clear it to continue					*/
	u8 write_or_read = 0;
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
	TWDR = ( slave_add << 1 | write_or_read );
	SET_BIT(TWCR,TWINT);
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
}

void I2C_MI_Send_Slave_Address_Read(u8 slave_add){
	/* poll of flag to check last process done successfully		*/
	/* write SLA + R/W	in TWDR									*/
	/* clear flag to start transmission							*/
	/*	specific value to be written in TWCR -- IGNORED FOR NOW	*/
	/*	poll on flag and clear it to continue					*/
	u8 write_or_read = 1;
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
	TWDR = ( slave_add << 1 | write_or_read );
	SET_BIT(TWCR,TWINT);
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
}

void I2C_MI_Send_Master_Send_Byte(u8 master_data){
	/* poll on flag*/
	/* put data in TWDR*/
	/* clear flag to immediately start writing */
	/* poll on flag*/
	
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
	TWDR = master_data;
	SET_BIT(TWCR,TWINT);
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
}

void I2C_MI_Send_Master_Read_Byte(u8 *master_data_read){
	/* poll on flag*/
	/* read data from TWDR*/
	/* clear flag to immediately start reading */
	/* poll on flag*/
	
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
	*master_data_read = TWDR ;
	SET_BIT(TWCR,TWINT);
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
}

void I2C_MI_Send_Stop_Condition(void){
	/* poll on flag*/
	/* put stop condition*/
	/* clear flag to immediately start stop condition */
	
	while( 0 == GET_BIT(TWCR,TWINT) )
	;
	SET_BIT(TWCR, TWSTO);
	SET_BIT(TWCR,TWINT);
	
}