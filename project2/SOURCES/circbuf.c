#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

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

CircBuff *CircBuff1;
uint8_t  * c_buffer;
uint8_t length_buff;

uint8_t cbuffer_full()
{
    if((CircBuff1->count) ==(CircBuff1->length)){
        (CircBuff1->buff_states)=full;
        printf("\n%d",CircBuff1->buff_states);
        return (CircBuff1->buff_states);
    }
    else{
        (CircBuff1->buff_states)=available;
        return (CircBuff1->buff_states);
    }

}

uint8_t cbuffer_empty()
{
    if(((CircBuff1->head)==(CircBuff1->tail)) && ((CircBuff1->count)==0)){
        (CircBuff1->buff_states)=empty;
        return (CircBuff1->buff_states);
    }
    else{
        (CircBuff1->buff_states)=available;
        return (CircBuff1->buff_states);
    }
}

uint8_t cbuffer_add(uint8_t * data,uint8_t values_add)
{
   if(((CircBuff1->head)==(CircBuff1->tail)) && ((CircBuff1->count)>(CircBuff1->length))){
        (CircBuff1->count)=0;
   }

    while(values_add){
        if((CircBuff1->count)!=(CircBuff1->length)){
            *(CircBuff1->head)=*data;
            (CircBuff1->head)++;
            (CircBuff1->count)++;
            if((CircBuff1->head)>((CircBuff1->buffer)+(CircBuff1->length)-1)){
                (CircBuff1->head)=(CircBuff1->buffer);
            }
        (CircBuff1->buff_states)=available;
        //return (CircBuff1->buff_states);
        }
        else{
            (CircBuff1->buff_states)=full;
          //  return (CircBuff1->buff_states);
        }
        data++;
        values_add--;
    }
}

uint8_t cbuffer_peak(uint8_t search_term)
{
    uint8_t value_peak;
    value_peak= *((CircBuff1->buffer)+search_term-1);
    return value_peak;
}

uint8_t cbuffer_remove(uint8_t values_remove)
{
    uint8_t remove_data;
    while(values_remove){
        if((CircBuff1->count)!=0){
            remove_data= *(CircBuff1->tail);
            *(CircBuff1->tail)=0;
            (CircBuff1->tail)++;
            (CircBuff1->count)--;
            if((CircBuff1->tail)>((CircBuff1->buffer)+(CircBuff1->length)-1)){
                (CircBuff1->tail)=(CircBuff1->buffer);
            }
        //return remove_data;
        }
        else{
            (CircBuff1->buff_states)=empty;
          //  return (CircBuff1->buff_states);
        }
        values_remove--;
    }

}

void cbuffer_memoryallocate()
{

    CircBuff1=(CircBuff *) calloc(1,sizeof(CircBuff1));
    c_buffer= (uint8_t *) calloc(length_buff,sizeof(CircBuff1));
}
void cbuffer_destroy()
{
    free(CircBuff1);
    free(c_buffer);
}

int main()
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
}

