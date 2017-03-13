* Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include <stdint.h>


/*transmitter*/

void UART_initialize_Tx (void)
{
	SIM_SCGC4 |= 0x00000400;		//provides clock to UART0
	SIM_SOPT2 |= 0x04000000;		//selecting FLL for uart0
	UART0_C2 = 0x00;						//turn off UART0 to disable interrupts
	UART0_BDH =0x00;						//configuring BDH and BDL to set the baud rate
	UART0_BDL =0x17;						//baud rate set to 57600
	UART0_C4 = 0x0f;						//Over Sampling Ratio is set to 16
	UART0_C1 = 0x00;						//Control 1 register is set for 1 stop bit, no parity bit and 8 bit data
	UART0_C2 = 0x08;						//Enabling the transmitter

	SIM_SCGC5 |= 0x00000200;		//enabling clock to port A
	PORTA_PCR2 = 0x0200;				//using PTA2 to be transmitter as ALT 2

}


/*receiver*/
/*void UART_initialize_Rx (void)
{
	SIM_SCGC4 |= 0x00000400;		//provides clock to UART0
	SIM_SOPT2 |= 0x04000000;		//selecting FLL for uart0
	UART0_C2 = 0x00;						//turn off UART0 to disable interrupts
	UART0_BDH =0x00;						//configuring BDH and BDL to set the baud rate
	UART0_BDL =0x17;						//baud rate set to 57600
	UART0_C4 = 0x0f;						//Over Sampling Ratio is set to 16
	UART0_C1 = 0x00;						//Control 1 register is set for 1 stop bit, no parity bit and 8 bit data
	UART0_C2 = 0x04;						//Enabling the receiver

	SIM_SCGC5 |= 0x00000200;		//enabling clock to port A
	PORTA_PCR1 = 0x0200;				//using PTA2 to be transmitter as ALT 2

}*/


/*Initialized only red LED*/
/*void LEDS_initialize(void)
{
	SIM_SCGC5 |= 0x00000400; //enabling clock to port B
	PORTB_PCR18 = 0x100;
    PTB->PDDR |= 0x40000;
    PTB->PSOR = 0x40000;

}*/


/*Function to check if receiver is working*/
/*void LED_set(int value)
{
	if(value){
		PTB->PCOR = 0x40000;
	}
	else{
		PTB->PSOR= 0x40000;
	}
}*/


/*function to send one byte*/
void UART_send_byte(uint8_t data)
{
	while(!(UART0_S1 & 0xC0))
				  {}
		UART0_D = data;

}


/*To transmit n bytes*/
/*void UART_send_nbyte(uint8_t * data_ptr,uint8_t length)
{
	uint8_t i=length;
	while(i){
		while(!(UART0_S1 & 0xC0))
						  {}
		UART0_D=*data_ptr;
		data_ptr++;
		i--;
	}

}*/



/*To receive a single byte*/
/*void UART_receive_byte()
{
	uint8_t c;
		UART_initialize_Rx();
		LEDS_initialize();
		while(!((UART0_S1) & (0x20))){
		}
		c=UART0_D;
		LED_set(c);
}*/

int main(void)
{
	/*to check single byte reception using red led*/
	/*uint8_t c;
	UART_initialize_Rx();
	LEDS_initialize();
	while(!((UART0_S1) & (0x20))){
	}
	c=UART0_D;
	LED_set(c);*/
////////////////////////////////////////////////////////////


	/*to check single byte tranmission*/
    UART_initialize_Tx();
	uint8_t data=0x55;
	UART_send_byte(data);

	//while(!(UART0_S1 & 0xC0))
		//	  {}
	//UART0_D = 'B';*/
/////////////////////////////////////////////////////

	/*To check multiple byte transmission*/
	/*UART_initialize_Tx();
	uint8_t data[]="This is string";
	uint8_t * data_ptr=data;
	uint8_t length=15;
	UART_send_nbyte(data_ptr,length);
	*/
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
