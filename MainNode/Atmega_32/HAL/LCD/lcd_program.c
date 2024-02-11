/*
 * lcd_program.c
 *
 * Created: 10/21/2023 3:21:33 PM
 *  Author: Mina
 */ 

/**************************INCLUDES*******************************************************/
#include "lcd_interface.h"
/**************************STATIC FUNCTION IMPLEMENTATIONS********************************/
static void lcd_void_init_pins			(void);
static void lcd_send_pulse_enable		(void);
/**************************FUNCTION IMPLEMENTATIONS***************************************/
static void lcd_void_init_pins(void){
	/* set the RS , EN , LCD 4 pins as output pins*/
	DIO_void_SetPinDirection ( RS_PORT, RS_PIN, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinDirection ( EN_PORT, EN_PIN, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinDirection ( LCD_BIT7_PORT, LCD_BIT7_PIN, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinDirection ( LCD_BIT6_PORT, LCD_BIT6_PIN, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinDirection ( LCD_BIT5_PORT, LCD_BIT5_PIN, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinDirection ( LCD_BIT4_PORT, LCD_BIT4_PIN, DIO_DIRECTION_OUTPUT);
	
	/* set the RS , EN , LCD 4 pins to low logic*/
	/* pins are default 0 , we clear them in case they were set before in the program*/
	DIO_void_SetPinValue ( RS_PORT, RS_PIN, LOGIC_LOW);
	DIO_void_SetPinValue ( EN_PORT, EN_PIN, LOGIC_LOW);
	DIO_void_SetPinValue ( LCD_BIT7_PORT, LCD_BIT7_PIN, LOGIC_LOW);
	DIO_void_SetPinValue ( LCD_BIT6_PORT, LCD_BIT6_PIN, LOGIC_LOW);
	DIO_void_SetPinValue ( LCD_BIT5_PORT, LCD_BIT5_PIN, LOGIC_LOW);
	DIO_void_SetPinValue ( LCD_BIT4_PORT, LCD_BIT4_PIN, LOGIC_LOW);
}

static void lcd_send_pulse_enable(void){
	DIO_void_SetPinValue ( EN_PORT, EN_PIN, LOGIC_HIGH);
	DIO_void_SetPinValue ( EN_PORT, EN_PIN, LOGIC_LOW);
}

void lcd_send_command(u8 command){
	u8 GIE_state = 0;
	GIE_GetValue(&GIE_state);
	GIE_Disable();
	RS_DIRECTION_COMMAND();
	DIO_void_SetPinValue ( LCD_BIT7_PORT, LCD_BIT7_PIN, (command>>7 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT6_PORT, LCD_BIT6_PIN, (command>>6 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT5_PORT, LCD_BIT5_PIN, (command>>5 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT4_PORT, LCD_BIT4_PIN, (command>>4 & (u8)0x01));
	lcd_send_pulse_enable();
	_delay_us(1520);
	DIO_void_SetPinValue ( LCD_BIT7_PORT, LCD_BIT7_PIN, (command>>3 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT6_PORT, LCD_BIT6_PIN, (command>>2 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT5_PORT, LCD_BIT5_PIN, (command>>1 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT4_PORT, LCD_BIT4_PIN, (command>>0 & (u8)0x01));
	lcd_send_pulse_enable();
	_delay_us(1520);
	GIE_SetValue(GIE_state);
}

void lcd_send_char(u8 chr){
	RS_DIRECTION_DATA();
	DIO_void_SetPinValue ( LCD_BIT7_PORT, LCD_BIT7_PIN, (chr>>7 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT6_PORT, LCD_BIT6_PIN, (chr>>6 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT5_PORT, LCD_BIT5_PIN, (chr>>5 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT4_PORT, LCD_BIT4_PIN, (chr>>4 & (u8)0x01));
	lcd_send_pulse_enable();
	DIO_void_SetPinValue ( LCD_BIT7_PORT, LCD_BIT7_PIN, (chr>>3 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT6_PORT, LCD_BIT6_PIN, (chr>>2 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT5_PORT, LCD_BIT5_PIN, (chr>>1 & (u8)0x01));
	DIO_void_SetPinValue ( LCD_BIT4_PORT, LCD_BIT4_PIN, (chr>>0 & (u8)0x01));
	lcd_send_pulse_enable();
	_delay_us(50);
}

void lcd_send_string(u8* str){
	u8 GIE_state = 0;
	GIE_GetValue(&GIE_state);
	GIE_Disable();
	while(*str){
		lcd_send_char(*(str++));
	}
	GIE_SetValue(GIE_state);
}

void lcd_send_char_pos(u8 chr, u8 row, u8 col){
	u8 GIE_state = 0;
	GIE_GetValue(&GIE_state);
	GIE_Disable();
	col--;
	switch(row){
		case 1: lcd_send_command(0x80 + col); break;
		case 2: lcd_send_command(0xC0 + col); break;
		case 3: lcd_send_command(0x94 + col); break;
		case 4: lcd_send_command(0xD4 + col); break;
	}
	lcd_send_char(chr);
	GIE_SetValue(GIE_state);
	
}

void lcd_send_string_pos(u8* str, u8 row, u8 col){
	u8 GIE_state = 0;
	GIE_GetValue(&GIE_state);
	GIE_Disable();
	col--;
	switch(row){
		case 1: lcd_send_command(0x80 + col); break;
		case 2: lcd_send_command(0xC0 + col); break;
		case 3: lcd_send_command(0x94 + col); break;
		case 4: lcd_send_command(0xD4 + col); break;
	}
	//_delay_ms(5);
	while(*str){
		lcd_send_char(*(str++));
	}
	GIE_SetValue(GIE_state);
}

void lcd_init_4bit(void){
	lcd_void_init_pins();
	_delay_ms(20);
	lcd_send_command(LCD_CMD_8BIT_MODE_2_LINE);
	_delay_ms(5);
	lcd_send_command(LCD_CMD_8BIT_MODE_2_LINE);
	_delay_us(150);
	lcd_send_command(LCD_CMD_8BIT_MODE_2_LINE);
	lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	lcd_send_command(LCD_CMD_CURSOR_HOME);
	lcd_send_command(LCD_CMD_ENTRY_MODE_INC_SHIFT_OFF);
	lcd_send_command(LCD_CMD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
	lcd_send_command(LCD_CMD_4BIT_MODE_2_LINE);
	lcd_send_command(0x80);
	lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
	lcd_send_command(LCD_CMD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
}

void lcd_convert_u8_to_str (u8  value , u8* str){
	memset(str,'\0',4);
	sprintf((s8*)str,"%d",value);
	return;
}

void lcd_convert_u16_to_str(u16 value , u8* str){
	memset(str,'\0',6);
	sprintf((s8*)str,"%d",value);
	return;
}

void lcd_convert_u32_to_str(u32 value , u8* str){
	memset(str,'\0',11);
	sprintf((s8*)str,"%d",value);
	return;
}

void lcd_convert_f32_to_str(f32 value , u8* str){
	memset(str,'\0',11);
	sprintf((s8*)str,"%0.1f",value);
	return;
}

