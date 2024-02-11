/*
 * I2C_Private.h
 *
 * Created: 7/8/2023 8:01:36 PM
 *  Author: Rizk
 */ 


#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_


/*Macros for Checking(Master Transmit)*/
#define I2C_SC_ACK            0x08
#define I2C_RSC_ACK           0x10
#define I2C_MT_SLA_W_ACK      0x18
#define I2C_MT_DATA_ACK       0x28


/*Macros for Checking(Master Receive)*/
 #define I2C_MR_SLA_R_ACK        0x40
 #define I2C_MR_DATA_ACK  0x80



/*TWI Registers*/
#define TWBR   *((volatile u8*)0x20)
#define TWSR   *((volatile u8*)0x21)
#define TWAR   *((volatile u8*)0x22)
#define TWDR   *((volatile u8*)0x23)
#define TWCR   *((volatile u8*)0x56)






#endif /* I2C_PRIVATE_H_ */