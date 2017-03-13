/******************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/12/2017
*
* File : uart_init.c
* Description : Source file for UART initialization
*               -void UART_initialize(void)
*               -void LEDS_initialize(void)
*               -void LED_set(int8_t value)
*		-void UART_send_byte(uint8_t data)
*               -void UART_send_nbyte(uint8_t * data_TXptr,uint8_t length)
*		-uint8_t UART_receive Byte()
******************************************************/

#include "circbuff.h"
#include <stdio.h>

#ifdef FRDM
#include "MKL25Z4.h"
#include <stdint.h>
#include "uart_init.h"
#include "logger.h"
#include "binary_logger.h"

uint16_t i = 0;
#define MCGFLLCLK 0x04000000
#define OSR16 0x0F
#define BDH_BAUD_VALUE 0x00
#define BDL_BAUD_57600 0x17


void UART_initialize(void)
{
	/*Provide clock to UART0*/
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;	

	/*Selecting MCGFLL clock for UART0*/
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC_MASK & MCGFLLCLK;

	/*Turn Off UART0 to make changes and then enable it */		
	UART0_C2 = 0x00;	

	/*Adjusting values of BDH and BDL to set baud rate as 57600 */
	UART0_BDH = BDH_BAUD_VALUE;			
	UART0_BDL = BDL_BAUD_57600;		

	/*Oversampling ratio is set to 16*/
	UART0_C4 = UART0_C4_OSR_MASK & OSR16;

	/*Control register1 is set for 1 start bit, 8 bit data, 1 stop bit, no parity */
	UART0_C1 = 0x00;					

	/*Enabling the transmitter and receiver and receiver interrupt bit*/
	UART0_C2 = UART0_C2_RE_MASK | UART0_C2_TE_MASK | UART0_C2_RIE_MASK;	
										
	/*Enabling clock to port A*/
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	/*Using port A pin 2 as transmitter and port A pin 1 as receiver */	
	PORTA_PCR2 = 0x0200;				
	PORTA_PCR1 = 0x0200;

#ifdef LOG_ON
	/*Binary logger for GPIO_INITIALIZED*/
	system_log->logID = GPIO_INITIALIZED;
	system_log->LogLength = 0;
	system_log->Payload = 0;
	log_item(system_log);
#endif
	/*Setting 12 bit for UART0 in NVIC*/
	NVIC->ISER[0]|=0x00001000;
}


/*Initialized only red LED*/
void LEDS_initialize(void)
{
	/*Enabling clock for port B*/
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	/*Using port B pin 18 (red LED) as GPIO*/
	PORTB_PCR18 = 0x100;
	
	/*Setting port B pin 18 as output*/
    	PTB->PDDR |= 0x40000;

	/*Sets the port B pin 18 value to 1*/ 
    	PTB->PSOR = 0x40000;
}


/*Function to check if receiver is working*/
void LED_set(int8_t value)
{
	if(value){
		/*Sets the prot B pin 18 value to 0*/
		PTB->PCOR = 0x40000;
	}
	else{
		/*Sets the prot B pin 18 value to 1*/
		PTB->PSOR= 0x40000;
	}
}


/*function to send one byte*/
void UART_send_byte(uint8_t data)
{
	uint16_t i;
	for(i=30000;i>0;i--);

	/*The 8 bit data is send into UART0_D register for transmission through UART*/
	UART0_D = data;
}


/*To transmit n bytes*/
void UART_send_nbyte(uint8_t * data_TXptr,uint8_t length)
{
	uint8_t i=length;
	while(i!=0){
		/*The 8 bit data is send into UART0_D register for transmission through UART*/
		UART0_D=*data_TXptr;
		data_TXptr++;
		i--;
	}
}


/*To receive a single byte*/
uint8_t UART_receive_byte()
{
	uint8_t c;
	
	/*Initialize LEDS, whenever a character is received RED LED glows*/
	LEDS_initialize();
	
	/*The 8 bit data received through UART0 receiver is present in UART0_D register*/
	c=UART0_D;

#ifdef LOG_ON
	/*Binary logger for data recived*/
	system_log = create_log_item();
	system_log->logID = DATA_RECEIVED;
	system_log->LogLength = 1;
	system_log->Payload = &c;
	log_item(system_log);
    	destroy_log_item(system_log);
    	system_log = NULL;
#endif

	LED_set(c);
	return(c);
}

#endif
