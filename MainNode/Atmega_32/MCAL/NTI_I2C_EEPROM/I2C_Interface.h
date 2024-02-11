/*
 * I2C_Interface.h
 *
 * Created: 7/8/2023 8:01:56 PM
 *  Author: Rizk
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include "std_types.h"
#include "bit_math.h"
typedef enum {
	I2C_ok,
	I2C_SC_Error,
	I2C_RSC_Error, 
	I2C_MT_SLA_W_Error,
	I2C_MR_SLA_R_Error,
	I2C_MT_Data_Error,
	I2C_MR_Data_Error,

	}I2C_Error;
	
	
void I2C_MASTER_INIT(void);
void I2C_SLAVE_INIT(u8 slave_address);
	
I2C_Error I2C_Send_Start_Condition(void);
I2C_Error I2C_Send_Repeated_Start_Condition(void);
I2C_Error I2C_Send_Slave_Address_Write(u8 slave_add);
I2C_Error I2C_Send_Slave_Address_Read(u8 slave_add);
I2C_Error I2C_Send_Master_Send_Byte(u8 master_data);
I2C_Error I2C_Send_Master_Read_Byte(u8 *master_data_read);
void      I2C_Send_Stop_Condition(void);



#endif /* I2C_INTERFACE_H_ */