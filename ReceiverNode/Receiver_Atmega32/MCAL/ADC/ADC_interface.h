/*
 * ADC_interface.h
 *
 * Created: 10/23/2023 2:08:32 PM
 *  Author: Mina
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "../std_types.h"
#include "../bit_math.h"

#define ADC_ENABLE_BIT				0x07
#define ADC_REF_SELECT_1			0x07
#define ADC_REF_SELECT_0			0x06
#define ADC_LEFT_ADJUST_BIT			0x05
#define ADC_PRESCALER_BIT_0			0x00
#define ADC_PRESCALER_BIT_1			0x01
#define ADC_PRESCALER_BIT_2			0x02
#define ADC_INTERRUPT_ENABLE_BIT	0x03
#define ADC_INTERRUPT_FLAG_BIT		0x04
#define ADC_START_CONVERSION_BIT	0x06

#define ADC_CHANNEL_0				0x00
#define ADC_CHANNEL_1				0x01
#define ADC_CHANNEL_2				0x02
#define ADC_CHANNEL_3				0x03
#define ADC_CHANNEL_4				0x04
#define ADC_CHANNEL_5				0x05
#define ADC_CHANNEL_6				0x06
#define ADC_CHANNEL_7				0x07


void ADC_Init(void);
void ADC_Read(u8 channel, u16* ptr);

void ADC_Result(u8 channel,s32 min_ref_value, s32 max_ref_value, f32* flt_result);
void ADC_Result_LM35(u8 channel, f32* flt_result);

/*********************************AUTO TRIGGER FUNCTION *********************************/
void ADC_auto_trigger_SelectInt0AndReturnFreeRunning(u8 channel, u16* retVal);
void ADC_Auto_Trigger_Init(u8 channel);
void ADC_Auto_Trigger_Read(volatile u16* retVal);

#endif /* ADC_INTERFACE_H_ */