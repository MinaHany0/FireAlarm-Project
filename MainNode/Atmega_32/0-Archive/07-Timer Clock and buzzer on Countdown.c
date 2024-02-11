 ///*
 //* Created: 10/20/2023 10:59:45 AM
 //*  Author: Mina
 //*/ 
 //
///****************INCLUDES**************************/
//#include "MCAL/TIMER0/timer0_interface.h"
//#include "HAL/LCD/lcd_interface.h"
///****************GLOBAL VARIABLES******************/
//u8 clock_intro[]= "DIGITAL CLOCK";
//u8 str_clock_hours[4];
//u8 str_clock_mins [4];
//u8 str_clock_secs [4];
//u8 str_empty      [9] = "        ";
//u8 no_hours = 23;
//u8 no_mins = 59;
//u8 no_secs = 50;
//u8 Countdown = 10;
///****************PROTOTYPES************************/
//void TMR0_InterruptHandlerFun(void);
//
//int main(void){
	//DIO_void_SetPinDirection(PORT_C, PIN_6,DIO_DIRECTION_OUTPUT); //set buzzer pin output
	//DIO_void_SetPinValue(PORT_C, PIN_6,LOGIC_LOW);
	//lcd_init_4bit();
	//lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	//lcd_send_string_pos(clock_intro, 1, 4);
	//
	//GIE_Enable();
	//TMR0_Callback(TMR0_InterruptHandlerFun);
	//TMR0_Enable_Interrupt();
	//TMR0_Init();
	//while(1)
	//{	}
	//return 0;
//}
//
//void TMR0_InterruptHandlerFun(void){
	//no_secs++;
	//if(60 == no_secs){
		//no_secs = 0;
		//no_mins++;
		//if(60 == no_mins){
			//no_mins = 0;
			//no_hours++;
			//if(24 == no_hours){
				//no_hours = 0;
			//}
		//}
	//}
	//lcd_convert_u8_to_str(no_secs,str_clock_secs);
	//lcd_convert_u8_to_str(no_mins,str_clock_mins);
	//lcd_convert_u8_to_str(no_hours,str_clock_hours);
	//lcd_send_string_pos(str_empty, 2, 1);
	//if(no_hours>9){
		//lcd_send_string_pos(str_clock_hours, 2, 1);
	//}
	//else{
		//lcd_send_char_pos('0',2,1);
		//lcd_send_string_pos(str_clock_hours, 2, 2);
	//}
	//lcd_send_char_pos(':',2,3);
	//if(no_mins>9){
		//lcd_send_string_pos(str_clock_mins, 2, 4);
	//}
	//else{
		//lcd_send_char_pos('0',2,4);
		//lcd_send_string_pos(str_clock_mins, 2, 5);
	//}
	//lcd_send_char_pos(':',2,6);
	//if(no_secs	>9){
		//lcd_send_string_pos(str_clock_secs, 2, 7);
	//}
	//else{
		//lcd_send_char_pos('0',2,7);
		//lcd_send_string_pos(str_clock_secs, 2, 8);
	//}
	//
	//Countdown--;
	//if(Countdown == 0){
		//DIO_void_SetPinValue(PORT_C, PIN_6,LOGIC_HIGH);
	//}
//}


 /*
 * Created: 10/20/2023 10:59:45 AM
 *  Author: Mina
 */ 
 
/****************INCLUDES**************************/
#include "HAL/KEY_PAD/KEYPAD_interface.h"
#include "HAL/LCD/lcd_interface.h"
/****************GLOBAL VARIABLES******************/
u8 pressed_key = 255;
u8 countdown_start[] = "CountDown Seconds ?!";
u8 Thanks[] = "THANK YOU VERY MUCH!";
/****************PROTOTYPES************************/


int main(void){
	KEYPAD_Init();
	lcd_init_4bit();
	lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	lcd_send_string_pos(countdown_start,3,1);
	while(pressed_key != '1'){
		KEYPAD_Read(&pressed_key);
	}
	lcd_send_string_pos(Thanks,3,1);
	while(1)
	{	}
	return 0;
}