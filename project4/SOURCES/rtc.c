/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/12/2017
*
* File : rtc.c
* Description : Source file for RTC initialization functions
*            	-void rtc_init(void)
***************************************************************************/

#include "circbuff.h"

#ifdef FRDM
#include "MKL25Z4.h"
#include "rtc.h"
void rtc_init(void){

	//Enabling clock to Port D
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	//Provide clock to SPI0
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

	//Enable the internal reference clock. MCGIRCLK is active.
	MCG_C1 |= MCG_C1_IRCLKEN_MASK;
	//Select the slow internal reference clock source.
    MCG_C2 &= ~(MCG_C2_IRCS_MASK);
	//Set PTC1 as RTC_CLKIN and select 32 KHz clock source for the RTC module.
	PORTC_PCR1 |= (PORT_PCR_MUX(0x1));
    SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);
	//Set PTC3 as CLKOUT pin and selects the MCGIRCLK clock to output on the CLKOUT pin.
    SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100);
    PORTC_PCR3 |= (PORT_PCR_MUX(0x5));

    //Enable software access and interrupts to the RTC module.
    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

    //Clear all RTC registers.
    RTC_CR = RTC_CR_SWR_MASK;
    RTC_CR &= ~RTC_CR_SWR_MASK;

    if (RTC_SR & RTC_SR_TIF_MASK){
         RTC_TSR = 0x00000000;
    }
    //Set time compensation parameters. (These parameters can be different for each application)
    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

    //Enable seconds interrupt
    RTC_IER |= RTC_IER_TSIE_MASK;

    //Enable time seconds interrupt for the module and enable its irq.
    NVIC_EnableIRQ(RTC_Seconds_IRQn);

    //Write to Time Seconds Register.
    RTC_TSR = TIME_STAMP - ADJUSTMENT; //Epoch Time

    //Enable time counter.
    RTC_SR |= RTC_SR_TCE_MASK;
}

#endif
