#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "RF24.h"
#include "headers/nordic.h"

void nrf_write_config(uint8_t value);
uint8_t nrf_read_config();


#define BBB

//RF24 RF24_cpp(115,117);
//SPI SPI_cpp;


#ifdef BBB
  #define SPI_write_byte(val) call_spi_transfer(&SPI_cpp,val);
  void call_csn_LOW(struct RF24 *p);
  void call_csn_HIGH(struct RF24 *p);
  uint8_t call_spi_transfer(struct SPI *s, uint8_t tx_);
  #define nrf_chip_enable() call_csn_LOW(&RF24_cpp)
  #define nrf_chip_disable() call_csn_HIGH(&RF24_cpp)
#endif


void call_spi_init(struct SPI *s);
uint8_t call_spi_transfer(struct SPI *s, uint8_t tx_);
void call_RF24_begin(struct RF24 *p);
void call_RF24_printDetails(struct RF24 *p);
uint8_t call_get_status(struct RF24 *p);
void call_print_status(struct RF24 *p, uint8_t status);
//void call_csn(SPI *s, int mode);
//void call_csn_LOW(struct RF24 *p);
//void call_csn_HIGH(struct RF24 *p);

/*Function to write to the NRF CONFIG register*/
void nrf_write_config(uint8_t value) {

        nrf_chip_enable();
        uint8_t reg = CONFIG;
        nrf_write_register(reg, value);
        nrf_chip_disable();
}

/*Function to read from NRF CONFIG register*/
uint8_t nrf_read_config() {
        nrf_chip_enable();
        uint8_t value;
        nrf_read_register(CONFIG);
        uint8_t val = DUMMY;
        value = SPI_write_byte(val);
        nrf_chip_disable();
        return value;
}

/*Function to read a NRF register*/
void nrf_read_register(uint8_t reg) {
        uint8_t val = R_REGISTER | (REGISTER_MASK & reg);
        SPI_write_byte(val);
}

/*Function to write to a NRF register*/
void nrf_write_register(uint8_t reg, uint8_t value) {
        nrf_chip_enable();
        uint8_t val = W_REGISTER | (REGISTER_MASK & reg);
        SPI_write_byte(val);
        val = value;
        SPI_write_byte(val);
        nrf_chip_disable();
}

/*Function to read NRF STATUS register*/
uint8_t nrf_read_status() {
        nrf_chip_enable();
        uint8_t value;
        uint8_t val = DUMMY;
        nrf_read_register(STATUS); //Can send NOP as well to read STATUS
        value = SPI_write_byte(val);
        nrf_chip_disable();
        return value;
}
uint8_t nrf_read_rf_setup() {

        uint8_t value;
        nrf_chip_enable();
        nrf_read_register(RF_SETUP);
        value = SPI_write_byte(DUMMY);
        nrf_chip_disable();
        return value;
}

/*Function to write to the NRF RF_SETUP register*/
void nrf_write_rf_setup(uint8_t value){

        uint8_t reg = W_REGISTER | RF_SETUP;
        nrf_chip_enable();
        nrf_write_register(reg, value);
        nrf_chip_disable();
}

/*Function to read from NRF RF_CH register*/
uint8_t nrf_read_rf_ch() {
        nrf_chip_enable();
        uint8_t value;
        nrf_read_register(RF_CH);
        value = SPI_write_byte(DUMMY);
        nrf_chip_disable();
        return value;
}

/*Function to write to the NRF RF_CH register*/
void nrf_write_rf_ch(uint8_t channel) {

        uint8_t reg = W_REGISTER | RF_CH;
        nrf_write_register(reg, channel);
}

/*Function to write to the NRF TX_ADDR register*/
void nrf_write_TX_ADDR(uint8_t * tx_addr) {

        uint8_t reg = W_REGISTER | TX_ADDR;
        uint8_t i;
        nrf_chip_enable();
        SPI_write_byte(W_REGISTER | reg);
        //SPI_send_packet(tx_addr,5);
        nrf_chip_disable();
}

/*Function to read from NRF FIFO_STATUS register*/
uint8_t nrf_read_fifo_status() {
        nrf_chip_enable();
        uint8_t value;
        nrf_read_register(FIFO_STATUS);
        value = SPI_write_byte(DUMMY);
        nrf_chip_disable();
        return value;
}

/*Function to flush TX_FIFO buffer*/
void nrf_flush_tx_fifo() {
        nrf_chip_enable();
        uint8_t val = FLUSH_TX;
        SPI_write_byte(val);
        nrf_chip_disable();
}

/*Function to flush RX_FIFO buffer*/
void nrf_flush_rx_fifo() {
        nrf_chip_enable();
        uint8_t val = FLUSH_RX;
        SPI_write_byte(val);
        nrf_chip_disable();
}



int main(){
    uint8_t status;

    call_RF24_begin(&RF24_cpp); 
  
    nrf_write_config(CONFIG_PWR_UP | CONFIG_PRIM_RX);
    uint8_t configVal = nrf_read_config();
    
    printf("CONFIG %d\n\r",configVal);
    nrf_write_rf_setup(RF_SETUP_VALUE);
    uint8_t rfSetupVal = nrf_read_rf_setup();   
    printf("RF SETUP %d\n\r",rfSetupVal);

    uint8_t statusVal = nrf_read_status();
    printf("STATUS %d\n\r",statusVal);

    uint8_t fifoStatusVal = nrf_read_fifo_status();
    printf("FIFO STATUS %d\n\r",fifoStatusVal);

    nrf_write_rf_ch(RF_CHANNEL_VALUE);
    uint8_t rfChVal = nrf_read_rf_ch();
    printf("RF CH %d\n\r",rfChVal);

    return 1;
}
