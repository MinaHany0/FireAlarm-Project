/*
 * ADC_program.c
 *
 * Created: 10/23/2023 2:07:54 PM
 *  Author: Mina
 */ 

#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"


void ADC_Init(void){
	/* disable adc peripheral*/
	CLEAR_BIT(ADCSRA, ADC_ENABLE_BIT);  
	/* select reference of adc*/
	CLEAR_BIT(ADMUX, ADC_REF_SELECT_1);
	SET_BIT(ADMUX, ADC_REF_SELECT_0);
	/*configure right adjustment*/
	CLEAR_BIT(ADMUX, ADC_LEFT_ADJUST_BIT);
	/*configure prescaler to be 128 16MHz crystal */
	SET_BIT(ADCSRA, ADC_PRESCALER_BIT_0);
	SET_BIT(ADCSRA, ADC_PRESCALER_BIT_1);
	SET_BIT(ADCSRA, ADC_PRESCALER_BIT_2);
	/*disable interrupt and clear flag by setting it*/
	CLEAR_BIT(ADCSRA, ADC_INTERRUPT_ENABLE_BIT);
	SET_BIT(ADCSRA, ADC_INTERRUPT_FLAG_BIT);
	/*enable auto trigger *////////////////////////////////added
	SET_BIT(ADCSRA, 5);
	/*select free running mode */
	CLEAR_BIT(SFIOR, 5);
	CLEAR_BIT(SFIOR, 6);
	CLEAR_BIT(SFIOR, 7);
	/*start conversion*/
	SET_BIT(ADCSRA, ADC_START_CONVERSION_BIT);
	/* enable adc peripheral*/
	SET_BIT(ADCSRA, ADC_ENABLE_BIT);
}

void ADC_Read(u8 channel, u16* ptr){
	/*select channel*/
	ADMUX &= 0xE0;
	ADMUX |= channel;
	/*start conversion*/
	SET_BIT(ADCSRA, ADC_START_CONVERSION_BIT);
	/*block till flag is cleared*/
	while(0 == GET_BIT(ADCSRA, ADC_INTERRUPT_FLAG_BIT)){
		/*NOTHING*/
	}
	/* clear adc flag by setting it*/
	SET_BIT(ADCSRA, ADC_INTERRUPT_FLAG_BIT);
	/*pass data to pointer*/
	*ptr = ADC;
}

void ADC_Result(u8 channel,s32 min_ref_value, s32 max_ref_value, f32* flt_result){
	u16 adc_binary_result = 0;
	ADC_Read(channel, &adc_binary_result);
	*flt_result = ( (f32)(max_ref_value-min_ref_value)*adc_binary_result / 1023)+ (f32)min_ref_value;
}

void ADC_Result_LM35(u8 channel, f32* flt_result){
	u16 adc_binary_result = 0;
	ADC_Read(channel, &adc_binary_result);
	*flt_result = adc_binary_result * 5000.0f /1024 /10 ;
}

void ADC_auto_trigger_SelectInt0AndReturnFreeRunning(u8 channel, u16* retVal){
	/*save last channel source*/
	u8 last_ch = (ADMUX & 0x1F)>>5;               //   & 0001 1111
	/*save last auto trigger mode source*/
	u8 last_mode = SFIOR & 0xE0;             // & 1110 0000
	/*select new channel*/
	ADMUX &= 0xE0;
	ADMUX |= channel;
	/*select auto trigger source */
	CLEAR_BIT(SFIOR, 5);
	SET_BIT(SFIOR, 6);
	CLEAR_BIT(SFIOR, 7);
	/*now an automatic start conversion is done by the cpu*/
	/*pass conversion result to pointer*/
	*retVal = ADC;
	/* clear adc flag by setting it*/
	SET_BIT(ADCSRA, ADC_INTERRUPT_FLAG_BIT);
	/*retrieve channel state*/
	ADMUX &= 0xE0;
	ADMUX |= last_ch;
	/*retrieve mode state*/
	SFIOR &= 0x1F;
	SFIOR |= (last_mode<<5);
}

void ADC_Auto_Trigger_Init(u8 channel){
	/*		disable adc peripheral								*/
	CLEAR_BIT(ADCSRA, ADC_ENABLE_BIT);
	
	/*		select reference of adc								*/
	CLEAR_BIT(ADMUX, ADC_REF_SELECT_1);
	SET_BIT(ADMUX, ADC_REF_SELECT_0);
	
	/*		configure right adjustment							*/
	CLEAR_BIT(ADMUX, ADC_LEFT_ADJUST_BIT);
	
	/*		configure prescaler to be 128 16MHz crystal			*/
	SET_BIT(ADCSRA, ADC_PRESCALER_BIT_0);
	SET_BIT(ADCSRA, ADC_PRESCALER_BIT_1);
	SET_BIT(ADCSRA, ADC_PRESCALER_BIT_2);
	
	/*		disable interrupt and clear flag by setting it		*/
	CLEAR_BIT(ADCSRA, ADC_INTERRUPT_ENABLE_BIT);
	SET_BIT(ADCSRA, ADC_INTERRUPT_FLAG_BIT);
	
	/*	select External Interrupt 0 as Auto trigger Source		*/
	CLEAR_BIT(SFIOR, 5);
	SET_BIT(SFIOR, 6);
	CLEAR_BIT(SFIOR, 7);
	/*select channel*/
	ADMUX &= 0xE0;
	ADMUX |= channel;
	
	/*					enable auto trigger						*/
	SET_BIT(ADCSRA, 5);
	
	/*					enable adc peripheral					*/
	SET_BIT(ADCSRA, ADC_ENABLE_BIT);
}

void ADC_Auto_Trigger_Read(volatile u16* retVal){
	/* DO NOT UN COMMENT THE WHILE LOOP BECAUSE THE FLAG SOMETIMES DOESNOT GET TRIGGERED*/
	//while(0 == GET_BIT(ADCSRA, ADC_INTERRUPT_FLAG_BIT)){
		///*NOTHING*/
	//}
	/* clear adc flag by setting it*/
	SET_BIT(ADCSRA, ADC_INTERRUPT_FLAG_BIT);
	/*pass data to pointer*/
	*retVal = ADC;

}