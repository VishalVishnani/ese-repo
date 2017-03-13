/************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/08/2017
*
* File : main.c
* Description : Source file for project2
*               -UART0_IRQHandler()
*		-analyse_data()
*               -compile time switches
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuff.h"
#include "logger.h"
#include "binary_logger.h"
#include "data.h"

/*Defining buffer lengths*/
uint8_t length_TXbuff=255;
uint8_t length_RXbuff=16;

/*Compile time switch for BBB*/
#ifdef BBB
	#define UART_initialize()
	#define log_data(data_TX,length_TX) log_data_BBB(data_TX,length_TX)
	#define log_integer(test3,length_TX) log_integer_BBB(test3,length_TX)
	#define log_string(data_TX) log_string_BBB (data_TX)
	#define UART0_C2 (temp)
#endif

/*Compile time switch for HOST*/
#ifdef HOST
	#define UART_initialize()
	#define log_data(data_TX,length_TX) log_data_BBB(data_TX,length_TX)
	#define log_integer(test3,length_TX) log_integer_BBB(test3,length_TX)
	#define log_string(data_TX) log_string_BBB (data_TX)
	#define UART0_C2 (temp)
#endif

/*Compile time switch for FRDM*/
#ifdef FRDM
#include "uart_init.h"
#include "MKL25Z4.h"
#define printf(...)

/*Defining Global Variables*/

uint16_t alphabetCount = 0;
uint16_t numericCount = 0;
uint16_t punctuationCount = 0;
uint16_t miscCount = 0;
uint8_t recievedDataCount = 0;
uint8_t warningString[] = "Buffer is Full\n\r";
uint8_t recieved_data;
uint8_t analyse = 0;

/**********************************************
*Function to analyse recieved data
*It can analyse if data is an alphabet, number,
*punctuation or miscellaneous character
**********************************************/
void analyse_data(){
#ifdef LOG_ON
	uint8_t c = recieved_data;
	/* Check if data is an alphabet, number,
	 * punctuation or a miscellaneous character*/
	if(((c>='a') && (c<='z')) || ((c>='A') && (c<='Z')))
	    alphabetCount++;
	else if ((c>='0') && (c<= '9'))
	    numericCount++;
	else if (c == '.' || c == ',' || c == '\'' || c == ':' || c == ';' || c == '!' || c== '"')
	    punctuationCount++;
	else miscCount++;
	/*From first data we start the analyzing so log that*/
	if(recievedDataCount == 1){
		system_log = create_log_item();
	    system_log->logID = DATA_ANALYSIS_STARTED;
	    system_log->LogLength = 0;
	    log_item(system_log);
	    destroy_log_item(system_log);
	    }
	/*After 16 characters have been received send log info*/
	if(recievedDataCount == 16){
		system_log = create_log_item();
		system_log->logID = WARNING;
		system_log->LogLength = 16;
		system_log->Payload = warningString;
		log_item(system_log);
		/*Send log for Alphabet Count*/
		system_log->logID = DATA_ALPHA_COUNT;
	    if(alphabetCount>9)
	    	system_log->LogLength = 2;
	    else system_log->LogLength = 1;
	    my_itoa((uint8_t*)&alphabetCount,alphabetCount,10);
	    system_log->Payload = (uint8_t*)&alphabetCount;
	    log_item(system_log);
	    alphabetCount=0;

	    /*Send log for Number Count*/
	    system_log->logID = NUMERIC_COUNT;
	    if(numericCount>9)
	       	system_log->LogLength = 2;
	    else system_log->LogLength = 1;
	    my_itoa((uint8_t*)&numericCount,numericCount,10);
	    system_log->Payload = (uint8_t*)&numericCount;
	    log_item(system_log);
	    numericCount=0;

	    /*Send log for Punctuation Count*/
	   	system_log->logID = DATA_PUNCTUATION_COUNT;
	   	if(punctuationCount>9)
 			system_log->LogLength = 2;
	    else system_log->LogLength = 1;
	    my_itoa((uint8_t*)&punctuationCount,punctuationCount,10);
	    system_log->Payload = (uint8_t*)&punctuationCount;
	   	log_item(system_log);
	   	punctuationCount=0;

	   	/*Send log for Miscellaneous character count*/
	    system_log->logID = DATA_MISC_COUNT;
	    if(miscCount>9)
	        system_log->LogLength = 2;
	    else system_log->LogLength = 1;
	    my_itoa((uint8_t*)&miscCount,miscCount,10);
	    system_log->Payload = (uint8_t*)&miscCount;
	   	log_item(system_log);
	   	miscCount = 0;

	   	/*Send log for Analysis Completed*/
	  	system_log->logID = DATA_ANALYSIS_COMPLETED;
	    system_log->LogLength = 0;
	    log_item(system_log);
	    recievedDataCount = 0;
	    cbuffer_remove(CircBuffR,16);
	    destroy_log_item(system_log);
	   }
	analyse = 0;
#endif
}

