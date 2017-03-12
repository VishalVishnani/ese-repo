/******************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 02/28/2017
*
* File : test_memory.c
* Description : Source file for testing memory functions
*               -test_memmove_invalid_pointer()
*               -test_memmove_no_overlap()
*               -test_memmove_src_in_dst()
*               -test_memmove_dst_in_src()
*               -test_memset_invalid_pointer()
*               -test_memset_valid()
*               -test_memzero_invalid_pointer()
*               -test_memzero_valid()
*               -test_reverse_invalid_pointer()
*               -test_reverse_odd()
*               -test_reverse_even()
*               -test_reverse_character()
*
* Tester : Virag Gada, MS in Embedded Systems
* Testing environment : To test the functions we need
* to install the Cmocka framework libraries in our folder
* path and make changes to the test Makefile to include
* our source files and test files.
********************************************************/

#include<stdio.h>
#include<stdint.h>
#include "memory.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


/*********************************************************
* Defining global variables required for out test function
* length and odd_length to provide odd and even lengths
* set[32] array to behave as a memory
*********************************************************/
uint32_t length = 10;
uint32_t odd_length = 11;
uint8_t set[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

/****************************************************************
* test_memmove_invalid_pointer() - Function to test NULL pointer
* check in my_memmove function.
* Input parameter - For this we can send either src or dst as
* NULL and some length
* Expected Result - Since an invalid(NULL) pointer is passed as a
* parameter the function should return an INVALID_MEMORY_POINTER
* emum
****************************************************************/
void test_memmove_invalid_pointer(void **state)
{
	uint8_t *src = &set[0];
	uint8_t *dst = NULL;
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

/****************************************************************
* test_memmove_no_overlap() - Function to test my_memmove function
* to move data from src to dst memory locations without overlap
* Input parameter - For this we send a pointer to valid src and dst
* locations along with the length in bytes so they don't overlap
* Expected Result - Since it does not have an invalid length or
* invalid pointer it should successfully move memory and return
* enum.
****************************************************************/
void test_memmove_no_overlap(void **state)
{
	uint8_t *src = &set[5];
	uint8_t *dst = &set[20];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

/****************************************************************
* test_memmove_src_in_dst() - Function to test my_memmove function
* to move data from src to dst memory locations with src in dst
* overlap
* Input parameter - For this we send a pointer to valid src and dst
* locations along with the length in bytes so that src is in dst
* Assumption - src in dst memory case can be handled by the function
* Expected Result - Since it does not have an invalid length or
* invalid pointer it should successfully move memory with src in
* dst and return enum.
****************************************************************/
void test_memmove_src_in_dst(void **state)
{
	uint8_t *src = &set[15];
	uint8_t *dst = &set[10];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

/****************************************************************
* test_memmove_dst_in_src() - Function to test my_memmove function
* to move data from src to dst memory locations with dst in src
* overlap
* Input parameter - For this we send a pointer to valid src and dst
* locations along with the length in bytes so that dst is in src
* Assumption - dst in src memory case can be handled by the function
* Expected Result - Since it does not have an invalid length or
* invalid pointer it should successfully move memory with dst in
* src and return enum.
****************************************************************/
void test_memmove_dst_in_src(void **state)
{
	uint8_t *src = &set[10];
	uint8_t *dst = &set[15];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

/****************************************************************
* test_memset_invalid_pointer() - Function to test NULL pointer
* check in my_memset function.
* Input parameter - For this we send src as NULL with some value
* and length
* Expected Result - Since an invalid(NULL) pointer is passed as a
* parameter the function should return an INVALID_MEMORY_POINTER
* emum
****************************************************************/
void test_memset_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	uint8_t value = 5;
	enum memory_status status = my_memset(src,length,value);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

/****************************************************************
* test_memset_valid() - Function to test my_memset function to
* set a particular value in memory
* Input parameter - For this we send a pointer to a valid memory
* location along with the length in bytes and value to set
* Expected Result - Since it does not have an invalid length or
* invalid pointer it should successfully set value and return
* enum.
****************************************************************/
void test_memset_valid(void **state)
{
	uint8_t *src = &set[0];
	uint8_t value = 5;
	enum memory_status status = my_memset(src,length,value);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

/****************************************************************
* test_memzero_invalid_pointer() - Function to test NULL pointer
* check in my_memzero function.
* Input parameter - For this we send src as NULL with some length
* Expected Result - Since an invalid(NULL) pointer is passed as a
* parameter the function should return an INVALID_MEMORY_POINTER
* emum
****************************************************************/
void test_memzero_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	enum memory_status status = my_memzero(src,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

/****************************************************************
* test_memzero_valid() - Function to test my_memzero function to
* set zeros in memory
* Input parameter - For this we send a pointer to a valid memory
* location along with the length in bytes
* Expected Result - Since it does not have an invalid length or
* invalid pointer it should successfully set zeros and return
* enum.
****************************************************************/
void test_memzero_valid(void **state)
{
	uint8_t *src = &set[5];
	enum memory_status status = my_memzero(src,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

/****************************************************************
* test_reverse_invalid_pointer() - Function to test NULL pointer
* check in my_reverse function.
* Input parameter - For this we can send src as NULL and some
* length
* Expected Result - Since an invalid(NULL) pointer is passed as a
* parameter the function should return an INVALID_MEMORY_POINTER
* emum
****************************************************************/
void test_reverse_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	enum memory_status status = my_reverse(src,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

/****************************************************************
* test_reverse_odd() - Function to test my_reverse function with
* odd length
* Input parameter - For this we send a pointer to a valid memory
* location along with an odd length in bytes
* Assumption: Function is written to handle odd length cases as
* well
* Expected Result - Since it does not have an invalid length or
* invalid pointer it should successfully reverse odd memory and
* return enum.
****************************************************************/
void test_reverse_odd(void **state)
{
	uint8_t *src = &set[10];
	enum memory_status status = my_reverse(src,odd_length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

/****************************************************************
* test_reverse_even() - Function to test my_reverse function with
* even length
* Input parameter - For this we send a pointer to a valid memory
* location along with an even length in bytes
* Expected Result - Since it does not have an invalid length or
* invalid pointer it should successfully reverse even memory and
* return enum.****************************************************************/
void test_reverse_even(void **state)
{
	uint8_t *src = &set[10];
	enum memory_status status = my_reverse(src,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

/****************************************************************
* test_reverse_character() - Function to test my_reverse function
* with all characters
* Input parameter - For this we send a pointer to a memory with
* all 256 characters
* Expected Result - Since it does not have an invalid length or
* invalid pointer it should successfully reverse memory and
* return enum.
****************************************************************/
void test_reverse_character(void **state)
{
	uint8_t chr_set[256];
	uint8_t chr_check[256];
	uint16_t i;

	for(i=0;i<256;i++)
	{
		chr_set[i] = i;
		chr_check[i] = i;
	}

	uint8_t *src = chr_set;
	enum memory_status status = my_reverse(src,256);

	/*Check if the reversed string is equal to the sent string
	* from reverse*/
	for(i=0;i<256;i++)
	{
		if(chr_set[i]!=chr_check[255-i])
		{
			status = TRANSFER_FAILED;
			break;
		}
	}

	if(i == 256)
		assert_int_equal(status, SUCCESSFUL_TRANSFER);
	else assert_int_equal(status, TRANSFER_FAILED);
}

/*Function testing the unit tests by passing
* function pointers to cmoka_unit_test*/
int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
  	cmocka_unit_test(test_memmove_invalid_pointer),
    cmocka_unit_test(test_memmove_no_overlap),
    cmocka_unit_test(test_memmove_dst_in_src),
    cmocka_unit_test(test_memmove_src_in_dst),
	cmocka_unit_test(test_memset_invalid_pointer),
	cmocka_unit_test(test_memset_valid),
	cmocka_unit_test(test_memzero_invalid_pointer),
	cmocka_unit_test(test_memzero_valid),
	cmocka_unit_test(test_reverse_invalid_pointer),
	cmocka_unit_test(test_reverse_odd),
	cmocka_unit_test(test_reverse_even),
	cmocka_unit_test(test_reverse_character),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
