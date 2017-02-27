#include "MKL25Z4.h"
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

int main(void)
{

    /* Write your code here */
	/*UART_initialize_Tx();
	while(!(UART0_S1 & 0xC0))
			  {}
	UART0_D = 'B';*/

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    /* Never leave main */
    return 0;
}
