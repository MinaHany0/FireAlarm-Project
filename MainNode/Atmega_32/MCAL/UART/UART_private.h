/*
 * UART_private.h
 *
 * Created: 10/30/2023 11:50:52 AM
 *  Author: Mina
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR		(*(volatile u8*) 0x2C)
#define UCSRA	(*(volatile u8*) 0x2B)
#define UCSRB	(*(volatile u8*) 0x2A)
#define UCSRC	(*(volatile u8*) 0x40)
#define UBRRH	(*(volatile u8*) 0x40)
#define UBRRL	(*(volatile u8*) 0x29)

typedef enum{
	MPCM = 0,
	U2X,
	PE,
	DOR,
	FE,
	UDRE,
	TXC,
    RXC,
}UCSRAbits;

typedef enum{
	TXB8 = 0,
	RXB8,
	UCSZ2,
	TXEN,
	RXEN,
	UDRIE,
	TXCIE,
	RXCIE,       
}UCSRBbits;

typedef enum{
	UCPOL = 0,
	UCSZ0,
	UCSZ1,
	USBS,
	UPM0,
	UPM1,
	UMSEL,
	URSEL ,  
}UCSRCbits;
#endif /* UART_PRIVATE_H_ */