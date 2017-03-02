* circbuff.c
 *
 *  Created on: Feb 28, 2017
 *      Author: vishal virag
 */
//include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "circbuff.h"

/*typedef enum buffer_states{
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

CircBuff *CircBuff1;
uint8_t  * c_buffer;
uint8_t length_buff;
*/
uint8_t cbuffer_full(CircBuff *CircBuffTR)
{
    if((CircBuffTR->count) ==(CircBuffTR->length)){
        (CircBuffTR->buff_states)=full;
        printf("\n%d",CircBuffTR->buff_states);
        return (CircBuffTR->buff_states);
    }
    else{
        (CircBuffTR->buff_states)=available;
        return (CircBuffTR->buff_states);
    }

}

uint8_t cbuffer_empty(CircBuff *CircBuffTR)
{
    if(((CircBuffTR->head)==(CircBuffTR->tail)) && ((CircBuffTR->count)==0)){
        (CircBuffTR->buff_states)=empty;
        return (CircBuffTR->buff_states);
    }
    else{
        (CircBuffTR->buff_states)=available;
        return (CircBuffTR->buff_states);
    }
}

uint8_t cbuffer_add(CircBuff *CircBuffTR,uint8_t * data,uint8_t values_add)
{
   if(((CircBuffTR->head)==(CircBuffTR->tail)) && ((CircBuffTR->count)>(CircBuffTR->length))){
        (CircBuffTR->count)=0;
   }

    while(values_add){
        if((CircBuffTR->count)!=(CircBuffTR->length)){
            *(CircBuffTR->head)=*data;
            (CircBuffTR->head)++;
            (CircBuffTR->count)++;
            if((CircBuffTR->head)>((CircBuffTR->buffer)+(CircBuffTR->length)-1)){
                (CircBuffTR->head)=(CircBuffTR->buffer);
            }
        (CircBuffTR->buff_states)=available;
        //return (CircBuffTR->buff_states);
        }
        else{
            (CircBuffTR->buff_states)=full;
          //  return (CircBuffTR->buff_states);
        }
        data++;
        values_add--;
    }
}

uint8_t cbuffer_peak(CircBuff * CircbuffTR,uint8_t search_term)
{
    uint8_t value_peak;
    value_peak= *((CircBuffTR->buffer)+search_term-1);
    return value_peak;
}

uint8_t cbuffer_remove(CircBuff * CircBuffTR,uint8_t values_remove)
{
    uint8_t remove_data;
    while(values_remove){
        if((CircBuffTR->count)!=0){
            remove_data= *(CircBuffTR->tail);
            *(CircBuffTR->tail)=0;
            (CircBuffTR->tail)++;
            (CircBuffTR->count)--;
            if((CircBuffTR->tail)>((CircBuffTR->buffer)+(CircBuffTR->length)-1)){
                (CircBuffTR->tail)=(CircBuffTR->buffer);
            }
        //return remove_data;
        }
        else{
            (CircBuffTR->buff_states)=empty;
          //  return (CircBuff1->buff_states);
        }
        values_remove--;
    }

}

void cbuffer_memoryallocate()
{

    CircBuffT=(CircBuff *) calloc(1,sizeof(CircBuffT));
    CircBuffR=(CircBuff *) calloc(1,sizeof(CircBuffR));
    c_bufferT= (uint8_t *) calloc(length_buff,sizeof(CircBuffT));
    c_bufferR= (uint8_t *) calloc(length_buff,sizeof(CircBuffR));
}

void cbuffer_destroy()
{
    free(CircBuffT);
    free(CircBuffR);
    free(c_bufferT);
    free(c_bufferR);

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





