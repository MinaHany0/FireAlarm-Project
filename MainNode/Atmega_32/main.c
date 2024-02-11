
 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 

/****************INCLUDES**************************/

#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/EXT_INT/ext_int_interface.h"
#include "MCAL/TIMER0/timer0_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "MCAL/SPI/SPI_interface.h"
#include "HAL/LCD/lcd_interface.h"
#include "HAL/LED/led_interface.h"

/****************MACRO VARIABLES*******************/

#define TEMP_CHANNEL			ADC_CHANNEL_1
#define FLAME_EXT_INT_0			EXT_INT_0_INDEX

#define GAS_SENSOR_PORT			PORT_A
#define GAS_SENSOR_PIN			PIN_7

#define LOW_PWM					150
#define HIGH_PWM				250

#define GAS_NO_FLAME_NO			1
#define GAS_NO_FLAME_YES		2
#define GAS_YES_FLAME_NO		4
#define GAS_YES_FLAME_YES		8

/****************GLOBAL VARIABLES******************/

volatile u16 Temp_ADC_val	= 0;
u8 gas_text_std[]   =	"NO GAS DETECTED    ";
u8 gas_detected[]	=	"GAS DETECTED       ";
u8 flame_text_std[] =	"NO FLAME DETECTED   ";
u8 flame_detected[] =	"FLAME DETECTED      ";
u8 temp_std[]		=	"Temp value is ";
u8 temp_reading[6];
u64 IsModeNormal		= 0;
u8 motor_HS_flag = 0;
volatile u8 rec = 0;
u8 BT_text_std[] =	"FIRE ALARM IS ";
u8 BT_text_1[] = "MANUAL";
u8 BT_text_2[] = "AUTO  ";

volatile u8 Gas_State = 0;
volatile u8 Flame_state = 0;
volatile u8 SPI_Sender_Flag = 0;

volatile u8 SPI_Counter = 'A';
/**********HELPER FUNCTIONS************************/

void GasSensor_Init(void);

void GasSensor_PollerHandler(void);

void GasSensor_Poll(void);

void FLAME_INT_EXT_InterruptHandler(void);

void APP_Init(void);

u8 IsAnySensorActive(void);

void FanLowSpeed (void);

void FanHighSpeed (void);

void UART_RX_InterruptHandlerr(void);

void EXT_INT1_Int_Handler(void);
/****************MAIN FUNCTION*********************/

int main(void){
	
	APP_Init();
	
	while(1)
	{	SPI_Sender_Flag = 0;
		GasSensor_Poll();
		if( IsAnySensorActive() ){}
		else{
			if(IsModeNormal < 100000){
				IsModeNormal++;
			}
			else if(IsModeNormal == 100000){
				SPI_Sender_Flag = 0;
				Gas_State = 0;
				Flame_state = 0;
				BUZZER_turn_off();
				LED_turn_off(LED_BLUE_PORT,LED_BLUE_PIN);
				LED_turn_off(LED_YELLOW_PORT,LED_YELLOW_PIN);
				LED_turn_on(LED_GREEN_PORT ,LED_GREEN_PIN);
				lcd_send_string_pos(gas_text_std,1,1);
				lcd_send_string_pos(flame_text_std,2,1);
				FanLowSpeed();
				motor_HS_flag = 0;
				IsModeNormal++;
			}
			else{
				SPI_Sender_Flag = 0;
			}
		}
	}
	return 0;
}

