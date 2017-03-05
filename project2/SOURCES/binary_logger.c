/*
 * binary_logger.c
 *
 *  Created on: Mar 3, 2017
 *      Author: viga7710
 */

#include <stdlib.h>
#include <stdint.h>
#include "circbuff.h"
#include "binary_logger.h"
#include "logger.h"

uint8_t string[10] = " Log ID: ";
uint8_t string2[10]= " Payload: ";

Log_t * create_log_item(){

	Log_t * struct_ptr = (Log_t *) calloc(1,sizeof(Log_t));
	return struct_ptr;
}

uint8_t log_item(Log_t * struct_ptr){

	uint8_t len = struct_ptr->LogLength;
	uint16_t ID = struct_ptr->logID;
	uint16_t pay= struct_ptr->Payload;
	cbuffer_add(CircBuffT,&string[0],10);

	if(ID >=0xa && ID<= 0xf){
		my_itoa((uint8_t*)&(struct_ptr->logID),(struct_ptr->logID),10);
		cbuffer_add(CircBuffT,(uint8_t *)&(struct_ptr->logID),2);}
	else{
		my_itoa((uint8_t *)&(struct_ptr->logID),(struct_ptr->logID),10);
		cbuffer_add(CircBuffT,(uint8_t *)&(struct_ptr->logID),1);
	}

	if(len != 0){
		cbuffer_add(CircBuffT,&string2[0],10);
		cbuffer_add(CircBuffT,(uint8_t *)&(struct_ptr->Payload),2);
	}
	return NOERROR;
}

uint8_t destroy_log_item(Log_t * struct_ptr){

	free(struct_ptr);
	return NOERROR;
}
