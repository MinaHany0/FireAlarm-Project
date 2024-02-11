/*
 * EEPROM_Interface.h
 *
 * Created: 7/9/2023 3:59:15 PM
 *  Author: Rizk
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

u8 EEPROM_WRITE_DATA(u16 Address , u8 data);

u8 EEPROM_READ_DATA(u16 Address , u8 * data);



#endif /* EEPROM_INTERFACE_H_ */