/*
 * gpio.c
 *
 *  Created on: Apr 12, 2017
 *      Author: Virag Gada
 */

#include <stdint.h>
#include "MKL25Z4.h"
#include "gpio.h"
#include "spi.h"

/*Function to initialize gpio pins for NRF module*/
void GPIO_nrf_init(){

	//Enabling clock to Port D
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//Provide clock to SPI0
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	//CE ON by default
	PORTD_PCR5 = PORT_PCR_MUX(1);				//Set the PTD5 pin multiplexer to GPIO mode
	GPIOD_PDDR |= CHIP_SHIFT;					// Set the pins direction to output
	GPIOD_PCOR |= CHIP_SHIFT;					//Set the initial output state to low

	//CSN is HIGH by default
	PORTD_PCR6 = PORT_PCR_MUX(1);				//Set the PTD6 pin multiplexer to GPIO mode
	GPIOD_PDDR |= SLAVE_SHIFT;					//Set the pins direction to output
	GPIOD_PSOR |= SLAVE_SHIFT;					//Set the initial output state to high

	//For IRQ from the SPI device
	PORTD_PCR7 = PORT_PCR_MUX(1);				//Set the PTD7 pin multiplexer to GPIO mode
	GPIOD_PDDR |= ISR_SHIFT;					//Set the pins direction to input

	//Set as SPI0_SCK
	PORTD->PCR[1]= ALT_MODE;

	//Set as SPI0_MOSI
	PORTD->PCR[2]= ALT_MODE;

	//Set as SPI0_MISO
	PORTD->PCR[3]= ALT_MODE;
}
