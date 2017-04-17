/************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/01/2017
*
* File : data.c
* Description : Source file for data manipuation
*               -big_to_little32()
*               -little_to_big32()
*               -my_atoi()
*               -my_itoa()
*               -print_memory()
*               -stringLength()
*************************************************/

#include<stdio.h>
#include<stdint.h>
#include"data.h"
#include"memory.h"

#ifdef FRDM
 #define printf(...)
#endif

/*Defining Macros*/
#define ASCII_OF_A (65)
#define ASCII_OF_0 (48)

/*Function is used to convert to Little Endian notation*/
int8_t big_to_little32(uint32_t * data,uint32_t length)
{
    uint32_t temp;
    uint32_t i;

    if(data == NULL)
    {
    	return INVALID_POINTER;
    }
    else if(length == 0 || length > 4294967296)
    {
     	return INVALID_DATA_LENGTH;
    }
    else
    {   for(i=0;i<length;i++)
   	 	{   /*Shift data bytes in a 32 bit data memory*/
   	    	temp=((*data&0xFF)<<24)|((*data&0xFF000000)>>24)|((*data&0xFF00)<<8)|((*data&0xFF0000)>>8);
  	     	*data=temp;
     	 	data++;
     	}
     	return SUCCESSFUL_CONVERSION;
    }
}

/*Function is used to convert to Big Endian notation*/
int8_t little_to_big32(uint32_t * data,uint32_t length)
{
    uint32_t temp;
    uint32_t i;

    if(data == NULL)
    {
        return INVALID_POINTER;
    }
    else if(length == 0 || length > 4294967296)
    {
         return INVALID_DATA_LENGTH;
    }
    else
    {   for(i=0;i<length;i++)
   	 	{   /*Shift data bytes in a 32 bit data memory*/
   	    	temp=((*data&0xFF)<<24)|((*data&0xFF000000)>>24)|((*data&0xFF00)<<8)|((*data&0xFF0000)>>8);
  	     	*data=temp;
     	 	data++;
     	}
     	return SUCCESSFUL_CONVERSION;
    }
}

/*Function is used to convert ASCII string to Integer*/
int32_t my_atoi(int8_t * str)
{
   int8_t sign = 0;
   int32_t result=0;

   if(*str == '\0')
   {
    	return '\0';
   }

   if(*str == '-')
   {
    	sign = 1;
   		str++;
   }

   /*Check if data is an integer or higher hex bits*/
   if(((*str>='0')&&(*str<='9'))||*str==' '||((*str>='A')&&(*str<='F')))
   {
    	while(*str!='\0')
    	{
        	if(*str==' ')
        	{
            	str++;
            	continue;
        	}
        	else if((*str>='0')&&(*str<='9'))
        	{
            	result = result*10 + (uint8_t)(*str - '0');
            	str++;
            	continue;
        	}
        	else if((*str>='A')&&(*str<='F'))
        	{
            	result = result*10 + (uint8_t)(*str - 'A');
            	str++;
            	continue;
        	}
        	break;
    	}
   	}

   if(sign)
   {
   		result = -result;
   }

   if(result)
    return result;
   else return 0;
}

/* Function to convert Integer values to ASCII*/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base)
{   uint8_t sign = 0;
    uint32_t remainder;
    uint8_t position = 1;
    uint16_t length;

    /*Handle signed data*/
    if(data<0)
    {
    	sign = 1;
    	data = -data;
    }

    position = 1;
    /*Till data is present divide the data with base and
     *store its remainder in a string */
    while(data)
    {
   		remainder = data%base;
      	data=data/base;

    	if(remainder>9)
    	{
       		remainder = remainder - 10;
       		*(str+position-1) = (int8_t)(remainder+ASCII_OF_A);
    	}
    	else
    	{
    		*(str+position-1) = (int8_t)(remainder+ASCII_OF_0);
    	}
    	position++;
    }
    if(sign)
    {
      	*(str+position-1)= '-';
       	position++;
    }
    *(str+position-1)='\0';

    /*Since remainder is stored in reverse order
     *we need to reverse the string*/
    length = stringLength(str);
    my_reverse((uint8_t*)str,length);
    return str;
}

/*Function to find length of array
  It takes the array as an input*/
uint8_t stringLength(int8_t *str1)
{
	uint8_t length = 0;
    /*Calculate length till NULL terminator is reached*/
    while((*str1)!='\0')
    {
    	length++;
    	str1++;
    }
    return length;
}

/*Function to print a block of memory starting
 *from a memory location upto the length specified*/
void print_memory(uint8_t * start,uint32_t length)
{
    uint32_t i;
    /*Print memory up to a specified length*/
    printf("\nDisplaying memory: ");
    for(i=0;i<length;i++)
    {
    	printf("%x ",*start);
    	start++;
    }
    printf("\n");
}
