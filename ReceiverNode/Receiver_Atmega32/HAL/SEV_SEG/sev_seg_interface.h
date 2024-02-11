/*
 * sev_seg_interface.h
 *
 * Created: 10/21/2023 9:53:41 AM
 *  Author: Mina
 */ 



#ifndef SEV_SEG_INTERFACE_H_
#define SEV_SEG_INTERFACE_H_

/*********************************INCLUDES*************************************************/
#include "../../MCAL/DIO/dio_interface.h"
#include "sev_seg_config.h"
/*********************************MACRO DECLARATIONS***************************************/
/*********************************MACRO FUNCTIONS******************************************/
/*********************************DATA TYPE DEFINITIONS************************************/
typedef struct {
	u8 port :2;
	u8 pin  :3;
}seg_7_pin_t;
/*********************************FUNCTION INTERFACE DECLARATION***************************/
void seg_7_void_init(void);
void seg_7_void_write_val(u32 val);
#endif /* SEV_SEG_INTERFACE_H_ */