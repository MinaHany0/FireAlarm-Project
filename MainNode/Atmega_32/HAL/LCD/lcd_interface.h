/*
 * lcd_interface.h
 *
 * Created: 10/21/2023 3:21:45 PM
 *  Author: Mina
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*********************************INCLUDES*************************************************/
#include "../../MCAL/DIO/dio_interface.h"
#include "../../MCAL/GIE/gie_interface.h"
#include "lcd_config.h"
#include "lcd_private.h"

#include <stdio.h>
#include <string.h>
/*********************************MACRO DECLARATIONS***************************************/
#define LCD_CMD_CLEAR_DISPLAY                        0x01
#define LCD_CMD_DISPLAY_OFF	                         0x08
#define LCD_CMD_CURSOR_HOME                          0x02
#define LCD_CMD_ENTRY_MODE_DEC_SHIFT_OFF             0x04
#define LCD_CMD_ENTRY_MODE_DEC_SHIFT_ON              0x05
#define LCD_CMD_ENTRY_MODE_INC_SHIFT_OFF             0x06
#define LCD_CMD_ENTRY_MODE_INC_SHIFT_ON              0x07
#define LCD_CMD_SHIFT_CURSOR_LEFT                    0x10
#define LCD_CMD_SHIFT_CURSOR_RIGHT                   0x14
#define LCD_CMD_DISPLAY_SHIFT_LEFT                   0x18
#define LCD_CMD_DISPLAY_SHIFT_RIGHT                  0x1C
#define LCD_CMD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF  0x0C
#define LCD_CMD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON   0x0D
#define LCD_CMD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF   0x0E
#define LCD_CMD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON    0x0F
#define LCD_CMD_8BIT_MODE_2_LINE                     0x38
#define LCD_CMD_4BIT_MODE_2_LINE                     0x28
/*********************************MACRO FUNCTIONS******************************************/
/*********************************DATA TYPE DEFINITIONS************************************/
/*********************************FUNCTION INTERFACE DECLARATION***************************/

void lcd_init_4bit(void);
void lcd_send_command(u8 command);
void lcd_send_char(u8 chr);
void lcd_send_string(u8* str);
void lcd_send_char_pos(u8 chr, u8 row, u8 col);
void lcd_send_string_pos(u8* str, u8 row, u8 col);
void lcd_send_custom_char(u8* char_arr);

void lcd_convert_u8_to_str (u8  value , u8* str);
void lcd_convert_u16_to_str(u16 value , u8* str);
void lcd_convert_u32_to_str(u32 value , u8* str);
void lcd_convert_f32_to_str(f32 value , u8* str);

#endif /* LCD_INTERFACE_H_ */