/***********************************
*Function to handle UART interrupts
************************************/
void UART0_IRQHandler(void){
	__disable_irq();
	/* Check if interrupt is for TX or RX and handle accordingly
	 * For TX interrupt we take the data from TX buffer and
	 * sent it to UART to transmit*/
    if((UART0_C2 & UART0_C2_TIE_MASK)!=0){
	uint8_t data;
	uint16_t i;
	while(CircBuffT->count){
		data=*(CircBuffT->tail);
		UART_send_byte(data);
        cbuffer_remove(CircBuffT,1);
        for (i=1000;i>0;i--);
		}
	/*Disabling TX interrupt bit*/
	log_flush();
	UART0_C2 &= ~UART0_C2_TIE_MASK;
    }

    /* For RX interrupt check add data to the RX buffer and
     * analyse the data to check if it is an alphabet, number,
     * punctuation or a miscellaneous characters*/
	else if(((UART0_C2 & UART0_C2_RIE_MASK)!=0) && ((UART0_S1 & UART0_S1_RDRF_MASK) !=0)){
		uint8_t c= UART_receive_byte();
		recieved_data = c;
    	recievedDataCount++;
    	cbuffer_add(CircBuffR,&c,1);
    	analyse = 1;
    	//analyse_data(c);
    	UART0_C2|=UART_C2_TIE_MASK;
	}
    __enable_irq();
}
#endif

int main()
{
	/*Create log item*/
	system_log = create_log_item();

	/*Create and Initialize Transmit Circular Buffer*/
	CircBuffT = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(CircBuffT->length) = length_TXbuff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_TXbuff);

	CircBuffT->buffer = cbufferT;
	cbuffer_init(CircBuffT);

	UART_initialize();
	#ifdef LOG_ON
		system_log->logID = LOGGER_INITIALIZED;
		log_item(system_log);
		system_log->logID = SYSTEM_INITIALIZED;
		log_item(system_log);
	#endif

	/*Create and Initialize Receiver Circular Buffer*/
    CircBuffR = (CircBuff *) calloc(1,sizeof(CircBuff));
    uint8_t * cbufferR=NULL;
    (CircBuffR->length) = length_RXbuff;
    cbufferR = cbuffer_memoryAllocate(cbufferR,length_RXbuff);
    CircBuffR->buffer = cbufferR;
    cbuffer_init(CircBuffR);

#ifdef LOG_ON

    /*Testing log_data function*/
    uint8_t payload_string1[18] = "Testing log_data\n\r";
	system_log->logID = INFO;
	system_log->LogLength = 18;
	system_log->Payload = payload_string1;
	log_item(system_log);

	uint8_t test1[4]={'1','2','3','4'};
	uint8_t * data_TX = test1;
	uint8_t length_TX=(sizeof(test1)/sizeof(uint8_t));
	log_data(data_TX,length_TX);
	printf("\n");

	/*Testing log_string function*/
	uint8_t payload_string2[20] = "Testing log_string\n\r";
    system_log->logID = INFO;
    system_log->LogLength = 20;
    system_log->Payload = payload_string2;
    log_item(system_log);

    uint8_t test2[]="This is a string";
    data_TX=test2;
    log_string(data_TX);
	printf("\n");

	/*Testing log_integer function*/
	uint8_t payload_string3[21] = "Testing log_integer\n\r";
	system_log->logID = INFO;
	system_log->LogLength = 21;
	system_log->Payload = payload_string3;
	log_item(system_log);

	uint32_t test3=1234;
    length_TX=sizeof((test3)/sizeof(uint8_t));
    log_integer(test3,length_TX);
    printf("\n");
    destroy_log_item(system_log);
    system_log = NULL;
#else
#ifdef HOST
 printf("logging functionality is disabled");
#elif BBB
 printf("logging functionality is disabled");
#else
/*Print when logging is disabled*/
uint8_t string3[34]=" Logging functionality is disabled";
uint8_t *str_ptr=string3;
uint8_t length=0;
uint8_t state;
while(*str_ptr!='\0'){
	length++;
	str_ptr++;
}
str_ptr=str_ptr-length;

state = cbuffer_add(CircBuffT,str_ptr,length);
if(state == NULL_POINTER)
{
uint8_t nullPointerError[] = "NULL Pointer\n\r";
system_log->logID = LOG_ERROR;
system_log->LogLength = 14;
system_log->Payload = nullPointerError;
log_item(system_log);
}

UART0_C2|=UART_C2_TIE_MASK;

#endif
#endif

#ifdef FRDM
while(1){
	/*When UART receives data the variable is set to analyze data*/
	if(analyse == 1){
		analyse_data();
	}
}
#endif

}
