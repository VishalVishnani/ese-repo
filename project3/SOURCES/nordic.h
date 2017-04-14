/*
 * nordic.h
 *
 *  Created on: 22-Mar-2017
 *      Author: Virag Gada
 */

#ifndef SOURCES_NORDIC_H_
#define SOURCES_NORDIC_H_

#include <stdint.h>

#define REGISTER_MASK 			(0x1F) //Since first 5 bits are related to register address
#define DUMMY 					(0xFF) //Required to perform a read operation
#define RF_CHANNEL_VALUE 		(0x12) //Set RF channel frequency
#define RF_SETUP_VALUE 			(0x07) //Set 0 dBm RF Tx output, 1 Mbps data rate and LNA gain

/*NRF2401 SPI command defines*/
#define R_REGISTER				(0x00)
#define W_REGISTER				(0x20)
#define R_RX_PAYLOAD			(0x61)
#define W_TX_PAYLOAD			(0xA0)
#define FLUSH_TX				(0xE1)
#define FLUSH_RX				(0xE2)
#define REUSE_TX_PL				(0xE3)
#define ACTIVATE				(0x50)
#define R_RX_PL_WID				(0x60)
#define W_ACK_PAYLOAD			(0xA8)
#define WR__TX_PAYLOAD_NOACK	(0xB0)
#define NOP						(0xFF)

/*NRF2401 Register map*/
#define CONFIG					(0x00)
#define EN_AA					(0x01)
#define EN_RXADDR				(0x02)
#define SETUP_AW				(0x03)
#define SETUP_RETR				(0x04)
#define RF_CH					(0x05)
#define RF_SETUP				(0x06)
#define STATUS					(0x07)
#define OBSERVE_TX				(0x08)
#define CD						(0x09)
#define RX_ADDR_P0				(0x0A)
#define RX_ADDR_P1				(0x0B)
#define RX_ADDR_P2				(0x0C)
#define RX_ADDR_P3				(0x0D)
#define RX_ADDR_P4				(0x0E)
#define RX_ADDR_P5				(0x0F)
#define TX_ADDR					(0x10)
#define RX_PW_P0				(0x11)
#define RX_PW_P1				(0x12)
#define RX_PW_P2				(0x13)
#define RX_PW_P3				(0x14)
#define RX_PW_P4				(0x15)
#define RX_PW_P5				(0x16)
#define FIFO_STATUS				(0x17)
#define DYNPD					(0x1C)
#define FEATURE					(0x1D)

/*CONFIG register bit definitions*/
#define CONFIG_RESERVED			(0x80)
#define	CONFIG_MASK_RX_DR		(0x40)
#define	CONFIG_MASK_TX_DS		(0x20)
#define	CONFIG_MASK_MAX_RT		(0x10)
#define	CONFIG_EN_CRC			(0x08)
#define	CONFIG_CRCO				(0x04)
#define	CONFIG_PWR_UP			(0x02)
#define	CONFIG_PRIM_RX			(0x01)

/*Defining Global Variables*/
uint8_t TX_Addr_Values[5];

/************************************************************
* nrf_write_register() - Write value to the given register
* uint8_t register - Address of the register to write on
* uint8_t value - The value to be written on the register
*************************************************************/
void nrf_write_register(uint8_t reg, uint8_t value);

/************************************************************
* nrf_read_register() - Send the command to read a register
* 						and the register address
* uint8_t register - Address of the register to be read
*************************************************************/
void nrf_read_register(uint8_t reg);

/************************************************************
* nrf_read_status() - Read's the NRF STATUS register
* uint8_t(return)  - Returned value of the STATUS register
*************************************************************/
uint8_t nrf_read_status();

/************************************************************
* nrf_write_config() - Write to the NRF CONFIG register
* uint8_t value - Value to be written to the CONFIG register
*************************************************************/
void nrf_write_config(uint8_t value);

/************************************************************
* nrf_read_config() - Read's to the NRF CONFIG register
* uint8_t(return)  - Returned value of the register
*************************************************************/
uint8_t nrf_read_config();

/************************************************************
* nrf_read_rf_setup() - Read's the NRF RF_SETUP register
* uint8_t(return)  - Returned value of the register
*************************************************************/
uint8_t nrf_read_rf_setup();

/************************************************************
* nrf_write_rf_setup() - Write to the NRF RF_SETUP register
* uint8_t value - Value to be written to the RF_SETUP register
*************************************************************/
void nrf_write_rf_setup(uint8_t value);

/************************************************************
* nrf_read_rf_ch() - Read's the NRF RF_CH and return's
*					 the value
* uint8_t (return) - Returned value of the RF_CH register
*************************************************************/
uint8_t nrf_read_rf_ch();

/************************************************************
* nrf_write_rf_ch() - Writes to the NRF RF_CH register

* uint8_t channel - Value to be written to the RF_CH register
*************************************************************/
void nrf_write_rf_ch(uint8_t channel);

/************************************************************
* nrf_read_TX_ADDR() - Function to read TX_ADDR reg
* uint8_t *(return) - Returned value of the pointer containing
* 					  TX_ADDR reg values
*************************************************************/
uint8_t * nrf_read_TX_ADDR();

/************************************************************
* nrf_write_TX_ADDR() - Function to write to the TX_ADDR reg
* uint8_t * tx_addr - Pointer of the array containing values
*************************************************************/
void nrf_write_TX_ADDR(uint8_t * tx_addr);

/************************************************************
* nrf_read_fifo_status() - Function to read FIFO_STATUS reg
* uint8_t(return) - Returned value of the FIFO_STATUS register
*************************************************************/
uint8_t nrf_read_fifo_status();

/************************************************************
* nrf_flush_tx_fifo() - Function to flush TX FIFO
*************************************************************/
void nrf_flush_tx_fifo();

/************************************************************
* nrf_flush_rx_fifo() - Function to flush RX FIFO
*************************************************************/
void nrf_flush_rx_fifo();

#endif /* SOURCES_NORDIC_H_ */
