/**************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/01/2017
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

    if(src == NULL || dst == NULL)
    {
    	return INVALID_MEMORY_POINTER;
    }
    /*Check for the memory overlap condition*/
    if(src>dst)
    {
        for(i=1;i<=length;i++)
        {
            *(dst+i-1)= *(src + i-1);
        }
        return SUCCESSFUL_TRANSFER;
    }
    else if(dst>src)
    {
        for(i=length;i>0;i--)
        {
            *(dst+i-1)= *(src + i-1);
        }
        return SUCCESSFUL_TRANSFER;
    }
    else if(src==dst)
    {
     	return SAME_ADDRESS;
    }
    else
    {
        return TRANSFER_FAILED;
    }
}

/*Function used to set a value in memory from
 *a memory location upto a specified length */
int8_t my_memset(uint8_t *src,uint32_t length,uint8_t value)
{
    uint32_t i=0;
    uint32_t j=0;

    if(src == NULL)
        {
        	return INVALID_MEMORY_POINTER;
        }

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
        return SUCCESSFUL_TRANSFER;
    }
    /*Else value not written properly
     *return error */
    else
    {
        return TRANSFER_FAILED;
    }
}

/*Function to clear(write 0) to a block of memory*/
int8_t my_memzero(uint8_t* src,uint32_t length)
{
    uint32_t i=0;
    uint32_t j=0;

    if(src == NULL)
        {
        	return INVALID_MEMORY_POINTER;
        }

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
        return SUCCESSFUL_TRANSFER;
    }
    /*Else return error*/
    else
    {
        return TRANSFER_FAILED;
    }
}

/*Function to reverse a length of bytes in memory*/
int8_t my_reverse(uint8_t * src,uint32_t length)
{
    uint8_t * first = src;
    uint8_t * last = NULL;
    last = src + (length-1);
    uint8_t temp;

    if(src == NULL)
        {
        	return INVALID_MEMORY_POINTER;
        }

    if(length == 0 || length >4294967296)
    {
     	return INVALID_LENGTH;
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
		return SUCCESSFUL_TRANSFER;
    }

}
