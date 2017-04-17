/**************************************************
* Authors : Vishal Vishnani, Virag Gada

* Date : 04/16/2017
*
* File : profiling_FRDM.c
* Description : Source file for TPM0 configuration
*               -init_TPM0()
*               -TPM0_start()
*               -TPM0_stop()
*               -timetaken()
*               -Profiler_run()
*
***************************************************/
#include "circbuff.h"
#include "Profiling_FRDM.h"
#include "memory.h"
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#ifdef FRDM
#include "MKL25Z4.h"
#include "DMA.h"
#include "uart_init.h"
#endif

#define size (10)
struct timeval initial, final;
#define CLOCKTIME 0.0477
#define RESET_VALUE (0x00)
#define PRESCALAR (0x04)
#define MCGFLLCLK_VAL (0x1)
#define LPTPM_INCREMENT (0x1)
#define LPTPM_DISABLE (0x0)
#define OVERFLOW_VAL (0xFFFF)

#ifdef FRDM

/*function to configure TPM0 counter*/
void init_TPM0(){
	/*Clock gate control for TPM0*/
	SIM->SCGC6|=SIM_SCGC6_TPM0_MASK;

	/*selecting MCGFLLCLK as TPM clock source*/
	SIM_SOPT2|=SIM_SOPT2_TPMSRC(MCGFLLCLK_VAL);

	/*Clear SC register*/
	TPM0_SC=RESET_VALUE;

	/*clear count value*/
	TPM0_CNT=RESET_VALUE;

	/*Setting modulo value*/
	TPM0_MOD=OVERFLOW_VAL;

	/*Clear timer overflow flag*/
	TPM0_SC|=TPM_SC_TOF_MASK;

	/*Enable timer overflow interrupt*/
	TPM0_SC|=TPM_SC_TOIE_MASK;
}


/*function to start timer counter*/
void TPM0_start(){

	/*set count value to 0*/
	TPM0_CNT=RESET_VALUE;

	/*Enable LPTPM counter increment*/
	TPM0_SC|= TPM_SC_CMOD(LPTPM_INCREMENT);
}


/*Function to stop timer counter*/
void TPM0_stop(){

	/*stop the counter*/
	TPM0_SC |= TPM_SC_CMOD(LPTPM_DISABLE);
}

#endif

/*function to calculate time difference in microseconds*/
uint32_t timetaken(){
	uint32_t initial_us,final_us,diff_us;
	initial_us= (uint32_t)initial.tv_sec*1000000 + (uint32_t)initial.tv_usec;
	final_us= (uint32_t)final.tv_sec*1000000 + (uint32_t)final.tv_usec;
	diff_us=final_us-initial_us;
	return diff_us;
}


/*function to start profiler to calculate timer taken by each
 * function for different transfer sizes in microseconds*/
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
//	memzero_dma_byte((uint8_t *)&source, (uint32_t) size); //dma zero -8 bit
//	memzero_dma_halfword((uint16_t *)&source, (uint32_t) size); // dma zero -16bit
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

