/*
 * Profiling_FRDM.c
 *
 *  Created on: Apr 2, 2017
 *      Author: vishal
 */
#include "MKL25Z4.h"

void init_TPM0(){
	/*Clock gate control for TPM0*/
	SIM->SCGC6|=0x01000000;

	/*selecting MCGFLLCLK as TPM clock source*/
	SIM_SOPT2|=0x01000000;
	TPM0_SC=0x0;
	TPM0_CNT=0x0; //set counter value to o
	TPM0_MOD=0xFFFF; //setting modulo value
	TPM0_SC=0x00000080; //enable timer overflow flag

}

void TPM0_start(){
	TPM0_CNT=0x0;
	TPM0_SC|= 0x00000008; //enable LPTPM counter increments
}

void TPM0_stop(){
	TPM0_SC= 0x00000008;
}


