/*
 * I2C_config.h
 *
 * Created: 11/4/2023 9:32:59 AM
 *  Author: Mina
 */ 


#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#include "I2C_private.h"

typedef enum{
	I2C_PRESCALER_1 = 0,
	I2C_PRESCALER_4,
	I2C_PRESCALER_16,
	I2C_PRESCALER_64,
}I2C_prescaler_t;

typedef enum{
	ACK,
	NOT_ACK,	
}ack_t;

typedef enum{
	GEN_CALL_DISABLE,
	GEN_CALL_ENABLE,
}gen_call_t;

#define I2C_FREQ				((u64)100000)
#define I2C_PRESCALER_VALUE		I2C_PRESCALER_1 
#define ACKNOWLEDGE_ENABLE		NOT_ACK
#define DEVICE_ADDRESS			0b0101010
#define GEN_CALL			GEN_CALL_ENABLE

#endif /* I2C_CONFIG_H_ */