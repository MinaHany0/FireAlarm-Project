/*
 * I2C.c
 *
 * Created: 7/8/2023 8:01:17 PM
 *  Author: Rizk
 */ 

#include "bit_math.h"
#include "std_types.h"

#include "I2C_Private.h"
#include "I2C_Interface.h"
#include "I2C_Config.h"

void I2C_MASTER_INIT(void)
{
	/*  Set prescaller 0  */
		      CLEAR_BIT(TWSR,0);
			  CLEAR_BIT(TWSR,1);	
			  
	/*  Set CLK 100kHZ -> Fcpu= 8MHZ  */
	          TWBR=32;
			  
	/*  Set CLK 100kHZ -> Fcpu= 16MHZ */
	            //TWBR=72;	     	

	/*            Enable ACK          */
	            SET_BIT(TWCR,6);

	/*            Enable I2C           */
            	SET_BIT(TWCR,2);
	
	
}
void I2C_SLAVE_INIT(u8 slave_address)
{
	
     /*    Set Slave Address   */
	 TWAR = slave_address<<1;
	 
	/*            Enable ACK          */
	SET_BIT(TWCR,6);

	/*            Enable I2C           */
	SET_BIT(TWCR,2);
		 	
	
	
}

I2C_Error I2C_Send_Start_Condition(void)
{
    I2C_Error Local_var = I2C_ok;

    /*  I2C Start Conversion  */
		SET_BIT(TWCR,5);
		
    /*      Clear Flag        */
        SET_BIT(TWCR,7);	
	
    /*      Polling on the Flag        */
    while(GET_BIT(TWCR,7)==0) {  }	
		
	/*  Check on ACK*/
	     if((TWSR & 0xF8)!=0x08)
		 {
			 
			 Local_var = I2C_SC_Error;
		 }
		 else
		 {
			 
		 }			 
		 return Local_var;
	   
}



I2C_Error I2C_Send_Repeated_Start_Condition(void)
{
	I2C_Error Local_var = I2C_ok;

	/*  I2C Start Conversion  */
	SET_BIT(TWCR,5);
	
	/*      Clear Flag        */
	SET_BIT(TWCR,7);
	
	/*      Polling on the Flag        */
	while(GET_BIT(TWCR,7)==0) {  }
	
	/*  Check on ACK*/
	if((TWSR & 0xF8)!=I2C_RSC_ACK)
	{
		
		Local_var = I2C_RSC_Error;
	}
	return Local_var;
	
}
I2C_Error I2C_Send_Slave_Address_Write(u8 slave_add)
{
	    I2C_Error Local_var = I2C_ok; 
		
		 /*    Set Slave Address   */
		    TWDR = slave_add<<1;
	
	    /*     Write Operation R/W bit    */
		     CLEAR_BIT(TWDR,0);
			 
	    /*    Clear start conversion    */
	          CLEAR_BIT(TWCR,5);			 
			 
			 
	    /*      Clear Flag        */
	        SET_BIT(TWCR,7);
	    
	    /*      Polling on the Flag        */
	        while(GET_BIT(TWCR,7)==0) {  }		
				
	if((TWSR & 0xF8)!=0X18)
	{
		
		Local_var = I2C_MT_SLA_W_Error;
	}					 
		return Local_var;
	
}
I2C_Error I2C_Send_Slave_Address_Read(u8 slave_add)
{
	I2C_Error Local_var = I2C_ok;
	
	/*    Set Slave Address   */
	    TWDR = slave_add<<1;
	
	/*     Read Operation R/W bit    */
	      SET_BIT(TWDR,0);
		  
			 
	/*    Clear start conversion    */
	     CLEAR_BIT(TWCR,5);		  
	
	/*      Clear Flag        */
	    SET_BIT(TWCR,7);
	
	/*      Polling on the Flag        */
	while(GET_BIT(TWCR,7)==0) {  }
	
	if((TWSR & 0xF8)!=I2C_MR_SLA_R_ACK)
	{
		
		Local_var = I2C_MR_SLA_R_Error;
	}
	return Local_var;
	
}
I2C_Error I2C_Send_Master_Send_Byte(u8 master_data)
{
	I2C_Error Local_var = I2C_ok;
	
	TWDR = master_data;	
	
	/*      Clear Flag        */
	SET_BIT(TWCR,7);
	
	/*      Polling on the Flag        */
	while(GET_BIT(TWCR,7)==0) {  }
		
	if((TWSR & 0xF8)!=I2C_MT_DATA_ACK)
	{
		
		Local_var = I2C_MT_Data_Error;
	}
	return Local_var;	
	
	
}
I2C_Error I2C_Send_Master_Read_Byte(u8 *master_data_read)
{
	I2C_Error Local_var = I2C_ok;
	
	/*      Clear Flag        */
	SET_BIT(TWCR,7);
	
	/*      Polling on the Flag        */
	while(GET_BIT(TWCR,7)==0) {  }
	
	if((TWSR & 0xF8)!=I2C_MR_DATA_ACK)
	{
		
		Local_var = I2C_MR_Data_Error;
	}
	else
	{
		*master_data_read = TWDR;
	}
	return Local_var;
	
	
}
void I2C_Send_Stop_Condition(void)
{
	
	
    /*  I2C Stop Conversion  */
       SET_BIT(TWCR,4);
    

	
    /*      Clear Flag        */
       SET_BIT(TWCR,7);	

}