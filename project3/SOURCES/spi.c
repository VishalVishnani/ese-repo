/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/10/2017
*
* File : spi.h
* Description : Source file for SPI functions
*            	-void SPI_init()
*            	-void SPI_read_byte(uint8_t * byte)
*            	-uint8_t SPI_write_byte(uint8_t byte)
*            	-void SPI_send_packet(uint8_t * p, size_t length)
*            	-void SPI_flush()
***************************************************************************/

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

#include <time.h>

#define ADJUSTMENT (21580)

uint8_t * c_time_string;

/*******************************************
* SPI_init() - Function to initialize RTC
********************************************/
void rtc_init(void);

#endif /* SOURCES_RTC_H_ */


#include <MKL25Z4.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "spi.h"
#include "gpio.h"

/* Function to initialize SPI0 */
void SPI_init(){

	GPIO_nrf_init();

	//Set as Master
	SPI0_C1 = SPI_C1_MSTR_MASK;

	//Make Master SS pin to select slave output
	SPI0_C2 = SPI_C2_MODFEN_MASK;

	//Set baud rate
	SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x01)); //Set Bitrate to 1Mbps

	//Enable SPI0
	SPI0_C1 |= SPI_C1_SPE_MASK;
}

/*Function to read a byte using SPI*/
void SPI_read_byte(uint8_t * byte){
	while(!(SPI0->S & SPI_S_SPRF_MASK));
	*byte = SPI0->D;
}

/*Function to write a byte using SPI*/
uint8_t SPI_write_byte(uint8_t byte){
	uint8_t val;
	//while(!(SPI0->S & SPI_S_SPTEF_MASK));
	SPI_flush();
	SPI0->D = byte;
	SPI_read_byte(&val);
	return val;
}

/*Function to write an array of data using SPI*/
void SPI_send_packet(uint8_t * p, size_t length){

	size_t i=length;
	while(i){
		SPI_write_byte(*(p + length-i));
		i--;
	}
}

/*Function to block till SPI transmit buffer is empty*/
void SPI_flush(){
	while(!(SPI0->S & SPI_S_SPTEF_MASK));
}
