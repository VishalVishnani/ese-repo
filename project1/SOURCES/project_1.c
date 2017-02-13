/*************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 02/12/2017
* 
* File : project_1.c
* Description : Source file for testing functions
*               - project_1_report()
*               - test_data1()
*               - test_data2()
*               - test_memory()
**************************************************/


#include<stdint.h>
#include<stdio.h>
#include"data.h"
#include"memory.h"
#include"project_1.h"

#ifdef FRDM
 #define printf(...)
#endif

/*Defining global variables*/
uint8_t set_1[32]={0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF,0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF};
uint8_t set_2[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};


/* The function is used to test the functions
 * big_to_little32() and little_to_big32() with set_1 data
 */
void test_data1(void)
{
	printf("\nIn test_data1() function: ");
    uint8_t * data = NULL;
    data = set_1;
    uint32_t length = 32;
    print_memory(data,length);
    /*Convert from big to little endian*/
    big_to_little32((uint32_t *)data,length);
    printf("\nAfter big endian to little endian conversion: ");
	print_memory(data,length);
	printf("\nAfter little endian to big endian conversion: ");
    /*Convert from little to big endian*/    
	little_to_big32((uint32_t *)data,length);
    print_memory(data,length);
}

/* The function is used to test the functions
 * my_itoa() and my_atoi() using set_2 data
 */
void test_data2(void)
{
    int8_t result[50]={0};
    uint8_t i = 0,j = 0;
    int32_t data = 0;
    uint8_t base = 10;
    int32_t intValue[10]={0};
    
	printf("\nIn test_data2() function: \n");
    for(i=0;i<32;i+=4)
	{
        /*Combine 4 bytes from set_2 and store in data*/
        for(j=0;j<4;j++)
        {
        	data = data*100 + *(set_2+i+j);
        }
        /*Call my_itoa() with address of string where data
         *is to be stored, the 32 bit data and the base*/
        my_itoa((int8_t *)(result+i), data , base);
        data = 0;

        printf("ITOA ");
        print_memory((uint8_t *)(result+i),8);
        /*Call my_atoi with the address of the string 
         *to convert and store it in an array*/

        *(intValue+i/4) = my_atoi(result+i);
        //printf("\n%p\n",point+i/4);
        for(j=0;j<4;j++)
        {
       	 	*(result+i+3-j) = *(intValue+i/4)%100;
            *(intValue+i/4) = *(intValue+i/4)/100;
        }
        printf("ATOI ");
        print_memory((uint8_t *)(result+i),4);
	}
}

/* The function is used to test functions like
 * my_reverse(), my_memset(), my_memmove() and
 * my_memzero() with set_2 data
 */
void test_memory(void)
{
    /*Reverse first 12 bytes*/
    uint8_t * start = set_2;
	printf("\nIn test_memory function: ");
    print_memory(start,32);
    my_reverse(start,12);
    //print_memory(start,32);

    /*Set 0xEE on the 17th to the 20th bytes*/
    uint8_t * src = &set_2[16];
    my_memset(src,4,0xEE);
    //print_memory(start,32);

    /*Move the 6 bytes starting at the 26th byte
     *([25]), to the 20th position ([19])*/
    src=&set_2[25];
    uint8_t * dst = &set_2[19];
    my_memmove(src,dst,6);
    //print_memory(start,32);

    /*Write zero to bytes 12-16 ([11] - [15])*/
    src=&set_2[11];
    my_memzero(src,5);
    //print_memory(start,32);

    /*Move the 8 bytes starting at the 1st byte ([0]),
     *to the 9th position ([8])*/
    src=set_2;
    dst=&set_2[8];
    my_memmove(src,dst,8);
    print_memory(start,32);
}

/* The function is used to call test_data1(),
 * test_data2() and test_memory() to test
 * functions in data.c and memory.c*/
void project_1_report(void)
{
    test_data1();
    test_data2();
    test_memory();
}
