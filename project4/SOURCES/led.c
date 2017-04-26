/**********************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/26/2017
*
* File : led.c
* Description : Source file for LED functions
*               -void LEDS_initialize(void)
*               -void RED_LED_set(uint8_t value)
*               -void GREEN_LED_set(uint8_t value)
*				-void LED_Intensity(uint8_t LEDColour, uint16_t Intensity)
***********************************************************************************/


#include "MKL25Z4.h"
#include "stdint.h"
#include "led.h"
#include "gpio.h"

/*Initialized only red LED*/
void LEDS_initialize(void)
{
	/*Enabling clock for port B and D*/
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	/*Initialize GPIO pins for LED*/
	GPIO_led_init();
}


/*Function to check if receiver is working*/
void RED_LED_set(uint8_t value)
{
	if(value){
		/*Sets the prot B pin 18 value to 0*/
		PTB->PCOR = PIN_18;
	}
	else{
		/*Sets the prot B pin 18 value to 1*/
		PTB->PSOR= PIN_18;
	}
}

/*Function to check if receiver is working*/
void GREEN_LED_set(uint8_t value)
{
	if(value){
		/*Sets the prot B pin 18 value to 0*/
		PTB->PCOR = PIN_19;
	}
	else{
		/*Sets the prot B pin 18 value to 1*/
		PTB->PSOR= PIN_19;
	}
}

void LED_Intensity(uint8_t LEDColour, uint16_t Intensity) // Function that actually changes colours and intensity
{
	if(LEDColour == 'R')                       //if the colour is RED
	{

		TPM2->CONTROLS[0].CnV = Intensity; //r
		TPM2->CONTROLS[1].CnV = 0; //g
		TPM0->CONTROLS[1].CnV = 0; //b
	}


	else if (LEDColour == 'G')  //if the colour is GREEN
	{
		TPM2->CONTROLS[0].CnV = 0; //r
		TPM2->CONTROLS[1].CnV = Intensity; //g
		TPM0->CONTROLS[1].CnV = 0; //b
	}

	else if (LEDColour == 'B') //if the colour is BLUE
	{
		TPM2->CONTROLS[0].CnV = 0; //r
		TPM2->CONTROLS[1].CnV = 0; //g
		TPM0->CONTROLS[1].CnV = Intensity; //b
	}

	else if (LEDColour == 'C') //if the colour is CYAN = BLUE+GREEN
	{
		TPM2->CONTROLS[0].CnV = 0; //r
		TPM2->CONTROLS[1].CnV = Intensity; //g
		TPM0->CONTROLS[1].CnV = Intensity; //b

	}

	else if (LEDColour == 'V') //if the colour is VIOLET= RED+BLUE
	{
		TPM2->CONTROLS[0].CnV = Intensity; //r
		TPM2->CONTROLS[1].CnV = 0; //g
		TPM0->CONTROLS[1].CnV = Intensity; //b
	}

	else if (LEDColour == 'Y') //if the colour is YELLOW=RED+GREEN
	{
		TPM2->CONTROLS[0].CnV = Intensity; //r
		TPM2->CONTROLS[1].CnV = Intensity; //g
		TPM0->CONTROLS[1].CnV = 0; //b
	}

	else if (LEDColour == 'W') //if the colour is WHITE=RED+GREEN+BLUE
	{
		TPM2->CONTROLS[0].CnV = Intensity; //r
		TPM2->CONTROLS[1].CnV = Intensity; //g
		TPM0->CONTROLS[1].CnV = Intensity; //b
	}

	else //OFF condition
	{
		TPM2->CONTROLS[0].CnV = 0; //r
		TPM2->CONTROLS[1].CnV = 0; //g
		TPM0->CONTROLS[1].CnV = 0; //b
	}
}
