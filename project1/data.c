#include<stdio.h>
#include<stdint.h>
#include"data.h"
#include"memory.h"

/*Defining Macros*/
#define BINARY_BASE   2
#define DECIMAL_BASE  10
#define OCTAL_BASE    8
#define HEX_BASE      16
#define BINARY_BITS   10
#define OCTAL_BITS    1000
#define HEX_BITS      10000


/*Function is used to convert to Little Endian notation*/
int8_t big_to_little32(uint32_t * data,uint32_t length)
{
    uint32_t temp;
    uint8_t i;
    for(i=0;i<length;i++)
    {
        temp=((*data&0xFF)<<24)|((*data&0xFF000000)>>24)|((*data&0xFF00)<<8)|((*data&0xFF0000)>>8);
        *data=temp;
        data++;
    }
    return 0;
}

/*Function is used to convert to Big Endian notation*/
int8_t little_to_big32(uint32_t * data,uint32_t length)
{
    uint32_t temp;
    uint8_t i;
    for(i=0;i<length;i++)
    {
        temp=((*data&0xFF)<<24)|((*data&0xFF000000)>>24)|((*data&0xFF00)<<8)|((*data&0xFF0000)>>8);
        *data=temp;
        data++;
    }
    return 0;
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
   //printf("\nResult- %d",result);
   if(result)
    return result;
   else return 0;
}

/* Function to convert Integer values to ASCII*/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base)
{   uint8_t sign = 0;
    uint32_t remainder;
    uint64_t position = 1;
    uint16_t length;

    if(data<0)
     {
       sign = 1;
       data = -data;
      }

     position = 1;
     while(data)
     {
      remainder = data%base;
      data=data/base;

     if(remainder>9)
     {
       remainder = remainder - 10;
       *(str+position-1) = (int8_t)(remainder+65);
     }
      else
      {
        *(str+position-1) = (int8_t)(remainder+48);
      }
      position++;
     }
     if(sign)
     {
      *(str+position-1)= '-';
       position++;
     }
     *(str+position-1)='\0';

    length = stringLength(str);
    reverse(str,length);
    return str;
}

/*Function to reverse the array
  It receives the array pointer and length
  and returns some information about the array*/
void reverse(int8_t *str2, int length)
{
    int j=0;
    int8_t temp;
    int8_t *first = str2;
    int8_t *last = str2 + length-1;

    for(j=0;j<length/2;j++) /*Reverse if previous cases are false*/
      {
        temp = *first;
        *first = *last;
        *last = temp;
        last--;
        first++;
      }
}

/*Function to find length of array
  It takes the array as an input*/
uint8_t stringLength(int8_t *str1)
{
    uint8_t length = 0;
    while((*str1)!='\0')
    {
      length++;
      str1++;
    }
    return length;
}
