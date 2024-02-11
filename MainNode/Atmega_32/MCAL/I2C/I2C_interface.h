/*
 * I2C_interface.h
 *
 * Created: 11/4/2023 9:32:44 AM
 *  Author: Mina
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include "../std_types.h"
#include "../bit_math.h"

void I2C_MI_Init_Master(void);
void I2C_MI_Init_Slave(void);
void I2C_MI_Send_Start_Condition(void);
void I2C_MI_Send_Repeated_Start_Condition(void);
void I2C_MI_Send_Slave_Address_Write(u8 slave_add);
void I2C_MI_Send_Slave_Address_Read(u8 slave_add);
void I2C_MI_Send_Master_Send_Byte(u8 master_data);
void I2C_MI_Send_Master_Read_Byte(u8 *master_data_read);
void I2C_MI_Send_Stop_Condition(void);


#endif /* I2C_INTERFACE_H_ */