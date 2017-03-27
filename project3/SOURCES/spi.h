/*
 * spi.h
 *
 *  Created on: 22-Mar-2017
 *      Author: Virag Gada
 */

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_

#include <stdint.h>
#include <stdio.h>
#include <MKL25Z4.h>
#define SLAVE_SHIFT (1<<6)

#define SLAVE_SELECT_ON		(GPIOD_PSOR = SLAVE_SHIFT)
#define SLAVE_SELECT_OFF	(GPIOD_PCOR = SLAVE_SHIFT)

#define CHIP_SHIFT (1<<5)
#define CHIP_ENABLE			(GPIOD_PSOR = CHIP_SHIFT)
#define CHIP_DISABLE 		(GPIOD_PCOR = CHIP_SHIFT)

#define ISR_SHIFT (1<<7)

/************************************************************
* SPI_init() - Function to initialize SPI0 on Port D
*              Set master mode and Baud equal to
*************************************************************/
void SPI_init();

/************************************************************
* SPI_read_byte() - Function to read a single byte
*
* uint8_t byte - Data byte to be read
*************************************************************/
uint8_t SPI_read_byte();

/************************************************************
* SPI_write_byte() - Function to write a single byte
*
* uint8_t byte - Data byte to be written
*************************************************************/
void SPI_write_byte(uint8_t byte);

/************************************************************
* SPI_send_packet() - Function to send an array of data
*
* uint8_t * p - Pointer to the data array that is to be sent
* size_t length - Length of the packet
*************************************************************/
void SPI_send_packet(uint8_t * p, size_t length);

/************************************************************
* SPI_read_byte() - Function to block until transmit buffer
* 					is empty
*************************************************************/
void SPI_flush();


#endif /* SOURCES_SPI_H_ */
