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

/*Compile time switch to include libraries for FRDM*/
#ifdef FRDM
#include "uart_init.h"
#include "MKL25Z4.h"
#endif

uint8_t string[9] = " Log ID:";
uint8_t string2[9]= " Payload:";

/*Function to allocate memory in heap to the log item structure*/
Log_t * create_log_item(){

	Log_t * struct_ptr = (Log_t *) calloc(1,sizeof(Log_t));
	return struct_ptr;
}

/*Function to log the structure to the serial terminal*/
uint8_t log_item(Log_t * struct_ptr){

	uint8_t len = struct_ptr->LogLength;
	uint16_t ID = struct_ptr->logID;

	//cbuffer_add(CircBuffT,&string[0],9);
	log_string(string);

	//log_integer((uint32_t)ID, 2);
	if(ID >=0xa && ID<= 0xf){
		my_itoa((int8_t*)&(struct_ptr->logID),(struct_ptr->logID),10);
		log_data((uint8_t*)&(struct_ptr->logID),2);
		//cbuffer_add(CircBuffT,(uint8_t *)&(struct_ptr->logID),2);
		}
	else{
		my_itoa((int8_t *)&(struct_ptr->logID),(struct_ptr->logID),10);
		log_data((uint8_t*)&(struct_ptr->logID),1);
		//cbuffer_add(CircBuffT,(uint8_t *)&(struct_ptr->logID),1);
	}

	if(len!=0){
		//cbuffer_add(CircBuffT,&string2[0],10);
		//log_string(string2);
		log_data((uint8_t * )&string2,9);

		//log_string((struct_ptr->Payload));
		log_data((struct_ptr->Payload),len);
		//cbuffer_add(CircBuffT,(struct_ptr->Payload),len);
	}
	return NOERROR;
}

/*Function to free the structure from heap memory*/
uint8_t destroy_log_item(Log_t * struct_ptr){

	free(struct_ptr);
	return NOERROR;
}
