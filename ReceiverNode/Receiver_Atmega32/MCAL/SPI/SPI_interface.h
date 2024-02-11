/*
 * SPI_interface.h
 *
 * Created: 10/31/2023 2:52:53 PM
 *  Author: Mina
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "../DIO/dio_interface.h"
#include "../GIE/gie_interface.h"

void SPI_Master_Init(void);
void SPI_Slave_Init(void);
void SPI_Transmit(u8 value);
void SPI_Receive(volatile u8* value);
void SPI_Callback(void (*ptr)(void));



#endif /* SPI_INTERFACE_H_ */