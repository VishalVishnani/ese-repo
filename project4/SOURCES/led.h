/**********************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/26/2017
*
* File : led.h
* Description : Header file for LED functions
*               -void LEDS_initialize(void)
*               -void RED_LED_set(uint8_t value)
*               -void GREEN_LED_set(uint8_t value)
*				-void LED_Intensity(uint8_t LEDColour, uint16_t Intensity)
***********************************************************************************/
#ifndef SOURCES_LED_H_
#define SOURCES_LED_H_



/*****************************************************************************
* This function is used to initialize RED LED which is port B pin 18
*****************************************************************************/
void LEDS_initialize(void);


/****************************************************************************
*This function is to glow RED LED whenever any character is received through
* UART receiver.
* int value - The value of character received is in this variable
*****************************************************************************/
void RED_LED_set(uint8_t value);

void GREEN_LED_set(uint8_t value);

void LED_Intensity(uint8_t LEDColour, uint16_t Intensity);

#endif /* SOURCES_LED_H_ */
