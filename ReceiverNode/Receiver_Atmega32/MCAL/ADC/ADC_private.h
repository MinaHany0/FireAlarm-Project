/*
 * ADC_private.h
 *
 * Created: 10/23/2023 2:08:17 PM
 *  Author: Mina
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include "../std_types.h"

#define ADMUX   *((volatile u8*) 0x27)
#define ADCSRA  *((volatile u8*) 0x26)

#define ADCL	*((volatile u8*) 0x24)
#define ADCH	*((volatile u8*) 0x25)

#define ADC		*((volatile u16*) 0x24)
#define SFIOR	*((volatile u8*) 0x50)




#endif /* ADC_PRIVATE_H_ */