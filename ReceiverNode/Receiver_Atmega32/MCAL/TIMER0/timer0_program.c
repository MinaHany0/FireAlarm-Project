/*
 * timer0_program.c
 *
 * Created: 10/27/2023 10:38:15 AM
 *  Author: Mina
 */ 
/****************INCLUDES**************************/

#include "timer0_config.h"
#include "timer0_interface.h"
#include "timer0_private.h"
/****************GLOBAL VARIABLES******************/
static volatile u32 TMR0_OverFlowCounter = 0;
/****************PROTOTYPES************************/
#if TIMER0_NORMAL_MODE==TIMER0_WORKING_MODE
	static void (*TMR0_InterruptHandler_Normal)(void) = NULL;
#else
	static void (*TMR0_InterruptHandler_Compare)(void) = NULL;
#endif
/****************Function ************************/

static void TMR0_Select_Mode_Select_Prescaler(timer0_CS_t clock_source){
	if(NO_CLOCK_SOURCE == clock_source){
		CLEAR_BIT(TCCR0, CS00_BIT);
		CLEAR_BIT(TCCR0, CS01_BIT);
		CLEAR_BIT(TCCR0, CS02_BIT);
	}
	else if(CLOCK_NO_PRESCALER == clock_source){
		SET_BIT(TCCR0, CS00_BIT);
		CLEAR_BIT(TCCR0, CS01_BIT);
		CLEAR_BIT(TCCR0, CS02_BIT);
	}
	else if(CLOCK_WITH_PRESCALER_8 == clock_source){
		CLEAR_BIT(TCCR0, CS00_BIT);
		SET_BIT(TCCR0, CS01_BIT);
		CLEAR_BIT(TCCR0, CS02_BIT);
	}
	else if(CLOCK_WITH_PRESCALER_64 == clock_source){
		SET_BIT(TCCR0, CS00_BIT);
		SET_BIT(TCCR0, CS01_BIT);
		CLEAR_BIT(TCCR0, CS02_BIT);
	}
	else if(CLOCK_WITH_PRESCALER_256 == clock_source){
		CLEAR_BIT(TCCR0, CS00_BIT);
		CLEAR_BIT(TCCR0, CS01_BIT);
		SET_BIT(TCCR0, CS02_BIT);
	}
	else if(CLOCK_WITH_PRESCALER_1024 == clock_source){
		SET_BIT(TCCR0, CS00_BIT);
		CLEAR_BIT(TCCR0, CS01_BIT);
		SET_BIT(TCCR0, CS02_BIT);
	}
	/***********CONTINUE LATER***************/
}

#if  TIMER0_CTC_MODE==TIMER0_WORKING_MODE
static void TMR0_CTC_SelectCompareMatchOutput(timer0_CTC_CMO_t _compare_match_output){
	if(_compare_match_output == NORMAL_OC0_DISCONNECTED){
		CLEAR_BIT(TCCR0, COM00);
		CLEAR_BIT(TCCR0, COM01);
	}
	else if(_compare_match_output == TOGGLE_OC0_ON_COMPARE_MATCH){
		SET_BIT(TCCR0, COM00);
		CLEAR_BIT(TCCR0, COM01);
	}
	else if(_compare_match_output == CLEAR_OC0_ON_COMPARE_MATCH){
		CLEAR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
	}
	else if(_compare_match_output == SET_OC0_ON_COMPARE_MATCH){
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
	}
	else{/*NOTHING*/}
}
#endif

#if  TIMER0_FAST_PWM==TIMER0_WORKING_MODE || TIMER0_PWM_PHASE_CORRECT==TIMER0_WORKING_MODE
static void TMR0_PWM_SelectCompareMatchOutput(timer0_PWM_CMO_t _PWM__OUTPUT_MODE){
	if(_PWM__OUTPUT_MODE == NO_ACTION_OC0_DISCONNECTED){
		CLEAR_BIT(TCCR0, COM00);
		CLEAR_BIT(TCCR0, COM01);
	}
	else if(_PWM__OUTPUT_MODE == PULSE_NON_INVERTED_HIGH_START_CLEAR_OC0){
		CLEAR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
	}
	else if(_PWM__OUTPUT_MODE == PULSE_INVERTED_LOW_START_SET_OC0){
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
	}
	else{/*NOTHING*/}
}
#endif