void APP_Init(void){
	LED_init(LED_YELLOW_PORT ,LED_YELLOW_PIN );
	LED_init(LED_GREEN_PORT ,LED_GREEN_PIN );
	LED_init(LED_BLUE_PORT ,LED_BLUE_PIN );
	BUZZER_init();
	GasSensor_Init();
	lcd_init_4bit();
	ext_init(FLAME_EXT_INT_0,FLAME_INT_EXT_InterruptHandler,EXT_INT_ON_FALLING_EDGE);
	ext_init(EXT_INT_1_INDEX, EXT_INT1_Int_Handler,EXT_INT_ON_FALLING_EDGE);
	ADC_Auto_Trigger_Init(TEMP_CHANNEL);
	TMR0_Enable_Interrupt();
	TMR0_Init();
	UART_RX_Callback(UART_RX_InterruptHandlerr);
	UART_Init(9600);
	SPI_Master_Init();
	lcd_send_string_pos(BT_text_std,3,1);
	lcd_send_string_pos(BT_text_1,3,15);
	GIE_Enable();
	


	LED_turn_on(LED_GREEN_PORT ,LED_GREEN_PIN);
	lcd_send_string_pos(gas_text_std,1,1);
	lcd_send_string_pos(flame_text_std,2,1);
	FanLowSpeed();
}

void GasSensor_Init(void){
	DIO_void_SetPinDirection(GAS_SENSOR_PORT,GAS_SENSOR_PIN, DIO_DIRECTION_INPUT);
	DIO_void_SetPinValue	(GAS_SENSOR_PORT,GAS_SENSOR_PIN, LOGIC_HIGH			);
}

void GasSensor_PollerHandler(void){
	Gas_State = 1;
	lcd_send_string_pos(gas_detected,1,1);
	LED_turn_on(LED_YELLOW_PORT,LED_YELLOW_PIN);
	LED_turn_off(LED_GREEN_PORT,LED_GREEN_PIN);
	FanHighSpeed();
	IsModeNormal = 1;
}

void GasSensor_Poll(void){
	if(0 == DIO_void_GetBitValue(GAS_SENSOR_PORT, GAS_SENSOR_PIN)){
		GasSensor_PollerHandler();
	}
}

void FLAME_INT_EXT_InterruptHandler(void){
	Flame_state = 1;
	LED_turn_on(LED_BLUE_PORT,LED_BLUE_PIN);
	lcd_send_string_pos(flame_detected,2,1);
	ADC_Auto_Trigger_Read(&Temp_ADC_val);
	Temp_ADC_val = Temp_ADC_val * 5000.0f / 10230;
	lcd_convert_u16_to_str(Temp_ADC_val,temp_reading);
	lcd_send_string_pos(temp_std,4,1);
	IsModeNormal = 1;
	BUZZER_turn_on();
	LED_turn_off(LED_GREEN_PORT,LED_GREEN_PIN);
	lcd_send_string_pos(temp_reading,4,16);
	
}

u8 IsAnySensorActive(void){
	if(
		0 == DIO_void_GetBitValue(INT0_PORT		 ,INT0_PIN		)
	||	0 == DIO_void_GetBitValue(GAS_SENSOR_PORT,GAS_SENSOR_PIN)){
		return 1;
	}
	else{
		return 0;
	}
}

void FanLowSpeed (void){
	TMR0_Set_OCR0_Value(LOW_PWM);
}

void FanHighSpeed (void){
	if(motor_HS_flag == 0){	
		TMR0_Set_OCR0_Value(HIGH_PWM);
		motor_HS_flag = 1;
	}
}

void UART_RX_InterruptHandlerr(void){
	UART_Recieve(&rec);
	if(rec == 'L'){
		
		lcd_send_string_pos(BT_text_1,3,15);
	}
	else if(rec == 'R'){
		
		lcd_send_string_pos(BT_text_2,3,15);
	}
	else{}
}

u8 test_spi = 0;

void EXT_INT1_Int_Handler(void){
	
	if(0 == SPI_Sender_Flag){
		if(Gas_State == 0 && Flame_state == 0){
			SPI_Transmit(GAS_NO_FLAME_NO);
		}
		else if(Gas_State == 0 && Flame_state == 1){
			SPI_Transmit(GAS_NO_FLAME_YES);
		}
		else if(Gas_State == 1 && Flame_state == 0){
			SPI_Transmit(GAS_YES_FLAME_NO);
		}
		else if(Gas_State == 1 && Flame_state == 1){
			SPI_Transmit(GAS_YES_FLAME_YES);
		}
		
		
		lcd_send_char_pos(SPI_Counter,1,20);
		SPI_Counter++;	
		
		SPI_Sender_Flag++;
	}
}
