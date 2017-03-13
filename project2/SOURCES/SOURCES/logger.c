/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/12/2017
*
* File : logger.c
* Description : Source file for wrapper logger functions
*               -void log_data(uint8_t * data_TX,uint8_t length_TX)
*               -void log_flush(void)
*               -void log_data_BBB(uint8_t * data_TX,uint8_t length_TX)
*		-void log_string(uint8_t * data_TX)
*               -void log_string_BBB(uint8_t * data_TX)
*		-void log_integer(uint32_t test3,uint8_t length)
*		-void log_integer_BBB(uint32_t test3,uint8_t length)
***************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "circbuff.h"
#include "logger.h"
#include "data.h"
#include "memory.h"
#include "binary_logger.h"


#ifdef FRDM
#include "uart_init.h"
#include "MKL25Z4.h"
#endif


#ifdef BBB
#define UART0_C2 temp
#define UART_C2_TIE_MASK 0
#endif


#ifdef HOST
#define UART0_C2 temp
#define UART_C2_TIE_MASK 0
#endif
uint8_t temp;


/*This function is used as to add data to circular buffer and then transmit through uart
 for FRDM*/
void log_data(uint8_t * data_TX,uint8_t length_TX){

	cbuffer_add(CircBuffT,data_TX,length_TX);
	
	/*Enable the transmit interrupt*/
	UART0_C2 |= UART_C2_TIE_MASK;
}


/*This function is used to block until logger buffer is empty*/
void log_flush(void){
	/*Checks count value to check is buffer is empty*/
	while(CircBuffT->count)
	{
		/*Binary logger for system halted*/
		system_log->logID= SYSTEM_HALTED;
		system_log->LogLength=0;
		log_item(system_log);
	}
}


/*This function is used to add data to circular buffer and then display using printf
 for BBB and host machine*/
void log_data_BBB(uint8_t * data_TX,uint8_t length_TX){
	cbuffer_add(CircBuffT,data_TX,length_TX);
	while(CircBuffT->count){
		printf("%c ",*(CircBuffT->tail));
		cbuffer_remove(CircBuffT,1);
	}
}


/*This function is used to add string to circular buffer and then transmit through uart
 for FRDM*/
void log_string(uint8_t * data_TX){
	uint8_t length=0;

	/*To calculate length of string*/
	while(*data_TX!='\0'){
		length++;
		data_TX++;
	}
	data_TX=data_TX-length;
	cbuffer_add(CircBuffT,data_TX,length);

	/*To enable transmitter interrupt*/
	UART0_C2|=UART_C2_TIE_MASK;
}


/*This function is used to add string to circular buffer and then display using printf
 for BBB and host machine*/
void log_string_BBB(uint8_t * data_TX){
	uint8_t length=0;

	/*To calculate length of string*/
	while(*data_TX!='\0'){
		length++;
		data_TX++;
	}
	data_TX=data_TX-length;
	cbuffer_add(CircBuffT,data_TX,length);
	//CircBuffT->count = CircBuffT->count - 1;
	while(CircBuffT->count){
		printf("%c ",*(CircBuffT->tail));
		cbuffer_remove(CircBuffT,1);
		}
	}


/*This function is used to convert integer to ascii and then add it to circular buffer,
 to transmit through UART for FRDM*/
void log_integer(uint32_t test3,uint8_t length){
	uint32_t base=10;
	uint8_t test[length];
	uint8_t *str=test;
	/*Function to convert integer to ascii*/
	my_itoa((int8_t*)str,test3,base);
	cbuffer_add(CircBuffT,str,length);
	
	/*To enable transmit interrupt*/
	UART0_C2|=UART_C2_TIE_MASK;
}


/*This function is used to convert integer to ascii and then add it to circular buffer,
and display using printf for BBB and host machine*/
void log_integer_BBB(uint32_t test3,uint8_t length){
	uint32_t base=10;
	uint8_t test[length];
	uint8_t *str=test;
	
	/*Function to convert integer to ascii*/
	my_itoa((int8_t *)str,test3,base);
	cbuffer_add(CircBuffT,str,length);

	while(CircBuffT->count){
	printf("%c ",*(CircBuffT->tail));
	cbuffer_remove(CircBuffT,1);
	}

}