void TMR0_Init(void){
	#if TIMER0_NORMAL_MODE==TIMER0_WORKING_MODE
		/*Waveform Generation Mode Selection*/
		CLEAR_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		/*put initial tmr0 reg value*/
		TCNT0 = TIMER0_INITIAL_REG_VALUE;
	#endif	
	#if  TIMER0_CTC_MODE==TIMER0_WORKING_MODE
		/*Waveform Generation Mode Selection*/
		CLEAR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		/*Compare Match Output Mode*/
		TMR0_CTC_SelectCompareMatchOutput(TIMER0_CTC_OUTPUT_MODE); //CFG File
	#if OC0_PIN_OUTPUT_ENABLE	==	OC0_ENABLE
	DIO_void_SetPinDirection(OC0_PORT, OC0_PIN,DIO_DIRECTION_OUTPUT);
	#endif
		/*put initial OCR reg value*/
		OCR0 = TIMER0_INITIAL_OCR_VALUE;
	#endif
	#if  TIMER0_FAST_PWM==TIMER0_WORKING_MODE
		/*Waveform Generation Mode Selection*/
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		/*Compare Output Mode, Fast PWM Mode*/
		TMR0_PWM_SelectCompareMatchOutput(TIMER0_PWM_OUTPUT_MODE); //CFG File
		/*put OCR reg value*/
		OCR0 = TIMER0_PWM_OCR_VALUE;
	#endif
	#if  TIMER0_PWM_PHASE_CORRECT==TIMER0_WORKING_MODE
		/*Waveform Generation Mode Selection*/
		SET_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		/*Compare Match Output Mode*/
		TMR0_PWM_SelectCompareMatchOutput(TIMER0_PWM_OUTPUT_MODE); //CFG File
		/*put OCR reg value*/
		OCR0 = TIMER0_PWM_OCR_VALUE;
	#endif 
		/*Choosing prescaler mode to enable Timer0*/
		TMR0_Select_Mode_Select_Prescaler(TIMER0_PRESCALER_MODE);  //CFG File
}

void TMR0_Disable(void){
	TMR0_Select_Mode_Select_Prescaler(NO_CLOCK_SOURCE);
}

void TMR0_Enable_Interrupt(void){
	#if TIMER0_NORMAL_MODE==TIMER0_WORKING_MODE
		SET_BIT(TIMSK, TOIE0);
	#else
		SET_BIT(TIMSK, OCIE0);
	#endif
}

void TMR0_Clear_Flag_Disabled_Interrupt(void){
	#if TIMER0_NORMAL_MODE==TIMER0_WORKING_MODE
		SET_BIT(TIFR, TOV0);
	#else
		SET_BIT(TIFR, OCF0);
	#endif
}

void TMR0_Callback( void(*ptr)(void) ){
	#if TIMER0_NORMAL_MODE==TIMER0_WORKING_MODE
		TMR0_InterruptHandler_Normal = ptr;
	#else
		TMR0_InterruptHandler_Compare = ptr;
	#endif
}

void TMR0_delay_ms(u64 value){
	/*set gie state to 2 to be neither 1 nor 0*/
	u8 GIE_State = 2;
	/*disable at first*/
	TMR0_Disable();
	/*save GIE state*/
	GIE_GetValue(&GIE_State);
	/*disable GIE*/
	GIE_Disable();
	/*Choosing mode (normal in this case of 0,0)*/
	CLEAR_BIT(TCCR0,3);
	CLEAR_BIT(TCCR0,6);
	/*clear timer0 flag by setting it*/
	SET_BIT(TIFR, TOV0);
	/*put initial tmr0 reg value*/
	TCNT0 = 6;
	/*Choosing prescaler mode to enable Timer0*/
	TMR0_Select_Mode_Select_Prescaler(CLOCK_WITH_PRESCALER_64);
	while(value--){
		/*poll on timer0 flag*/
		while(0 == GET_BIT(TIFR, TOV0));
		/*put initial tmr0 reg value*/
		TCNT0 = 6;
		/*clear timer0 flag by setting it*/
		SET_BIT(TIFR, TOV0);
	}
	TMR0_Disable();	
	GIE_SetValue(GIE_State);
}

void __vector_11() __attribute__((signal));
void __vector_11(){
#if TIMER0_NORMAL_MODE==TIMER0_WORKING_MODE

	GIE_Disable();
	TMR0_OverFlowCounter++;
	if(TIMER0_OVERFLOWS_NEEDED == TMR0_OverFlowCounter){
		if(TMR0_InterruptHandler_Normal){
			TMR0_InterruptHandler_Normal();
		}
		TMR0_OverFlowCounter = 0;
//		TCNT0 = TIMER0_INITIAL_REG_VALUE;
	}
	GIE_Enable();
#endif
}

void __vector_10() __attribute__((signal));
void __vector_10(){
	GIE_Disable();
	#if TIMER0_CTC_MODE==TIMER0_WORKING_MODE
		TMR0_OverFlowCounter++;
		if(TIMER0_OCR_OVERFLOWS_NEEDED <= TMR0_OverFlowCounter){
			if(TMR0_InterruptHandler_Compare){
				TMR0_InterruptHandler_Compare();
			}
			TMR0_OverFlowCounter = 0;
		}
	GIE_Enable();
	#endif	
}

void TMR0_Set_OCR0_Value(u8 value){
	OCR0 = value;
}

void TMR0_Set_TCNT0_Value(u8 value){
	TCNT0 = value;
}