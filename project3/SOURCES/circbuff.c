/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/12/2017
*
* File : circbuff.c
* Description : Source file for Circular buffer functions
*               -cbuff_state cbuffer_full(CircBuff *CircBuffTR)
*               -cbuff_state cbuffer_empty(CircBuff *CircBuffTR)
*               -cbuff_state cbuffer_add(CircBuff *CircBuffTR,uint8_t * data,uint8_t values_to_add)
*		-uint8_t cbuffer_peak(CircBuff * CircbuffTR,uint8_t search_term)
*               -cbuff_state cbuffer_remove(CircBuff * CircBuffTR,uint8_t values_to_remove)
*		-uint8_t *  cbuffer_memoryAllocate(uint8_t *cbuffer, uint8_t length_buff)
*		-cbuff_state cbuffer_Destroy(CircBuff *CircBuffTR, uint8_t  *c_bufferTR)
*		-void cbuffer_init(CircBuff *CircBuffTR)
***************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "circbuff.h"
#include "logger.h"
#include "binary_logger.h"


#ifdef FRDM
#include "MKL25Z4.h"
#endif


/*This function checks if buffer is full*/
cbuff_state cbuffer_full(CircBuff *CircBuffTR)
{
	/*Return Null pointer error, if CircBuffTR doesn't point to a valid location*/
	if(CircBuffTR == NULL){
		#ifdef LOG_ON
			/*Binary logger for log error*/
			uint8_t nullPointerError[] = "NULL Pointer\n\r";
			system_log->logID = LOG_ERROR;
			system_log->LogLength = 14;
			system_log->Payload = nullPointerError;
			log_item(system_log);
		#endif
		return NULL_POINTER;
	}
	/*If count value is equal to length, return circular buffer is full*/
    if((CircBuffTR->count) == (CircBuffTR->length)){
        (CircBuffTR->cbuff_state)=BUFFER_FULL;
        printf("\n%d",CircBuffTR->cbuff_state);
    }
    else{
		/*If count is less than length, return circular buffer is available*/
        (CircBuffTR->cbuff_state)=AVAILABLE;
    }
	/*Return circular buffer is full or available*/
    return (CircBuffTR->cbuff_state);
}

/*This function checks if buffer is empty*/
cbuff_state cbuffer_empty(CircBuff *CircBuffTR)
{
	/*return null pointer error,if CircBuffTR doesn't point to a valid loaction*/
	if(CircBuffTR == NULL)
		return NULL_POINTER;

	/*If Count=0, return circular buffer is empty*/
	if(((CircBuffTR->head)==(CircBuffTR->tail)) && ((CircBuffTR->count)==0)){
        (CircBuffTR->cbuff_state)=BUFFER_EMPTY;
    }
    else{
		/*If count!=0 return buffer is available*/
        (CircBuffTR->cbuff_state)=AVAILABLE;
    }
	/*Return whether buffer is empty or available*/
    return (CircBuffTR->cbuff_state);
}

/*This function is used to add elements to circular buffer*/
cbuff_state cbuffer_add(CircBuff *CircBuffTR,uint8_t * data,uint8_t values_to_add)
{
	/*Return null pointer error if CircBuffTR doesn't point to a valid loaction*/
	if(CircBuffTR == NULL)
		return NULL_POINTER;

	/*Return no length error,if values to add is 0*/
	if(values_to_add == 0)
		return NO_LENGTH;

	if(((CircBuffTR->head)==(CircBuffTR->tail)) && ((CircBuffTR->count)>(CircBuffTR->length))){
		(CircBuffTR->count)=0;
	}

    while(values_to_add){
		/*Condition to check if buffer is not full*/
        if((CircBuffTR->count)!=(CircBuffTR->length)){
			/*Put the data at location pointed by head, then increment head pointer
              and count value*/
            *(CircBuffTR->head)=*data;
            (CircBuffTR->head)++;
            (CircBuffTR->count)++;

			/*Wrap around, if head is pointing to last location of buffer*/
            if((CircBuffTR->head)>((CircBuffTR->buffer)+(CircBuffTR->length)-1)){
                (CircBuffTR->head)=(CircBuffTR->buffer);
            }
			/*Return available after adding element in buffer*/
            (CircBuffTR->cbuff_state) = AVAILABLE;
        }
        else{
			/*Return buffer full if values to add is not zero but length is equal to count*/
            (CircBuffTR->cbuff_state) = BUFFER_FULL;
        }
        data++;
        values_to_add--;
    }
	/*Return available or buffer full*/
	return (CircBuffTR->cbuff_state);
}


/*This function is used to check the value present at a particular
  location of circular buffer*/
uint8_t cbuffer_peak(CircBuff * CircbuffTR,uint8_t search_term)
{
	/*Return null pointer error, if CircbuffTR doesn't point to a valid location*/
	if(CircbuffTR == NULL)
		return NULL_POINTER;

    uint8_t value_peak;
    value_peak= *((CircbuffTR->buffer)+search_term-1);

	/*Return the value present at particular location*/
    return value_peak;
}

/*This function is used to remove elements from circular buffer*/
cbuff_state cbuffer_remove(CircBuff * CircBuffTR,uint8_t values_to_remove)
{
	/*Return Null pointer error if CircbuffTR doesn't point to a valid location*/
	if(CircBuffTR == NULL)

		return NULL_POINTER;

	/*Return no length error, if the values to remove is passed as 0*/
	if(values_to_remove == 0)
		return NO_LENGTH;


    while(values_to_remove){

		/*Count value checks if buffer is empty*/
        if((CircBuffTR->count)!=0){
            *(CircBuffTR->tail)=0;

			/*After removing the element from buffer, increment tail pointer
              and decrement count value*/
            (CircBuffTR->tail)++;
            (CircBuffTR->count)--;

			/*Wrap around if tail points at last location*/
            if((CircBuffTR->tail)>((CircBuffTR->buffer)+(CircBuffTR->length)-1)){
                (CircBuffTR->tail)=(CircBuffTR->buffer);
            }
			/*Return no error after removing element*/
            (CircBuffTR->cbuff_state) = NO_ERROR;
        }
        else{
			/* If values to remove is not 0 but buffer is empty, return buffer empty*/
            (CircBuffTR->cbuff_state) = BUFFER_EMPTY;
        }
        values_to_remove--;
    }
    return (CircBuffTR->cbuff_state);
}

/*This function allocates heap memory to buffer*/
uint8_t *  cbuffer_memoryAllocate(uint8_t *cbuffer, uint8_t length_buff)
{
	cbuffer = (uint8_t *) calloc(length_buff,sizeof(uint8_t));

	/*Return the location of circular buffer after allocating memory*/
    return cbuffer;
}

/*This function is used to free the heap memory allocate to buffer*/
cbuff_state cbuffer_Destroy(CircBuff *CircBuffTR, uint8_t  *c_bufferTR)
{
	free(c_bufferTR);
	free(CircBuffTR);

	/*After destroying memory return no error*/
    return NO_ERROR;
}


/*This function is used to initialize circular buffer, to make head,tail
and buffer point at first location of buffer and initialize count to 0*/
void cbuffer_init(CircBuff *CircBuffTR)
{
	(CircBuffTR->head)=(CircBuffTR->buffer);
	(CircBuffTR->tail)=(CircBuffTR->buffer);
	(CircBuffTR->count)=0;
}
