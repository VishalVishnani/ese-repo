/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/12/2017
*
* File : uart_init.h
* Description : Header file for UART initialization
*               -void UART_initialize(void)
*               -void LEDS_initialize(void)
*               -void LED_set(int value)
*		-void UART_send_byte(uint8_t data)
*               -void UART_send_nbyte(uint8_t * data_TXptr,uint8_t length)
*		-uint8_t UART_receive Byte()
***************************************************************************/
#ifndef SOURCES_UART_INIT_H_
#define SOURCES_UART_INIT_H_


/*****************************************************************************
* This function is used to initialize for 1 start bit, 8 bit data, 1 stop bit,
* no parity and 57600 baud rate. Port A pin 2 is transmitter and port A pin 1
* is receiver
******************************************************************************/
void UART_initialize(void);


/*****************************************************************************
* This function is used to initialize RED LED which is port B pin 18
*****************************************************************************/
void LEDS_initialize(void);


/****************************************************************************
*This function is to glow RED LED whenever any character is received through
* UART receiver.
* int value - The value of character received is in this variable
*****************************************************************************/
void LED_set(uint8_t value);


/****************************************************************************
*This funcion is used to transmit one byte data through UART tranmsitter
*uint8_t data - The data is to be transmitted is in this variable
*****************************************************************************/
void UART_send_byte(uint8_t data);


/****************************************************************************
*This function is used to send an array of data through UART transmitter
uint8_t * data_TXptr - This points to an array where the data to be transmitted
* is stored
uint8_t length - This gives the length of data to be transmitted
****************************************************************************/
void UART_send_nbyte(uint8_t * data_TXptr,uint8_t length);


/*****************************************************************************
*This function is to receive a single byte through UART receiver and return
* that byte
******************************************************************************/
uint8_t UART_receive_byte();

#endif /* SOURCES_UART_INIT_H_ */
