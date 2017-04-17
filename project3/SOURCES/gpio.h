/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/12/2017
*
* File : gpio.h
* Description : Header file for GPIO initialize functions
*               - void GPIO_nrf_init()
*               - void GPIO_led_init()
***************************************************************************/

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_

#define ALT_MODE (0x0000200)

/*Function to initialize gpio pins for NRF module*/
/*********************************************************************
* GPIO_nrf_init() - Function to initialize GPIO pins for NRF module
*
*********************************************************************/
void GPIO_nrf_init();


#define PIN_18	(0x400000)

/*********************************************************************
* GPIO_led_init() - Function to initialize gpio pins for RED LED module
*
*********************************************************************/
void GPIO_led_init();


#endif /* SOURCES_GPIO_H_ */
