/**************************************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/26/2017
*
* File : timer.h
* Description : Source file for Timer/PWM functions
*               -void init_TPM0()
*               -void init_PWM()
*               -void TPM0_start()
*				-void TPM0_stop()
*               -uint32_t timetaken()
*               -void Profiler_run(void)
***************************************************************************************************/
//MCGFLL clock frequency 20.97 MHZ

#include "circbuff.h"
#ifndef SOURCES_TIMER_H_
#define SOURCES_TIMER_H_

#ifdef FRDM

/******************************************************************
* init_TPM0() - This function configures TPM0 counter
******************************************************************/
void init_TPM0();


/******************************************************************
* TPM0_start() - This function starts TPM0 counter
******************************************************************/
void TPM0_start();


/******************************************************************
* TPM0_stop() - This function stops TPM0 counter
******************************************************************/
void TPM0_stop();

/******************************************************************
* init_PWM() - Function to initialize PWM
******************************************************************/
void init_PWM();

#endif


/**********************************************************************
* Profiler_run() - This function starts the profiler to calculate time
* taken by various function
***********************************************************************/
void Profiler_run(void);


/*********************************************************************
* timetaken() - This function calculates difference between initial
* and final time in microseconds
*********************************************************************/
uint32_t timetaken (void);

#endif /* SOURCES_PROFILING_FRDM_H_ */
