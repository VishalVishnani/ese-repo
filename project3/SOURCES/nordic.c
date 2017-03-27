/*
 * nordic.c
 *
 *  Created on: 22-Mar-2017
 *      Author: Virag Gada
 */
#include "spi.h"
#include "nordic.h"

#define DUMMY (0xFF)

/*
 uint8_t nrf_read_register(uint8_t reg){

 uint8_t value=0;
 uint8_t array[2];
 array[0] = R_REGISTER | reg;

 //dummy byte while the MISO writes the data out
 array[1] = DUMMY;

 SPI_send_packet(array,2);
 value = SPI_read_byte();
 return value;
 }*/

void nrf_read_register(uint8_t reg) {

	SPI_write_byte(R_REGISTER | reg);
}

void nrf_write_register(uint8_t reg, uint8_t value) {

	SLAVE_SELECT_OFF;
	SPI_write_byte(W_REGISTER | reg);
	SPI_write_byte(value);
	SLAVE_SELECT_ON;
}

uint8_t nrf_read_status() {

	SLAVE_SELECT_OFF;
	uint8_t value;
	nrf_read_register(STATUS); //Can send NOP as well to read STATUS
	SPI_write_byte(DUMMY);
	value = SPI_read_byte();
	SLAVE_SELECT_ON;
	return value;
}

void nrf_write_config() {

	uint8_t reg = CONFIG;
	uint8_t value = CONFIG_PWR_UP | CONFIG_PRIM_RX;
	nrf_write_register(reg, value);
	CHIP_DISABLE;
}

uint8_t nrf_read_config() {

	SLAVE_SELECT_OFF;
	uint8_t value;
	nrf_read_register(CONFIG);
	SPI_write_byte(DUMMY);
	value = SPI_read_byte();
	SLAVE_SELECT_ON;
	return value;
}

uint8_t nrf_read_rf_setup() {

	uint8_t value;
	SLAVE_SELECT_OFF;
	nrf_read_register(RF_SETUP);
	SPI_write_byte(DUMMY);
	value = SPI_read_byte();
	SLAVE_SELECT_ON;
	return value;
}

void nrf_write_rf_setup() {

	uint8_t reg = W_REGISTER | RF_SETUP;
	//RF Power in -6dbm mode
	uint8_t value = 0x0D;
	nrf_write_register(reg, value);
}

uint8_t nrf_read_rf_ch() {

	SLAVE_SELECT_OFF;
	uint8_t value;
	nrf_read_register(RF_CH);
	SPI_write_byte(DUMMY);
	value = SPI_read_byte();
	SLAVE_SELECT_ON;
	return value;
}

void nrf_write_rf_ch(uint8_t channel) {

	uint8_t reg = W_REGISTER | RF_CH;
	//set the rf channel as 76
	uint8_t value = 0x4C;
	nrf_write_register(reg, value);
}

uint8_t * nrf_read_TX_ADDR() {

	//uint8_t TX_Addr_Values[5];
	SLAVE_SELECT_OFF;
	uint8_t i;
	for(i=0;i<5;i++)
	{
		nrf_read_register(TX_ADDR);
		SPI_write_byte(DUMMY);
		TX_Addr_Values[i] = SPI_read_byte();;
	}
	SLAVE_SELECT_ON;
	return TX_Addr_Values;
}

void nrf_write_TX_ADDR(uint8_t * tx_addr) {

	uint8_t reg = W_REGISTER | TX_ADDR;
	uint8_t i;
	SLAVE_SELECT_OFF;
	SPI_write_byte(W_REGISTER | reg);
	for(i=0;i<5;i++){
		SPI_write_byte(*(tx_addr+i));
	}
	SLAVE_SELECT_ON;
}

uint8_t nrf_read_fifo_status() {

	SLAVE_SELECT_OFF;
	uint8_t value;
	nrf_read_register(FIFO_STATUS);
	SPI_write_byte(DUMMY);
	value = SPI_read_byte();
	SLAVE_SELECT_ON;
	return value;
}

void nrf_flush_tx_fifo() {

	SLAVE_SELECT_OFF;
	SPI_write_byte(FLUSH_TX);
	SLAVE_SELECT_ON;
}

void nrf_flush_rx_fifo() {

	SLAVE_SELECT_OFF;
	SPI_write_byte(FLUSH_RX);
	SLAVE_SELECT_ON;
}
