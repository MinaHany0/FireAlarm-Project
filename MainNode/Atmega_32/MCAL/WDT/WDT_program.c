/*
 * WDT_program.c
 *
 * Created: 10/29/2023 10:21:57 AM
 *  Author: Mina
 */ 

#include "WDT_private.h"
#include "WDT_config.h"
#include "WDT_interface.h"


void WDT_Enable(WDT_prescaler_t _time){
	/*choose time mode*/
	WDTCR &= (u8)(~7);
	WDTCR |= (u8)(_time);
	/*enable WDT*/
	SET_BIT(WDTCR,WDE);
}

void WDT_Disable(void){
	/*set WDTOE & WDE both "specific sequence" */
	WDTCR = (1 << WDTOE) | (1 << WDE);
	/*clear WDTCR*/
	WDTCR = 0x00;
}