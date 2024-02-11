/*
 * WDT_private.h
 *
 * Created: 10/29/2023 10:22:41 AM
 *  Author: Mina
 */ 


#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

#include "../std_types.h"
#include "../bit_math.h"

#define WDTCR (*(volatile u8*) 0x41)

#define  WDTOE	4
#define  WDE	3
#define  WDP2	2
#define  WDP1	1
#define  WDP0	0

#endif /* WDT_PRIVATE_H_ */