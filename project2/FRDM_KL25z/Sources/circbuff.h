/**************************************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/12/2017
*
* File : circbuff.h
* Description : Header file for Circular buffer functions
*               -cbuff_state cbuffer_full(CircBuff *CircBuffTR)
*               -cbuff_state cbuffer_empty(CircBuff *CircBuffTR)
*               -cbuff_state cbuffer_add(CircBuff *CircBuffTR,uint8_t * data,uint8_t values_to_add)
*				-uint8_t cbuffer_peak(CircBuff * CircbuffTR,uint8_t search_term)
*               -cbuff_state cbuffer_remove(CircBuff * CircBuffTR,uint8_t values_to_remove)
*				-uint8_t *  cbuffer_memoryAllocate(uint8_t *cbuffer, uint8_t length_buff)
*				-cbuff_state cbuffer_Destroy(CircBuff *CircBuffTR, uint8_t  *c_bufferTR)
*				-void cbuffer_init(CircBuff *CircBuffTR)
***************************************************************************************************/

#define FRDM
#define LOG_ON
#include <stdint.h>

#ifndef SOURCES_CIRCBUFF_H_
#define SOURCES_CIRCBUFF_H_


/*Enum used for returning the buffer state*/
typedef enum buffer_states{
	NO_ERROR,
	ERROR,
	BUFFER_FULL,
    BUFFER_EMPTY,
	NULL_POINTER,
	NO_LENGTH,
	BUFFER_ALLCATION_FAILURE,
    AVAILABLE
    }cbuff_state;

/*Circular buffer structure*/
typedef struct CircBuf_t{
     volatile uint8_t * buffer;
     volatile uint8_t * head;
     volatile uint8_t * tail;
     volatile uint8_t length;
     volatile uint8_t count;
     cbuff_state cbuff_state;
}CircBuff;

/*Structure variable for transmitter circular buffer*/
CircBuff *CircBuffT;

/*Structure variable for receiver circular buffer*/
CircBuff *CircBuffR;

/*Variable which states the length of buffer*/
uint8_t  length_buff;


/******************************************************************************
* This function is used to check if circular buffer is full
* The return value can be full or available depending on count value
* CircBuff *CircBuffTR - Pointer which points to circular buffer
*******************************************************************************/
cbuff_state cbuffer_full(CircBuff *CircBuffTR);


/*******************************************************************************
* This  function is used to check if circular buffer is empty
* The return value can be empty or available depending on count value
* CircBuff CircBuffTR - Pointer which points to circular buffer
*******************************************************************************/
cbuff_state cbuffer_empty(CircBuff *CircBuffTR);


/******************************************************************************
* This function is used to add elements to circular buffer
* The return value can be full or available
* CircBuff * CircBuffTR - Pointer which points to circular buffer
* uint8_t * data - Pointer which points to array which contains data
                   to be stored on buffer
uint8_t values_add - This variable has the number of values to be added to buffer
********************************************************************************/
cbuff_state cbuffer_add(CircBuff *CircBuffTR,uint8_t * data,uint8_t values_add);


/*******************************************************************************
* This function is to check the value at a particular location of buffer
* It returns the value present at that loaction
* CircBuff * CircBuffTR - Pointer which points to circular buffer
* uint8_t search term - This variable gives the term number whose values is to
                        be checked
*******************************************************************************/ 
uint8_t cbuffer_peak(CircBuff *CircBuffTR,uint8_t search_term);


/*******************************************************************************
* This function is used to remove elements from circular buffer
* The return value can be empty or available depending on count value
* CircBuff * CircBuffTR - Pointer which points to circular buffer
* uint8_t values_remove - This variable gives the number of values which are
			  to be removed
*******************************************************************************/
cbuff_state cbuffer_remove(CircBuff *CircBuffTR,uint8_t values_remove);


/*******************************************************************************
* This function is used to allocate heap memory to circular buffer
* uint8_t length_Buff - This variable gives the length of circular buffer
* uint8_t * cbuffer - Pointer whcih points to circular buffer
*******************************************************************************/
uint8_t *  cbuffer_memoryAllocate(uint8_t *cbuffer, uint8_t length_buff);


/******************************************************************************
* This function is used to free the heap memory allocated to circular buffer
* uint8_t *c_bufferTR - Pointer which points to circular buffer
******************************************************************************/
cbuff_state cbuffer_Destroy(CircBuff *CircBuffTR, uint8_t  *c_bufferTR);


/*****************************************************************************
* This function is used to initialize circular buffer
* It makes head, tail, buffer point to same location and make count 0
*****************************************************************************/
void cbuffer_init(CircBuff *CircBuffTR);




#endif /* SOURCES_CIRCBUFF_H_ */
