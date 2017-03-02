/*
 * circbuff.h
 *
 *  Created on: Feb 28, 2017
 *      Author: vishal
 */

#ifndef SOURCES_CIRCBUFF_H_
#define SOURCES_CIRCBUFF_H_


typedef enum buffer_states{
    full=5,
    empty,
    available
    }b_s;

typedef struct CircBuf_t{
    volatile uint8_t * buffer;
    volatile uint8_t * head;
    volatile uint8_t * tail;
    volatile uint8_t length;
    volatile uint8_t count;
    b_s buff_states;
}CircBuff;

CircBuff *CircBuffT;
CircBuff *CircBuffTR;
CircBuff *CircBuffR;
uint8_t  * c_bufferT;
uint8_t * c_bufferR;
uint8_t length_buff;

uint8_t cbuffer_full(CircBuff *CircBuffTR);
uint8_t cbuffer_empty(CircBuff *CircBuffTR);
uint8_t cbuffer_add(CircBuff *CircBuffTR,uint8_t * data,uint8_t values_add);
uint8_t cbuffer_peak(CircBuff *CircBuffTR,uint8_t search_term);
uint8_t cbuffer_remove(CircBuff *CircBuffTR,uint8_t values_remove);
void cbuffer_memoryallocate();
void cbuffer_destroy();



#endif /* SOURCES_CIRCBUFF_H_ */
