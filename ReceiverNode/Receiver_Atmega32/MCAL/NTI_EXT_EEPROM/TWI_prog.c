/*
 * TWI.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TWI_int.h"
#include "TWI_Config.h"
#include "TWI_private.h"


/*------------------------------------------------------------------------*/
void M_TWI_void_Init(void)
{
#if   TWI_MODE   ==   TWI_MASTER_MODE
	TWBR_REG=72; 
	CLEAR_BIT(TWSR_REG,TWSR_TWPS0);
	CLEAR_BIT(TWSR_REG,TWSR_TWPS1);

#elif TWI_MODE   ==   TWI_SLAVE_MODE
	/* set SLAVE_ADDRESS and if GENERAL_CALL on  */
	TWAR_REG = (SLAVE_ADDRESS << 1) | GENERAL_CALL;

#endif

	/*EN ACK*/
	SET_BIT(TWCR_REG,TWCR_TWEA);
	/*EN TWI */
	SET_BIT(TWCR_REG,TWCR_TWEN);
}

/*------------------------------------------------------------------------*/

u8 M_TWI_u8_StartCondition(void)
{
	TWI_ERROR_STATUS local_error =NO_ERROR ;

	/* Start Condition */
	SET_BIT(TWCR_REG,TWCR_TWSTA);

	  /* to clear the flag */
	SET_BIT(TWCR_REG,TWCR_TWINT);

	while(GET_BIT(TWCR_REG,TWCR_TWINT) == 0);

	if((TWSR_REG & 0xF8) != TWI_START_COND_ACK)
	{
		local_error=START_ERROR;
	}
	else
	{

	}



	return  local_error ;
}

/***************************************************************************/

void M_TWI_void_StopCondition(void)

{

	SET_BIT(TWCR_REG,TWCR_TWSTO);
	SET_BIT(TWCR_REG,TWCR_TWINT);   /* to clear the flag */




}

/***************************************************************************/

u8 M_TWI_u8_RepeatedStart(void)
{
	TWI_ERROR_STATUS local_error =NO_ERROR ;

	/* Start Condition */
	SET_BIT(TWCR_REG,TWCR_TWSTA);

	/* to clear the flag */
	SET_BIT(TWCR_REG,TWCR_TWINT);

	while(GET_BIT(TWCR_REG,TWCR_TWINT) == 0);

	if((TWSR_REG & 0xF8) != TWI_REPEATED_START_COND_ACK)
	{
		local_error=REPEATED_STSRT_ERROR;
	}
	else
	{

	}

	return  local_error ;
}

/***************************************************************************/

u8 M_TWI_u8_SendSlaveAddressWrite(u8 Copy_u8Address)
{
	TWI_ERROR_STATUS local_error =NO_ERROR ;

	TWDR_REG = (Copy_u8Address << 1);

	/* Clear Start condition */
	CLEAR_BIT(TWCR_REG,TWCR_TWSTA);

	/* to clear the flag */
	SET_BIT(TWCR_REG,TWCR_TWINT);

	while(GET_BIT(TWCR_REG,TWCR_TWINT) == 0);


	if((TWSR_REG & 0xF8) != TWI_SEND_SLAVE_ADD_WRITE_ACK)
	{
		local_error=SLAVE_ADDRESS_WRITE_ERROR;
	}
	else
	{

	}
	return  local_error ;
}

/***************************************************************************/

u8 M_TWI_u8_SendSlaveAddressRead(u8 Copy_u8Address)
{

	TWI_ERROR_STATUS local_error =NO_ERROR ;
	TWDR_REG = (Copy_u8Address << 1) | 1;

	CLEAR_BIT(TWCR_REG,TWCR_TWSTA);
	SET_BIT(TWCR_REG,TWCR_TWINT);   /* to clear the flag */
		while(GET_BIT(TWCR_REG,TWCR_TWINT) == 0);

	if((TWSR_REG & 0xF8) != TWI_SEND_SLAVE_ADD_READ_ACK)
	{
		local_error=SLAVE_ADDRESS_READ_ERROR;
	}
	else
	{

	}
	return  local_error ;

}

/***************************************************************************/
u8 M_TWI_u8_SendByte(u8 Copy_u8Data)
{
	TWI_ERROR_STATUS local_error =NO_ERROR ;
	TWDR_REG = Copy_u8Data;
	//CLEAR_BIT(TWCR_REG,TWCR_TWSTA);
	SET_BIT(TWCR_REG,TWCR_TWINT);   /* to clear the flag */

	while(GET_BIT(TWCR_REG,TWCR_TWINT) == 0);

	if((TWSR_REG & 0xF8) != TWI_SEND_BYTE_ACK)
	{
		local_error=SEND_BYTE_ERROR;
	}
	else
	{

	}
	return  local_error ;

}

/***************************************************************************/

u8   M_TWI_u8_ReadByte(u8 *TWI_DATA)
{
	TWI_ERROR_STATUS local_error =NO_ERROR ;



	SET_BIT(TWCR_REG,TWCR_TWINT);   /* to clear the flag */


	while(GET_BIT(TWCR_REG,TWCR_TWINT) == 0);
	if((TWSR_REG & 0xF8) != TWI_READ_BYTE_ACK)
	{
		local_error=READ_BYTE_ERROR;
	}
	else
	{
		*TWI_DATA = TWDR_REG;
	}
	return  local_error ;
}

