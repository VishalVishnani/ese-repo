/**************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 02/12/2017
*
* File : memory.c
* Description : Source file for memory manipuation
*               -my_memmove()
*               -my_memset()
*               -my_memzero()
*               -my_reverse()
***************************************************/


#include<stdio.h>
#include<stdint.h>
#include "memory.h"

#ifdef FRDM
 #define printf(...)
#endif

/*Function used to move a block of memory from
 *one source location to a another*/
int8_t my_memmove(uint8_t * src,uint8_t * dst, uint32_t length)
{
    uint32_t i=0;

    /*Check for the memory overlap condition*/
    if(src>dst)
    {
        for(i=0;i<length;i++)
        {
            *(dst+i)=*(src + i);
        }
        return 1;
    }
    else if(dst>src)
    {
        for(i=length-1;i>=0;i--)
        {
            *(dst+i)=*(src + i);
        }
        return 1;
    }
    else if(src==dst)
    {
     	printf("Source and destination address are same");
     	return 1;
    }
    else
    {
        printf("error: mem move not possible");
        return 0;
    }
}

/*Function used to set a value in memory from
 *a memory location upto a specified length */
int8_t my_memset(uint8_t *src,uint32_t length,uint8_t value)
{
    uint32_t i=0;
    uint32_t j=0;

    for(i=0;i<length;i++)
    {
        *(src+i)=value;
    }

    /*Check if all the locations have the value
     *written, increment a variable if true*/
    for(i=0;i<length;i++)
    {
        if(*(src+i)==value)
        {
            j++;
        }
    }

    /*If true then value is successfully
     *written to all memory locations */
    if(j==length)
    {
        return 1;
    }
    /*Else value not written properly
     *return error */
    else
    {
        printf(" error: mem set failed");
        return 0;
    }
}

/*Function to clear(write 0) to a block of memory*/
int8_t my_memzero(uint8_t* src,uint32_t length)
{
    uint32_t i=0;
    uint32_t j=0;
    for(i=0;i<length;i++)
    {
    	*(src+i)=0;
    }

    /*Check if value is cleared
     *increment a variable if true*/
    for(i=0;i<length;i++)
    {
        if(*(src+i)==0)
        {
        	j++;
        }
    }

    /*If true then value is successfully
     *cleared from all memory locations*/
    if(j==length)
    {
        return 1;
    }
    /*Else return error*/
    else
    {
        printf(" error: mem zero failed");
        return 0;
    }
}

/*Function to reverse a length of bytes in memory*/
int8_t my_reverse(uint8_t * src,uint32_t length)
{
    uint8_t * first = src;
    uint8_t * last = NULL;
    last = src + (length-1);
    uint8_t temp;

    if(length == 0 || length >4294967296)
    {
    	printf("error : incorrect length for reverse function");
     	return 0;
    }
    else
    {/*Swap till half of the array is reached*/
     	while(first<=last)
    	{
         	temp=*first;
         	*first=*last;
         	*last=temp;
         	first++;
         	last--;
     	}
     return 1;
    }
}
