/* circbuff.c
 *
 *  Created on: Feb 28, 2017
 *      Author: vishal virag
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "circbuff.h"


cbuff_state cbuffer_full(CircBuff *CircBuffTR)
{
	if(CircBuffTR == NULL)
		return NULL_POINTER;

    if((CircBuffTR->count) == (CircBuffTR->length)){
        (CircBuffTR->buff_states)=BUFFER_FULL;
        printf("\n%d",CircBuffTR->buff_states);
    }
    else{
        (CircBuffTR->buff_states)=AVAILABLE;
    }
    return (CircBuffTR->buff_states);
}

cbuff_state cbuffer_empty(CircBuff *CircBuffTR)
{
	if(CircBuffTR == NULL)
		return NULL_POINTER;

	if(((CircBuffTR->head)==(CircBuffTR->tail)) && ((CircBuffTR->count)==0)){
        (CircBuffTR->buff_states)=BUFFER_EMPTY;
    }
    else{
        (CircBuffTR->buff_states)=AVAILABLE;
    }
    return (CircBuffTR->buff_states);
}

cbuff_state cbuffer_add(CircBuff *CircBuffTR,uint8_t * data,uint8_t values_to_add)
{
	if(CircBuffTR == NULL)
		return NULL_POINTER;

	if(values_to_add == 0)
		return NO_LENGTH;

	if(((CircBuffTR->head)==(CircBuffTR->tail)) && ((CircBuffTR->count)>(CircBuffTR->length))){
		(CircBuffTR->count)=0;
	}

    while(values_to_add){
        if((CircBuffTR->count)!=(CircBuffTR->length)){
            *(CircBuffTR->head)=*data;
            (CircBuffTR->head)++;
            (CircBuffTR->count)++;

            if((CircBuffTR->head)>((CircBuffTR->buffer)+(CircBuffTR->length)-1)){
                (CircBuffTR->head)=(CircBuffTR->buffer);
            }
            (CircBuffTR->buff_states) = AVAILABLE;
        }
        else{
            (CircBuffTR->buff_states) = BUFFER_FULL;
        }
        data++;
        values_to_add--;
    }
	return (CircBuffTR->buff_states);
}

uint8_t cbuffer_peak(CircBuff * CircbuffTR,uint8_t search_term)
{
	if(CircBuffTR == NULL)
			return NULL_POINTER;

    uint8_t value_peak;
    value_peak= *((CircBuffTR->buffer)+search_term-1);
    return value_peak;
}

cbuff_state cbuffer_remove(CircBuff * CircBuffTR,uint8_t values_to_remove)
{
	if(CircBuffTR == NULL)
			return NULL_POINTER;

	if(values_to_remove == 0)
			return NO_LENGTH;

    //uint8_t remove_data;
    while(values_to_remove){
        if((CircBuffTR->count)!=0){
            //remove_data= *(CircBuffTR->tail);
            *(CircBuffTR->tail)=0;
            (CircBuffTR->tail)++;
            (CircBuffTR->count)--;
            if((CircBuffTR->tail)>((CircBuffTR->buffer)+(CircBuffTR->length)-1)){
                (CircBuffTR->tail)=(CircBuffTR->buffer);
            }
            (CircBuffTR->buff_states) = NO_ERROR;
        }
        else{
            (CircBuffTR->buff_states) = BUFFER_EMPTY;
        }
        values_to_remove--;
    }
    return (CircBuffTR->buff_states);
}

cbuff_state  cbuffer_memoryAllocate(CircBuff *CircBuffTR, uint8_t length_buff)
{
    (CircBuffTR->buffer) = (uint8_t *) calloc(length_buff,sizeof(uint8_t));

    if ((CircBuffTR->buffer) == NULL)
    	return BUFFER_ALLCATION_FAILURE;
    else return NO_ERROR;
}

cbuff_state cbuffer_Destroy()
{
    free(CircBuffT);
    free(c_bufferT);
    return NO_ERROR;
}

void cbuffer_init(CircBuff *CircBuffTR)
{
	(CircBuffTR->head)=(CircBuffTR->buffer);
	(CircBuffTR->tail)=(CircBuffTR->buffer);
	(CircBuffTR->count)=0;
}

/*int main()
{
    printf("Enter the size of circular buffer:\n");
    scanf("%d",&length_buff);
    cbuffer_memoryallocate();
    (CircBuff1->length)=length_buff;
    uint8_t temp_len=length_buff;
    printf("Enter the number of values to be add\n");
    uint8_t values_add;
    scanf("%d",&values_add);
    printf("Enter the Values to be added\n");
    uint8_t temp[50];
    uint8_t i;
    for(i=0;i<values_add;i++){
        scanf("%d",&temp[i]);
    }
    uint8_t * data=temp;
    (CircBuff1->buffer)=(uint8_t *) c_buffer;
    (CircBuff1->head)=(CircBuff1->buffer);
    (CircBuff1->tail)=(CircBuff1->buffer);
    (CircBuff1->count)=0;
    printf("\n Head: %d",(CircBuff1->head));
    printf("\n Tail:%d",(CircBuff1->tail));
    printf("\n Buffer:%d",(CircBuff1->buffer));
    printf("\n count:%d",(CircBuff1->count));
    printf("\n length:%d",(CircBuff1->length));
    cbuffer_add(data,values_add);
    uint8_t j=0;
    while(temp_len){
        printf("\n%x",*(CircBuff1->buffer+j));
        (temp_len)--;
        j++;
    }
    printf("\n Head: %d",(CircBuff1->head));
    printf("\n Tail:%d",(CircBuff1->tail));
    printf("\n Buffer:%d",(CircBuff1->buffer));
    printf("\n count:%d",(CircBuff1->count));
    printf("\n length:%d",(CircBuff1->length));
    uint8_t search_term;
    printf("\nEnter the item no. to be searched: ");
    scanf("%d",&search_term);
    uint8_t value_peak= cbuffer_peak(search_term);
    printf("The value of that term is %d",value_peak);
    uint8_t values_remove;
    printf("\n Enter the number of elements to be removed: ");
    scanf("%d",&values_remove);
    cbuffer_remove(values_remove);
    temp_len=length_buff;
    j=0;
    while(temp_len){
        printf("\n%x",*(CircBuff1->buffer+j));
        (temp_len)--;
        j++;
    }
    printf("\n Head: %d",(CircBuff1->head));
    printf("\n Tail:%d",(CircBuff1->tail));
    printf("\n Buffer:%d",(CircBuff1->buffer));
    printf("\n count:%d",(CircBuff1->count));
    printf("\n length:%d",(CircBuff1->length));
    //cbuffer_full();
    //cbuffer_empty();
    cbuffer_destroy();
}*/
