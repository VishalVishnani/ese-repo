/*
 * circbuff.h
 *
 *  Created on: Feb 28, 2017
 *      Author: vishal
 */

#ifndef SOURCES_CIRCBUFF_H_
#define SOURCES_CIRCBUFF_H_


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

typedef struct CircBuf_t{
    volatile uint8_t * buffer;
    volatile uint8_t * head;
    volatile uint8_t * tail;
    volatile uint8_t length;
    volatile uint8_t count;
    cbuff_state buff_states;
}CircBuff;

CircBuff *CircBuffT;
CircBuff *CircBuffTR;
CircBuff *CircBuffR;
uint8_t  *c_bufferT;
uint8_t  *c_bufferR;
uint8_t  length_buff;

cbuff_state cbuffer_full(CircBuff *CircBuffTR);
cbuff_state cbuffer_empty(CircBuff *CircBuffTR);
cbuff_state cbuffer_add(CircBuff *CircBuffTR,uint8_t * data,uint8_t values_add);
uint8_t cbuffer_peak(CircBuff *CircBuffTR,uint8_t search_term);
cbuff_state cbuffer_remove(CircBuff *CircBuffTR,uint8_t values_remove);
cbuff_state cbuffer_memoryAllocate(CircBuff *CircBuffTR, uint8_t length_buff);
cbuff_state cbuffer_Destroy();
void cbuffer_init(CircBuff *CircBuffTR);



#endif /* SOURCES_CIRCBUFF_H_ */
