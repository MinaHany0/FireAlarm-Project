/*
 * WDT_interface.h
 *
 * Created: 10/29/2023 10:22:09 AM
 *  Author: Mina
 */ 


#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

typedef enum{
	time_16_3_msec,
	time_32_5_msec,
	time_65_msec,
	time_130_msec,
	time_260_msec,
	time_520_msec,
	time_1000_msec,
	time_2100_msec,
}WDT_prescaler_t;

void WDT_Enable(WDT_prescaler_t _time);
void WDT_Disable(void);

#endif /* WDT_INTERFACE_H_ */