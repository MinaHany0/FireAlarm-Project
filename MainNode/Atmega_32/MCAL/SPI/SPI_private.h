/*
 * SPI_private.h
 *
 * Created: 10/31/2023 3:05:54 PM
 *  Author: Mina
 */ 

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

//#define SPCR	(*(volatile u8*)0x2D)
//typedef enum{
//SPR0 = 0,
//SPR1,
//CPHA,
//CPOL,
//MSTR,
//DORD,
//SPE,
//SPIE,
//}SPCRbits;
//#define SPSR	(*(volatile u8*)0x2E)
//
//typedef enum{
		//= 0,
		//= 6,
	    //= 7,
//}SPSRbits;

typedef union{
	struct{
		u8 SPR0 :1;
		u8 SPR1 :1;
		u8 CPHA :1;
		u8 CPOL :1;
		u8 MSTR :1;
		u8 DORD :1;
		u8 SPE  :1;
		u8 SPIE :1;
		};
		u8 SPCR;
}SPCRRbits_t;

volatile SPCRRbits_t* SPCRbits = ((volatile SPCRRbits_t*)0x2D);

typedef union{
	struct{
		u8 SPI2X	:1;
		u8 RESERVED :5;
		u8 WCOL		:1;
		u8 SPIF		:1;
	};
	u8 SPSR;
}SPSRRbits_t;
volatile SPSRRbits_t* SPSRbits = ((volatile SPSRRbits_t*)0x2E);

volatile u8* SPDR = ((volatile u8*)0x2F);



#endif /* SPI_PRIVATE_H_ */