/*
 * SPI_config.h
 *
 * Created: 10/31/2023 3:05:39 PM
 *  Author: Mina
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "SPI_private.h"

/*parameters to be configured : speed mode , frequency*/
//phase and clock polarity is 0 and 0 
//speed is a normal

#define NORMAL_SPEED		0
#define DOUBLE_SPEED		1
#define SPI_SPEED			NORMAL_SPEED

#define SPI_CLK_POLARITY	SPI_CK_IDLE_LOW
#define SPI_CLK_PHASE		SPI_CK_PHASE_SAMPLE_LEAD
#define SPI_MASTER_MODE		SPI_MSTR_ENABLE
#define SPI_INTERRUPT		SPI_INTERRUPT_ENABLE

#define SPI_PORT					PORT_B
#define SS_PIN						PIN_4
#define MOSI_PIN					PIN_5
#define MISO_PIN					PIN_6
#define SCK_PIN						PIN_7

#define SPI_INTERRUPT_DISABLE		0
#define SPI_INTERRUPT_ENABLE		1

#define SPI_DISABLE					0
#define SPI_ENABLE					1

#define SPI_DATA_ORDER_RSB			0
#define SPI_DATA_ORDER_LSB			1

#define SPI_MSTR_DISABLE			0
#define SPI_MSTR_ENABLE				1

#define SPI_CK_IDLE_LOW				0
#define SPI_CK_IDLE_HIGH			1

#define SPI_CK_PHASE_SAMPLE_LEAD	0
#define SPI_CK_PHASE_SETUP_LEAD		1

#define SPI_SPI2X_NORMAL_SPEED		0
#define SPI_SPI2X_DOUBLE_SPEED		1


#endif /* SPI_CONFIG_H_ */