/*
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

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "data.h"
#include "circbuff.h"
#include "binary_logger.h"
#include "logger.h"
#include <time.h>
#include <sys/time.h>
#include "Profiling_FRDM.h"

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
#define DMA_DSR_BCR0_DONE (0x01000000)
#define DMA_CLOCK_DISABLE (0x7FFFFFFF)
#define printf(...)
#endif

#define START_CRITICAL() (__disable_irq())
#define END_CRITICAL()   (__enable_irq())

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

void DMA0_IRQHandler(void){
__disable_irq();
#ifdef PROFILER
	TPM0_stop();
#endif

DMA_DCR0 &=DMA_CLOCK_DISABLE;

DMA_DSR_BCR0 |= DMA_DSR_BCR0_DONE;
__enable_irq();
}

void TPM0_IRQHandler(void){
	__disable_irq();
	timer_overflow++;
	TPM0_SC|=TPM_SC_TOF_MASK; //clear TOF flag
	__enable_irq();
}

#endif
int main(void) {

	/*Create log item*/
	system_log = create_log_item();

	/*Create and Initialize Transmit Circular Buffer*/
	CircBuffT = (CircBuff *) calloc(1, sizeof(CircBuff));
	uint8_t * cbufferT = NULL;
	(CircBuffT->length) = length_TXbuff;
	cbufferT = cbuffer_memoryAllocate(cbufferT, length_TXbuff);

	CircBuffT->buffer = cbufferT;
	cbuffer_init(CircBuffT);
	DMA_initialize();
	rtc_init();


#ifdef FRDM

	system_log->Timestamp = RTC_TSR;

	UART_initialize();

	//log_integer(TIME_STAMP,10);

	#ifdef LOG_ON
		system_log->logID = RTC_INITIALIZED;
		log_item(system_log);

		system_log->logID = LOGGER_INITIALIZED;
		log_item(system_log);
	#endif

	SPI_init();

	#ifdef LOG_ON
		system_log->logID = SPI_INITIALIZED;
		log_item(system_log);

		system_log->logID = SYSTEM_INITIALIZED;
		log_item(system_log);
	#endif

	//Write  and read to NRF CONFIG register
	#ifdef LOG_ON
		uint8_t payload_string1[21] = " Testing CONFIG R/W\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 21;
		system_log->Payload = payload_string1;
		log_item(system_log);
	#endif

	nrf_write_config(CONFIG_PWR_UP | CONFIG_PRIM_RX);
	uint8_t configVal = nrf_read_config();
	log_string("CONFIG Value: ");
	log_integer((uint32_t)configVal,2);
	log_string("\n\r");

	//Read NRF STATUS register
	#ifdef LOG_ON
		uint8_t payload_string2[19] = " Testing STATUS R\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 19;
		system_log->Payload = payload_string2;
		log_item(system_log);
	#endif

	uint8_t statusVal = nrf_read_status();
	log_string("STATUS Value: ");
	log_integer((uint32_t)statusVal,2);
	log_string("\n\r");

	//Write and Read to NRF TX ADDR register
	#ifdef LOG_ON
		uint8_t payload_string3[22] = " Testing TX ADDR R/W\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 22;
		system_log->Payload = payload_string3;
		log_item(system_log);
	#endif

	nrf_write_TX_ADDR(tx_addr_values);
	txaddr_array = nrf_read_TX_ADDR();

	for(i=0;i<5;i++){
		log_integer((uint32_t)txaddr_array[i],3);
		log_string(" ");
	}

	//Write and Read to NRF RF SETUP register
	#ifdef LOG_ON
		uint8_t payload_string4[23] = " Testing RF SETUP R/W\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 23;
		system_log->Payload = payload_string4;
		log_item(system_log);
	#endif

	nrf_write_rf_setup(RF_SETUP_VALUE);
	uint8_t rdSetupVal = nrf_read_rf_setup();
	log_string("RF SETUP Value: ");
	log_integer((uint32_t)rdSetupVal,2);
	log_string("\n\r");

	//Write and Read to NRF RF CH register
	#ifdef LOG_ON
		uint8_t payload_string5[20] = " Testing RF CH R/W\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 20;
		system_log->Payload = payload_string5;
		log_item(system_log);
	#endif

	nrf_write_rf_ch(RF_CHANNEL_VALUE);
	uint8_t rfChVal = nrf_read_rf_ch();
	log_string("RF CH Value: ");
	log_integer((uint32_t)rfChVal,2);
	log_string("\n\r");

	//Read NRF FIFO STATUS register
	#ifdef LOG_ON
		uint8_t payload_string6[24] = " Testing FIFO STATUS R\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 24;
		system_log->Payload = payload_string6;
		log_item(system_log);
	#endif

	uint8_t fifoStatusVal = nrf_read_fifo_status();
	log_string(" FIFO STATUS Value: ");
	log_integer((uint32_t)fifoStatusVal,2);
	log_string("\n\r");

#endif

#ifdef PROFILER

	#ifdef LOG_ON
		uint8_t payload_string7[19] = " Testing Profiler\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 19;
		system_log->Payload = payload_string7;
		log_item(system_log);
	#endif

	uint8_t test2[]="Time for 10 bytes by 32-bit DMA memmove in microseconds is ";

	uint8_t * data_TX = test2;
	Profiler_run();
	log_string(data_TX);
	uint32_t counter_value=0;
	counter_value= TPM0_CNT * CLOCKTIME;
	log_integer(counter_value,3);

#endif

#ifdef EXTRA_CREDIT

	#ifdef LOG_ON
		uint8_t payload_string8[23] = " Testing Extra Credit\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 23;
		system_log->Payload = payload_string8;
		log_item(system_log);
	#endif

	uint8_t test1[4]={31,32,33,34};
	uint8_t * data_TX1 = test1;
	uint8_t length_TX=(sizeof(test1)/sizeof(uint8_t));

	for(i=0;i<5;i++){
			log_integer((uint32_t)test1[i],2);
			log_string(" ");
		}
	//log_integer(data_TX1,length_TX);
	uint8_t test3[]="This is a string.";
	data_TX1=test3;

	log_string(data_TX1);
#endif
	cbuff_state value6 = inline_cbuffer_full(CircBuffT);

	while (1) {
	}

	return 0;
}

