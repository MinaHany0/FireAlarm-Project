/*
 * I2C_private.h
 *
 * Created: 11/4/2023 9:33:15 AM
 *  Author: Mina
 */ 


#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWBR (*(volatile u8*) 0x20)
#define TWCR (*(volatile u8*) 0x56)
#define TWSR (*(volatile u8*) 0x21)
#define TWDR (*(volatile u8*) 0x23)
#define TWAR (*(volatile u8*) 0x22)


typedef enum{
	TWIE,
	TWEN = 2,
	TWWC,
	TWSTO,
	TWSTA,
	TWEA,
	TWINT, 
}TWCRbits;

typedef enum{
	TWPS0,
	TWPS1,
	TWS3 = 3,
	TWS4,
	TWS5,
	TWS6,
	TWS7,     
}TWSRbits;

typedef enum{
	TWGCE,
	TWA0,
	TWA1,
	TWA2,
	TWA3,
	TWA4,
	TWA5,
	TWA6,       
}TWARbits;

#endif /* I2C_PRIVATE_H_ */