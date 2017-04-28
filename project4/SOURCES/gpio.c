/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/27/2017
*
* File : gpio.c
* Description : Source file for GPIO initialize functions
*               - void GPIO_nrf_init()
*               - void GPIO_led_init()
***************************************************************************/

#include "circbuff.h"
#include <stdint.h>

#ifdef FRDM
#include "MKL25Z4.h"
#include "binary_logger.h"
#include "gpio.h"
#include "spi.h"

/*Function to initialize gpio pins for NRF module*/
void GPIO_nrf_init(){

	//Enabling clock to Port D
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//Provide clock to SPI1
	SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;

	//CE ON by default
	PORTD_PCR2 = PORT_PCR_MUX(1);				//Set the PTD2 pin multiplexer to GPIO mode
	GPIOD_PDDR |= CHIP_SHIFT;					// Set the pins direction to output
	GPIOD_PCOR |= CHIP_SHIFT;					//Set the initial output state to low

	//CSN is HIGH by default
	PORTD_PCR3 = PORT_PCR_MUX(1);				//Set the PTD3 pin multiplexer to GPIO mode
	GPIOD_PDDR |= SLAVE_SHIFT;					//Set the pins direction to output
	GPIOD_PSOR |= SLAVE_SHIFT;					//Set the initial output state to high

	//For IRQ from the SPI device
	PORTD_PCR0 = PORT_PCR_MUX(1);				//Set the PTD0 pin multiplexer to GPIO mode
	GPIOD_PDDR |= ISR_SHIFT;					//Set the pins direction to input

	//Set as SPI1_SCK
	PORTD->PCR[5]= ALT_MODE;

	//Set as SPI1_MOSI
	PORTD->PCR[6]= ALT_MODE;

	//Set as SPI1_MISO
	PORTD->PCR[7]= ALT_MODE;

	#ifdef LOG_ON
		/*Binary logger for GPIO_INITIALIZED*/
		system_log->logID = GPIO_INITIALIZED;
		system_log->LogLength = 0;
		system_log->Payload = 0;
		log_item(system_log);
	#endif
}

/*Funcion to initialize RED led*/
void GPIO_led_init(){

	/*Using port D pin 1 (blue LED) as GPIOs*/
	PORTD_PCR1 = PORT_PCR_MUX(0x4);

	/*Using port B pin 18 (red LED) as GPIO*/
	PORTB_PCR18 = PORT_PCR_MUX(0x3);

	/*Using port B pin 19 (green LED) as GPIO*/
	PORTB_PCR19 = PORT_PCR_MUX(0x3);

	/*Setting port B pin 18 as output*/
	//PTB->PDDR |= PIN_18;

	/*Setting port B pin 19 as output*/
	//PTB->PDDR |= PIN_19;

	/*Sets the port B pin 18 value to 1*/
	//PTB->PSOR = PIN_18;

	/*Sets the port B pin 19 value to 1*/
	//PTB->PSOR = PIN_19;




	#ifdef LOG_ON
		/*Binary logger for GPIO_INITIALIZED*/
		system_log->logID = GPIO_INITIALIZED;
		system_log->LogLength = 0;
		system_log->Payload = 0;
		log_item(system_log);
	#endif
}

#endif
