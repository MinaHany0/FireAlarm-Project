/*
 * timer0_private.h
 *
 * Created: 10/27/2023 10:39:14 AM
 *  Author: Mina
 */ 


#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_


#define TCCR0  *((volatile u8*) 0x53)
#define TCNT0  *((volatile u8*) 0x52)
#define TIMSK  *((volatile u8*) 0x59)
#define TIFR   *((volatile u8*) 0x58)
#define OCR0   *((volatile u8*) 0x5C)

#define CS00_BIT				0
#define CS01_BIT				1
#define CS02_BIT				2

#define WGM01					3
#define WGM00					6

#define COM01					5
#define COM00					4

#define TOIE0					0
#define TOV0					0
#define OCIE0					1
#define OCF0					1

#define OC0_PORT				PORT_B
#define OC0_PIN					PIN_3


#endif /* TIMER0_PRIVATE_H_ */