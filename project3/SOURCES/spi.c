/*
 * spi.c
 *
 *  Created on: 22-Mar-2017
 *      Author: Virag Gada
 */

#include <MKL25Z4.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "spi.h"

#define ALT_MODE (0x0000200)


/* Function to initialize SPI0
 * */
void SPI_init(){

	//Enabling clock to Port D
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//Provide clock to SPI0
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	//CE ON by default
	PORTD_PCR5 = PORT_PCR_MUX(1);								 //Set the PTD5 pin multiplexer to GPIO mode
	GPIOD_PCOR |= CHIP_SHIFT;									 //Set the initial output state to low
	GPIOD_PDDR |= CHIP_SHIFT;									// Set the pins direction to output

	//CSN is HIGH by default
	PORTD_PCR6 = PORT_PCR_MUX(1);								 //Set the PTD6 pin multiplexer to GPIO mode
	GPIOD_PSOR |= SLAVE_SHIFT;									 //Set the initial output state to high
	GPIOD_PDDR |= SLAVE_SHIFT;									 //Set the pins direction to output

	//for IRQ from the Spi device
	PORTD_PCR7 = PORT_PCR_MUX(1);								 //Set the PTD7 pin multiplexer to GPIO mode
	GPIOD_PDDR |= ISR_SHIFT;									 //Set the pins direction to input


	//Set as SPI0_PCS0
	PORTD->PCR[0]= ALT_MODE;

	//Set as SPI0_SCK
	PORTD->PCR[1]= ALT_MODE;

	//Set as SPI0_MOSI
	PORTD->PCR[2]= ALT_MODE;

	//Set as SPI0_MISO
	PORTD->PCR[3]= ALT_MODE;

	//Set as Master and SS pin to select slave
	SPI0_C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;

	//Make Master SS pin to select slave output
	SPI0_C2 = SPI_C2_MODFEN_MASK;

	//Set baud rate
	SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x08));

	//Enable SPI0
	SPI0_C1 |= SPI_C1_SPE_MASK;

/*
	SIM->SCGC5 = 0x00000800;			//Clock port C
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;
		//CE ON by default
		PORTC_PCR8 = PORT_PCR_MUX(1);								 Set the PTB8 pin multiplexer to GPIO mode
		GPIOC_PCOR |= 1 << 8;									 Set the initial output state to low
		GPIOC_PDDR |= 1 << 8;									 Set the pins direction to output

		//CSN is HIGH by default
		PORTC_PCR9 = PORT_PCR_MUX(1);								 Set the PTB9 pin multiplexer to GPIO mode
		GPIOC_PSOR |= 1 << 9;									 Set the initial output state to high
		GPIOC_PDDR |= 1 << 9;									 Set the pins direction to output

		//for IRQ from the Spi device
		PORTC_PCR10 = PORT_PCR_MUX(1);								 Set the PTB10 pin multiplexer to GPIO mode
		GPIOC_PDDR |= 1 << 10;									 Set the pins direction to input

		***********************************************************
		PORTC->PCR[4]=0x0000200;			//CS mode
		PORTC->PCR[5]=0X0000200;			//CK
		PORTC->PCR[6]=0x0000200;			//MOSI
		PORTC->PCR[7]=0x0000200;			//MISO

		SPI0_C1 |= 0x12;				//SSOE=1, MSb first
		SPI0_C2 |= 0x10;				//MODFEN=1		SS is automatic output
		SPI0_BR |= 0x60;				//Baud rate is selected


		SPI0_C1 |= 0x40;				//Start the spi  //SPE =1 ie Put spi on
*/

}

uint8_t SPI_read_byte(){

	uint8_t byte;
	while(SPI0->S & SPI_S_SPRF_MASK != SPI_S_SPRF_MASK);
	byte = SPI0->D;
	return byte;
}

void SPI_write_byte(uint8_t byte){

	while((SPI0->S & SPI_S_SPTEF_MASK != SPI_S_SPTEF_MASK));
	SPI0->D = byte;
}

void SPI_send_packet(uint8_t * p, size_t length){

	uint8_t i;
	while(length){
		while(SPI0->S & SPI_S_SPTEF_MASK == SPI_S_SPTEF_MASK);
		SPI0->D = *(p + i);
		length--;
	}
}

void SPI_flush(){

	while(SPI0->S & SPI_S_SPTEF_MASK == SPI_S_SPTEF_MASK);
}
