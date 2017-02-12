#include<stdint.h>
#include<stdio.h>
#include"data.h"
#include"memory.h"
#include"project_1.h"

uint8_t set_1[32]={0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF,0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF};
uint8_t set_2[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

void test_data1(void)
{
        printf("\nTestdata 1");
        uint8_t * data = 0;
        data = &set_1;
        uint32_t length = 8;
        print_memory(data,length);
        big_to_little32(data,length);
        print_memory(data,length);
        little_to_big32(data,length);
        print_memory(data,length);
}

void test_data2(void)
{   printf("\nTestdata 2");
    uint8_t result[50]={0};
    int8_t *ptr= NULL ;
    uint8_t i = 0,j = 0;
    uint8_t difference = 0;
    uint8_t length = 0;
    int32_t data = 0;
    uint8_t base = 10;
    int32_t intValue[10]={0};

    for(i=0;i<32;i+=4)
       {
        for(j=0;j<4;j++)
           {
               data = data*100 + *(set_2+i+j);
           }
        ptr = my_itoa((int8_t *)(result+i), data , base);
        data = 0;
        printf("ITOA ");
        print_memory(result+i,4);
        intValue[i/4] = my_atoi(result+i);
        for(j=0;j<4;j++)
           {
             *(result+i+3-j) = intValue[i/4]%100;
             intValue[i/4]=intValue[i/4]/100;
           }
        printf("ATOI ");
        print_memory((int8_t *)(result+i),1);
       }
}

void test_memory(void)
{
    printf("\nTest memory");

    uint8_t * start=&set_2;
    print_memory(start,8);
    my_reverse(start,12);
    uint8_t * src=&set_2[16];
    my_memset(src,4,0xEE);
    src=&set_2[25];
    uint8_t * dst=&set_2[19];
    my_memmove(src,dst,6);
    src=&set_2[11];
    my_memzero(src,5);
    src=&set_2;
    dst=&set_2[8];
    my_memmove(src,dst,8);
    print_memory(start,8);
}


void project_1_report(void)
{
    printf("\nProject1");
    void test_data1();
    void test_data2();
    void test_memory();
}

int main(void)
{
    test_data2();
    return 1;
}

