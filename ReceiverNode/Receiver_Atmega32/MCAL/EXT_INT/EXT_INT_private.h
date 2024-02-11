/*
 * EXT_INT_private.h
 *
 * Created: 10/22/2023 2:21:30 PM
 *  Author: Mina
 */ 

#define MCUCR  (*((volatile u8*) 0x55))
#define MCUCSR (*((volatile u8*) 0x54))
#define GICR   (*((volatile u8*) 0x5B))

#define ISC0_0_PIN_MASK		0
#define ISC0_1_PIN_MASK		1

#define ISC1_0_PIN_MASK		2
#define ISC1_1_PIN_MASK		3

#define ISC2_PIN_MASK		6

#define GICR_INT0_PIN_MASK	6
#define GICR_INT1_PIN_MASK	7
#define GICR_INT2_PIN_MASK	5