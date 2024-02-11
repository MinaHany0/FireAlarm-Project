/*
 * lcd_private.h
 *
 * Created: 10/21/2023 3:22:16 PM
 *  Author: Mina
 */ 


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define RS_DIRECTION_COMMAND()	(DIO_void_SetPinValue ( RS_PORT, RS_PIN, LOGIC_LOW))
#define RS_DIRECTION_DATA()		(DIO_void_SetPinValue ( RS_PORT, RS_PIN, LOGIC_HIGH))



#endif /* LCD_PRIVATE_H_ */