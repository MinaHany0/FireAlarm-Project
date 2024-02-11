 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 #define F_CPU 16000000UL
/****************INCLUDES**************************/
#include "MCAL/DIO/dio_interface.h"
#include "MCAL/TIMER0/timer0_interface.h"
#include "MCAL/EXT_INT/ext_int_interface.h"
#include "HAL/LCD/lcd_interface.h"
#include "HAL/LED/led_interface.h"
#include "MCAL/ADC/ADC_interface.h"
/****************MACRO VARIABLES*******************/

/****************GLOBAL VARIABLES******************/
u8 EmptyLine[]= "                    ";
u8 gas_text_std[]   = "NO GAS DETECTED     ";
u8 flame_text_std[] = "NO FLAME DETECTED   ";
u64 GasSensorCounter	= 0;
u64 FlameSensorCounter	= 0;
u16 ADC_value = 0;

u8 temp_str[6];
/****************PROTOTYPES************************/
void GasSensor_InterruptHandler(void);
void FlameSensor_InterruptHandler(void);
void GasSensorPoller_Init(void);
void FlameSensorInterrupt_Init(void);
void fan_normal_mode(void);
void enableAT(void);
void GasSensor_PollerHandler(void);
/****************MAIN FUNCTION*********************/
int main(void){
	ADC_Init();
	
	lcd_init_4bit();
	lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	lcd_send_string_pos(gas_text_std,1,1);
	lcd_send_string_pos(flame_text_std,2,1);
	LED_init(LED_RED_PORT ,LED_RED_PIN );
	LED_init(LED_YELLOW_PORT ,LED_YELLOW_PIN );
	
	DIO_void_SetPinDirection(PORT_A,PIN_7,DIO_DIRECTION_INPUT); // pin for flame;
	DIO_void_SetPinDirection(PORT_B,PIN_5,DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinDirection(PORT_B,PIN_6,DIO_DIRECTION_OUTPUT);
	
	DIO_void_SetPinValue(PORT_B,PIN_5,LOGIC_HIGH);
	DIO_void_SetPinValue(PORT_B,PIN_6,LOGIC_HIGH);
	fan_normal_mode();
	
	FlameSensorInterrupt_Init();
	while(1){
		GasSensorPoller_Init();
		lcd_send_string_pos(gas_text_std,1,1);
		lcd_send_string_pos(flame_text_std,2,1);
		LED_turn_off(LED_RED_PORT ,LED_RED_PIN);
		LED_turn_off(LED_YELLOW_PORT ,LED_YELLOW_PIN);
		
	}
}
/**********HELPER FUNCTIONS************************/

void GasSensorPoller_Init(void){
	/* init gas sensor on external interrupt INT1 */
	if(GET_BIT(PINA,PIN_7)  == 0){
		GasSensor_PollerHandler();
	}
}

void GasSensor_PollerHandler(void){
	/* work the motor on high speed */
	u8 gas_detected[] = "GAS DETECTED        ";
	LED_turn_on(LED_RED_PORT ,LED_RED_PIN);
	lcd_send_string_pos(gas_detected,1,1);
	
	
	TMR0_Set_OCR0_Value(50);
	_delay_ms(1000);
	TMR0_Set_OCR0_Value(200);
	
}

void FlameSensorInterrupt_Init(void){
	/* init gas sensor on external interrupt INT1 */
	
	ext_callback ( FlameSensor_InterruptHandler, EXT_INT_0_INDEX );
	ext_init	 ( EXT_INT_0_INDEX, EXT_INT_ON_FALLING_EDGE);
	GIE_Enable();
}

void FlameSensor_InterruptHandler(void){
	
	/* work the motor on high speed */
	u8 flame_detected[] = "FLAME DETECTED      ";
	LED_turn_on(LED_YELLOW_PORT ,LED_YELLOW_PIN);
	lcd_send_string_pos(flame_detected,2,1);
	
	ADC_auto_trigger_SelectInt0AndReturnFreeRunning(ADC_CHANNEL_1, &ADC_value);
	ADC_value = (u64)ADC_value * 5000ul / 10240;
	lcd_convert_u16_to_str(ADC_value, temp_str);
	lcd_send_string_pos(temp_str,4,10);
	_delay_ms(1000);
	
}

void fan_normal_mode(void){ // function enables pwm on low speed
	DIO_void_SetPinDirection(PORT_B, PIN_3, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue(PORT_B, PIN_3, LOGIC_LOW);
	TMR0_Init();
	
}
