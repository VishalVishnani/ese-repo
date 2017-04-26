/**************************************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/26/2017
*
* File : timer.c
* Description : Source file for Timer/PWM functions
*               -void init_TPM0()
*               -void init_PWM()
*               -void TPM0_start()
*				-void TPM0_stop()
*               -uint32_t timetaken()
*               -void Profiler_run(void)
***************************************************************************************************/

#include "circbuff.h"
#include "timer.h"
#include "memory.h"
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#ifdef FRDM
#include "MKL25Z4.h"
#include "DMA.h"
#include "uart_init.h"
#include "gpio.h"
#include "led.h"
#endif

struct timeval initial, final;

#define size 			(10)
#define CLOCKTIME 		(0.0477)
#define RESET_VALUE 	(0x00)
#define PRESCALAR 		(0x04)
#define MCGFLLCLK_VAL 	(0x1)
#define LPTPM_INCREMENT (0x1)
#define LPTPM_DISABLE 	(0x0)
#define OVERFLOW_VAL 	(0xFFFF)

#ifdef FRDM

/*Function to initialize TPM0 counter*/
void init_TPM0(){
	/*Clock gate control for TPM0*/
	SIM->SCGC6|=SIM_SCGC6_TPM0_MASK;

	/*selecting MCGFLLCLK as TPM clock source*/
	SIM_SOPT2|=SIM_SOPT2_TPMSRC(MCGFLLCLK_VAL);

	//Clear SC register
	TPM0_SC=RESET_VALUE;

	//Set counter value to 0
	TPM0_CNT=RESET_VALUE; //set counter value to o

	//Setting modulo value
	TPM0_MOD=OVERFLOW_VAL;

	//Set timer overflow flag
	TPM0_SC|=TPM_SC_TOF_MASK;

	//Enable timer overflow interrupt
	TPM0_SC|=TPM_SC_TOIE_MASK;
}

/*Function to initialize PWM*/
void init_PWM(){
	/*Clock gate control for TPM1*/
	SIM->SCGC6|= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK | SIM_SCGC6_TPM1_MASK;

	//USING MCGFLLCLK AS TIMER COUNTER CLOCK for TPM source clock
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(MCGFLLCLK_VAL);

	LEDS_initialize();

	/*Starting the controls for blue led: tpm 0 channel 1:*/
	TPM0_MOD = 1875; //
	TPM0_SC = 0x0000000F; //SETTING PRESCALER TO 128 and CMOD value to 1
	TPM0->CONTROLS[1].CnSC = 0x00000024; //0x20 | 0x04;  // EDGE ALIGNED, PULSE HIGH

	/*Setting Controls for TPM2*/
	TPM2_MOD = 1875; //
	TPM2_SC = 0x0000000F; //SETTING PRESCALER to 128 and CMOD value to 1
	/*Starting the controls for red led: tpm 2 channel 0:*/
	TPM2->CONTROLS[0].CnSC = 0x00000024; //0x20 | 0x04;  // EDGE ALIGNED, PULSE HIGH
	/*Starting the controls for GREEN led: tpm 2 channel 1:*/
	TPM2->CONTROLS[1].CnSC = 0x00000024; //0x20 | 0x04;  // EDGE ALIGNED, PULSE HIGH
}

void TPM0_start(){

	TPM0_CNT=RESET_VALUE;
	//Enable LPTPM counter increments
	TPM0_SC|= TPM_SC_CMOD(LPTPM_INCREMENT);
}

void TPM0_stop(){
	TPM0_SC |= TPM_SC_CMOD(LPTPM_DISABLE);
}

#endif

uint32_t timetaken(){
	uint32_t initial_us,final_us,diff_us;
	initial_us= (uint32_t)initial.tv_sec*1000000 + (uint32_t)initial.tv_usec;
	final_us= (uint32_t)final.tv_sec*1000000 + (uint32_t)final.tv_usec;
	diff_us=final_us-initial_us;
	return diff_us;
}

void Profiler_run(void){

	uint8_t source[size]={0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9};
	uint8_t dest[size];
#ifdef FRDM
	init_TPM0();
	TPM0_start();

	//my_memmove((uint8_t *)&source,(uint8_t*)&dest,(uint32_t)size); //my_memmove
	//my_memset((uint8_t *)&source,(uint32_t)size,(uint8_t) 0); //my_memset
	//memmove((uint8_t*)&dest,(uint8_t*)&source,(uint32_t)size); //std memmove
	//memset((uint8_t*)&source,(uint8_t) 0,(uint32_t) size); //std memset
	//TPM0_stop();
	//((uint8_t*)&source[0],(uint8_t*)&dest[0],(uint32_t) size); // dma -8 bit
	//memmove_dma_halfword((uint16_t*)&source[0],(uint16_t*)&dest[0],(uint32_t) size); // dma-16 bit
	memmove_dma_word((uint32_t*)&source[0],(uint32_t*)&dest[0],(uint32_t) size); // dma-32 bits
	//memzero_dma_byte((uint8_t *)&source, (uint32_t) size); //dma zero -8 bit
	//memzero_dma_halfword((uint16_t *)&source, (uint32_t) size); // dma zero -16bit
	//memzero_dma_word((uint32_t*)source,(uint32_t) size); //dma zero -32 bits

#endif

#ifdef BBB

	struct timeval initial, final;
	gettimeofday(&initial,NULL);

	my_memmove((uint8_t*)&source,(uint8_t*)&dest,(uint32_t)size);//my_memmove
	my_memset((uint8_t *)&source,(uint32_t)size,(uint8_t) 0); //my_memset
	memmove((uint8_t*)&dest,(uint8_t*)&source,(uint32_t)size); //std memmove
	memset((uint8_t*)&source,(uint8_t) 0,(uint32_t) size); //std memset

	gettimeofday(&final,NULL);
	uint32_t diff=0;
	diff=timetaken();

	#endif

}

