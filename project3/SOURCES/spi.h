/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/10/2017
*
* File : spi.h
* Description : Header file for SPI functions
*            	-void SPI_init()
*            	-void SPI_read_byte(uint8_t * byte)
*            	-uint8_t SPI_write_byte(uint8_t byte)
*            	-void SPI_send_packet(uint8_t * p, size_t length)
*            	-void SPI_flush()
***************************************************************************/

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_

#include "circbuff.h"

#ifdef FRDM
#include <stdint.h>
#include <stdio.h>
#include <MKL25Z4.h>

/*Global defines for SPI Pins*/
#define SLAVE_SHIFT (1<<6)
#define nrf_chip_enable() 		(GPIOD_PCOR = SLAVE_SHIFT)
#define nrf_chip_disable()		(GPIOD_PSOR = SLAVE_SHIFT)

#define CHIP_SHIFT (1<<5)
#define nrf_transmit_enable()	(GPIOD_PSOR = CHIP_SHIFT)
#define nrf_transmit_disable() 	(GPIOD_PCOR = CHIP_SHIFT)

#define ISR_SHIFT (1<<7)

/************************************************************
* SPI_init() - Function to initialize SPI0 on Port D
*              Set master mode and Baud equal to 1 Mbps
*************************************************************/
void SPI_init();

/************************************************************
* SPI_read_byte() - Function to read a single byte
* uint8_t * byte - Pointer to the location where returned
* 				   data is to be stored
*************************************************************/
void SPI_read_byte(uint8_t * byte);

/************************************************************
* SPI_write_byte() - Function to write a single byte
* uint8_t byte - Data byte to be written
* uint8_t (return) - Value returned after writing DUMMY byte
*************************************************************/
uint8_t SPI_write_byte(uint8_t byte);

/************************************************************
* SPI_send_packet() - Function to send an array of data
* uint8_t * p - Pointer to the data array that is to be sent
* size_t length - Length of the packet
*************************************************************/
void SPI_send_packet(uint8_t * p, size_t length);

/************************************************************
* SPI_flush() - Function to block until transmit buffer is
* 				empty
*************************************************************/
void SPI_flush();

#endif

#endif /* SOURCES_SPI_H_ */
