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

#include "MKL25Z4.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "spi.h"
#include "rtc.h"
#include "data.h"
#include "circbuff.h"
#include "binary_logger.h"
#include "logger.h"
#include "nordic.h"
#include "uart_init.h"
#include <time.h>
#include <sys/time.h>

#define START_CRITICAL() (__disable_irq())
#define END_CRITICAL()   (__enable_irq())

static int i = 0;
uint8_t recieved_data;
uint8_t recievedDataCount = 0;
uint8_t length_TXbuff = 200;
time_t timestamp, result;
clock_t clockval;
uint8_t * txaddr_array;
uint8_t tx_addr_values[5] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE };

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
			data = *(CircBuffT->tail);
			UART_send_byte(data);
			cbuffer_remove(CircBuffT, 1);
			for (i = 1000; i > 0; i--)
				;
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
}

void RTC_Seconds_IRQHandler(void) {

	system_log->Timestamp = RTC_TSR;
}

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
	rtc_init();
	UART_initialize();

	//UART0_D = 0xFF;

	SPI_init();
	nrf_write_config(CONFIG_PWR_UP | CONFIG_PRIM_RX);
	uint8_t value1 = nrf_read_config();

	uint8_t value2 = nrf_read_status();

	nrf_write_TX_ADDR(tx_addr_values);
	txaddr_array = nrf_read_TX_ADDR();

	nrf_write_rf_setup(RF_SETUP_VALUE);
	uint8_t value3 = nrf_read_rf_setup();

	nrf_write_rf_ch(RF_CHANNEL_VALUE);
	uint8_t value4 = nrf_read_rf_ch();

	uint8_t value5 = nrf_read_fifo_status();

	rtc_init();

	while (1) {
	}

	return 0;
}

