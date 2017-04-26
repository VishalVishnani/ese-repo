/************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/03/2017
*
* File : binary_logger.c
* Description : Source file for binary logger
*               -create_log_item()
*               -log_item()
*               -destroy_log_item()
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuff.h"
#include "binary_logger.h"
#include "logger.h"
#include "data.h"
#include <time.h>
#include <sys/time.h>

/*Compile time switch to include libraries for FRDM*/
#ifdef FRDM
#include "uart_init.h"
#include "MKL25Z4.h"
#include "rtc.h"
#endif

#if defined BBB || defined HOST
	uint8_t * c_time_string;
	struct timeval tv;
	time_t curtime;
	#define log_data(data_TX,length_TX) log_data_BBB(data_TX,length_TX)
	#define log_integer(test3,length_TX) log_integer_BBB(test3,length_TX)
	#define log_string(data_TX) log_string_BBB (data_TX)
#endif

uint8_t logString[9] = " Log ID:";
uint8_t payloadString[9]= " Payload:";
uint8_t timestampString[11] = " Timestamp:";

/*Function to allocate memory in heap to the log item structure*/
Log_t * create_log_item(){

	Log_t * struct_ptr = (Log_t *) calloc(1,sizeof(Log_t));
	return struct_ptr;
}

/*Function to log the structure to the serial terminal*/
uint8_t log_item(Log_t * struct_ptr){

	uint8_t len = struct_ptr->LogLength;
	uint16_t ID = struct_ptr->logID;

	log_string("\n\r");
	log_string(timestampString);

#if defined BBB || defined HOST

	gettimeofday(&tv, NULL);
	struct_ptr->Timestamp = tv.tv_sec;

#endif

	c_time_string = ctime((time_t *)&struct_ptr->Timestamp);

	uint8_t length = stringLength(c_time_string);

	c_time_string[length-1] = ' ';

	log_string(c_time_string);

	log_string(logString);

	if(ID >=0xa){
		my_itoa((int8_t*)&(struct_ptr->logID),(struct_ptr->logID),10);
		log_data((uint8_t*)&(struct_ptr->logID),2);
		}
	else{
		my_itoa((int8_t *)&(struct_ptr->logID),(struct_ptr->logID),10);
		log_data((uint8_t*)&(struct_ptr->logID),1);
	}

	if(len!=0){
		log_data((uint8_t * )&payloadString,9);

		log_data((struct_ptr->Payload),len);
	}
	return NOERROR;
}

/*Function to free the structure from heap memory*/
uint8_t destroy_log_item(Log_t * struct_ptr){

	free(struct_ptr);
	return NOERROR;
}
