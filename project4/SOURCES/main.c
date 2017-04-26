/*********************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/26/2017
* File : main.c
*********************************************************/

#include "MKL25Z4.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "data.h"
#include "circbuff.h"
#include "binary_logger.h"
#include "logger.h"
#include "led.h"
#include <time.h>
#include <sys/time.h>
#include "timer.h"

/*Compile time switch for BBB*/
#ifdef BBB
	#define UART_initialize()
    #define DMA_initialize()
	#define rtc_init()
	#define SPI_init()
	#define log_data(data_TX,length_TX) log_data_BBB(data_TX,length_TX)
	#define log_integer(test3,length_TX) log_integer_BBB(test3,length_TX)
	#define log_string(data_TX) log_string_BBB (data_TX)
	#define UART0_C2 (temp)
#endif

/*Compile time switch for HOST*/
#ifdef HOST
	#define UART_initialize()
	#define rtc_init()
	#define SPI_init()
	#define log_data(data_TX,length_TX) log_data_BBB(data_TX,length_TX)
	#define log_integer(test3,length_TX) log_integer_BBB(test3,length_TX)
	#define log_string(data_TX) log_string_BBB (data_TX)
	#define UART0_C2 (temp)
#endif

#ifdef FRDM
#include "MKL25Z4.h"
#include "DMA.h"
#include "uart_init.h"
#include "spi.h"
#include "rtc.h"
#include "nordic.h"
#include "led.h"
#define printf(...)
#endif


uint8_t timer_overflow=0;
static uint8_t i = 0;
uint8_t recieved_data;
uint8_t recievedDataCount = 0;
#define length_TXbuff (200)
#define CLOCKTIME (0.047)

#ifdef FRDM
uint8_t * txaddr_array;
uint8_t tx_addr_values[5] = { 55, 66, 77, 88, 99 };

/***********************************
 *Function to handle UART interrupts
 ************************************/
void UART0_IRQHandler(void) {
	START_CRITICAL();
	/* Check if interrupt is for TX or RX and handle accordingly
	 * For TX interrupt we take the data from TX buffer and
	 * sent it to UART to transmit*/
	if ((UART0_C2 & UART0_C2_TIE_MASK) != 0) {
		uint8_t data;
		uint16_t i;
		while (CircBuffT->count) {
		#ifdef EXTRA_CREDIT
			memmove_dma_byte_uart((CircBuffT->tail),&(UART0_D),(uint32_t) 1);
		#else
			data = *(CircBuffT->tail);
			UART_send_byte(data);
		#endif
			cbuffer_remove(CircBuffT, 1);
			for (i = 1000; i > 0; i--);
		}
		/*Disabling TX interrupt bit*/
		log_flush();
		UART0_C2 &= ~UART0_C2_TIE_MASK;
	}

	/* For RX interrupt check add data to the RX buffer and
	 * analyse the data to check if it is an alphabet, number,
	 * punctuation or a miscellaneous characters*/
	else if (((UART0_C2 & UART0_C2_RIE_MASK) != 0)
			&& ((UART0_S1 & UART0_S1_RDRF_MASK) != 0)) {
		uint8_t c = UART_receive_byte();
		recieved_data = c;
		recievedDataCount++;
		cbuffer_add(CircBuffR, &c, 1);
		UART0_C2 |= UART_C2_TIE_MASK;
	}
	END_CRITICAL();
}

/******************************************
 *Function to handle RTC Seconds interrupts
 ******************************************/
void RTC_Seconds_IRQHandler(void) {
	START_CRITICAL();
#ifdef LOG_ON
	log_string("\n\r");
	system_log->Timestamp = RTC_TSR;
	system_log->logID = HEARTBEAT;
	system_log->LogLength = 0;
	system_log->Payload = 0;
	log_item(system_log);
#endif
	END_CRITICAL();
}

/************************************
 *Function to handle DMA0 interrupts
 ************************************/
void DMA0_IRQHandler(void){
__disable_irq();
#ifdef PROFILER
	TPM0_stop();
#endif

DMA_DCR0 &=0x7FFFFFFF;
DMA_DSR_BCR0 |= 0x01000000;
__enable_irq();
}

/************************************
 *Function to handle TPM0 interrupts
 ************************************/
void TPM0_IRQHandler(void){
	__disable_irq();
	timer_overflow++;
	TPM0_SC|=TPM_SC_TOF_MASK; //clear TOF flag
	__enable_irq();
}

#endif

int main(void)
{
	//LEDS_initialize();

	//RED_LED_set(1);
	//GREEN_LED_set(1);
	init_PWM();

	//NVIC_SystemReset();
	LED_Intensity('W',1);

	while(1);
    return 0;
}

