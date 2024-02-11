
/* sev_seg.c
*
* Created: 10/21/2023 9:53:23 AM
*  Author: Mina
*/

#include "sev_seg_interface.h"
#include "sev_seg_config.h"

seg_7_pin_t seg_7_comm_anode[4];
seg_7_pin_t seg_7_decode_pin[4];

static void seg_7_void_pin_init(seg_7_pin_t* _pin, u8 logic_value){
	DIO_void_SetPinDirection( _pin->port, _pin->pin, DIO_DIRECTION_OUTPUT);
	DIO_void_SetPinValue	( _pin->port, _pin->pin, logic_value);
}

void seg_7_void_init(void){
	u8 l_counter = 0 ;
	/*configure all pins as in MCU Kit*/
	seg_7_comm_anode[0].port= PORT_B;
	seg_7_comm_anode[0].pin= PIN_6;
	seg_7_comm_anode[1].port= PORT_B;
	seg_7_comm_anode[1].pin= PIN_5;
	seg_7_comm_anode[2].port= PORT_A;
	seg_7_comm_anode[2].pin= PIN_2;
	seg_7_comm_anode[3].port= PORT_A;
	seg_7_comm_anode[3].pin= PIN_3;

	seg_7_decode_pin[0].port = PORT_B;
	seg_7_decode_pin[0].pin = PIN_0;
	seg_7_decode_pin[1].port = PORT_B;
	seg_7_decode_pin[1].pin = PIN_1;
	seg_7_decode_pin[2].port = PORT_B;
	seg_7_decode_pin[2].pin = PIN_2;
	seg_7_decode_pin[3].port = PORT_B;
	seg_7_decode_pin[3].pin = PIN_4;

	/* initializing all decoder pins to output low (common anode) all work at beginning*/
	for(l_counter = 0; l_counter < 4; l_counter++){
		seg_7_void_pin_init(&(seg_7_decode_pin[l_counter]), LOGIC_LOW);
	}
	/* initializing all 7 segment pins to output high to be ready to write 5 volts on*/
	for(l_counter = 0; l_counter < 4; l_counter++){
		seg_7_void_pin_init(&(seg_7_comm_anode[l_counter]), LOGIC_LOW);
	}
}

void seg_7_void_write_val(u32 val){
		u8 displayed_number = 0;
		
		for(u8 counter = 0; counter < 4; counter++){
			/* sends the number value to the pins of the decoder */
			displayed_number = val % 10;
			DIO_void_SetPinValue( seg_7_decode_pin[0].port, seg_7_decode_pin[0].pin, (displayed_number >> 0) & 0x01 );
			DIO_void_SetPinValue( seg_7_decode_pin[1].port, seg_7_decode_pin[1].pin, (displayed_number >> 1) & 0x01 );
			DIO_void_SetPinValue( seg_7_decode_pin[2].port, seg_7_decode_pin[2].pin, (displayed_number >> 2) & 0x01 );
			DIO_void_SetPinValue( seg_7_decode_pin[3].port, seg_7_decode_pin[3].pin, (displayed_number >> 3) & 0x01 );
			
			/* enables then disables selected seven segment anode pin*/
			DIO_void_SetPinValue( seg_7_comm_anode[3-counter].port, seg_7_comm_anode[3-counter].pin, LOGIC_LOW);
			_delay_ms(4);
			DIO_void_SetPinValue( seg_7_comm_anode[3-counter].port, seg_7_comm_anode[3-counter].pin, LOGIC_HIGH);
			/*divide value by 10 to get next digit*/
			val /=10;
			
		}
		return;
}