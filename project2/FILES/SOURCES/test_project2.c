/******************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 02/28/2017
*
* File : test_project2.c
* Description : Source file for testing memory functions
*               -test_big_to_little_invalid()
*               -test_little_to_big_invalid()
*               -test_big_to_little_valid_conversion()
*               -test_little_to_big_valid_conversion()
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
*               -test_circbuf_allocate_free()
*               -test_circbuf_invalid_pointer()
*               -test_circbuf_non_initialized_buffer()
*               -test_circbuf_add_remove()
*               -test_circbuf_buffer_full()
*               -test_circbuf_buffer_empty()
*               -test_circbuf_wrap_add()
*               -test_circbuf_wrap_remove()
*               -test_circbuf_over_fill()
*               -test_circbuf_over_empty()
*
* Tester : Virag Gada, MS in Embedded Systems
* Testing environment : To test the functions we need
* to install the Cmocka framework libraries in our folder
* path and make changes to the test Makefile to include
* our source files and test files.
********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "data.h"
#include "memory.h"
#include "circbuff.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*********************************************************
* Defining global variables required for out test function
* length and odd_length to provide odd and even lengths
* set[32] array to behave as a memory
* length_buff gives length of buffer to access
* data[11] array to behave as a buffer
*********************************************************/
uint32_t length = 10;
uint32_t odd_length = 11;
uint8_t set[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
uint8_t length_buff = 10;
uint8_t data[11] = {1,2,3,4,5,6,7,8,9,10,11};

/************************************************************
* test_big_to_little_invalid() - Function to test NULL pointer
* check in bit_to_little32 function.
* Input parameter - For this we send the NULL pointer as an input
* parameter along with some length
* Expected Result - Since an invalid(NULL) pointer is passed as a
* parameter the function should return an INVALID_POINTER emum
*************************************************************/
void test_big_to_little_invalid(void **state)
{
	uint32_t *ptr = NULL;
	uint32_t length = 4;
	enum data_status status = big_to_little32(ptr,length);
	assert_int_equal(status, INVALID_POINTER);
}

/************************************************************
* test_little_to_big_invalid() - Function to test NULL pointer
* check in little_to_big32 function.
* Input parameter - For this we send the NULL pointer as an input
* parameter along with some length
* Expected Result - Since an invalid(NULL) pointer is passed as a
* parameter the function should return an INVALID_POINTER emum
*
*************************************************************/
void test_little_to_big_invalid(void **state)
{
	uint32_t *ptr = NULL;
	uint32_t length = 4;
	enum data_status status = little_to_big32(ptr,length);
	assert_int_equal(status, INVALID_POINTER);
}

/************************************************************
* test_big_to_little_valid_conversion() - Function to test a
* valid conversion using big_to_little32 function.
* Input parameter - For this we send a pointer to a valid data
* along with the length in bytes
* Expected Result - Since it does not have an invalid pointer or
* invalid length it should successfully convert data and return
* enum.
*************************************************************/
void test_big_to_little_valid_conversion(void **state)
{
	uint32_t data = 0x12345678;
	uint32_t *ptr = &data;
	uint32_t length = 4;
	enum data_status status = big_to_little32(ptr,length);
	assert_int_equal(status, SUCCESSFUL_CONVERSION);
}

/************************************************************
* test_little_to_big_valid_conversion() - Function to test a
* valid conversion using little_to_big32 function.
* Input parameter - For this we send a pointer to a valid data
* along with the length in bytes
* Expected Result - Since it does not have an invalid pointer or
* invalid length it should successfully convert data and return
* enum
*************************************************************/
void test_little_to_big_valid_conversion(void **state)
{
	uint32_t data = 0x12345678;
	uint32_t *ptr = &data;
	uint32_t length = 4;
	enum data_status status = little_to_big32(ptr,length);
	assert_int_equal(status, SUCCESSFUL_CONVERSION);
}

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
* return enum.
****************************************************************/
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

/***********************************************************************
* test_circbuf_allocate_free() - Function to test cbuffer_memoryAllocate
* function and cbuffer_Destroy to check if buffer function can be used
* to allocate and free memory from heap
* Input parameter - For this we send the circbuff pointer and length
* to memory allocate function and pass it again to the destory function
* Expected Result - Receive a NO_ERROR enum from the functions
***********************************************************************/
void test_circbuf_allocate_free(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_Destroy(test_buffer,cbufferT);
	assert_int_equal(status, NO_ERROR);
}

/***********************************************************************
* test_circbuf_invalid_pointer() - Function to test if circbuff function
* can handle invalid pointer(NULL)
* Input parameter - For this we send the a NULL pointer to the
* cbuffer_full function
* Expected Result - Receive a NULL_POINTER enum from the function
***********************************************************************/
void test_circbuf_invalid_pointer(void **state)
{
	cbuff_state status = cbuffer_full(NULL);
	assert_int_equal(status,NULL_POINTER);
}

/***********************************************************************
* test_circbuf_non_initialized_buffer() - Function to test if circular
* buffer is initialized before using
* Input parameter - For this we allocate memory to the circular buffer
* and send it to initialize function
* Expected Result - Check if head and tail point at the buffer and set
* NO_ERROR enum
***********************************************************************/
void test_circbuf_non_initialized_buffer(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;
	cbuffer_init(test_buffer);
	cbuff_state status;
	if(((test_buffer->head) == (test_buffer->buffer)) && ((test_buffer->tail) == (test_buffer->buffer)))
		{
			status = NO_ERROR;
		}
	else status = ERROR;
	assert_int_equal(status, NO_ERROR);
}

/***********************************************************************
* test_circbuf_add_remove() - Function to test if circular buffer can
* add and remove data to the buffer
* Input parameter - For this we initialize buffer and add data to it
* and then remove the data and check for the returned enum
* Expected Result - Receive a NO_ERROR enum from the functions
***********************************************************************/
void test_circbuf_add_remove(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;
	cbuffer_init(test_buffer);
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status = cbuffer_remove(test_buffer,length_buff);
	assert_int_equal(status, NO_ERROR);
}

/***********************************************************************
* test_circbuf_buffer_full() - Function to test if circular buffer is
* full and return corresponding enum
* Input parameter - For this we initialize buffer and add data to it
* until buffer is full
* Expected Result - Receive a BUFFER_FULL enum from the function
***********************************************************************/
void test_circbuf_buffer_full(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;
	cbuffer_init(test_buffer);
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status = cbuffer_full(test_buffer);
	assert_int_equal(status, BUFFER_FULL);
}

/***********************************************************************
* test_circbuf_buffer_empty() - Function to test if circular buffer is
* empty and return corresponding enum
* Input parameter - For this we initialize buffer and add no data to it
* but directly call the remove function
* Expected Result - Since buffer is already empty we should receive a
* BUFFER_EMPTY enum from the function
***********************************************************************/
void test_circbuf_buffer_empty(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_empty(test_buffer);
	assert_int_equal(status, BUFFER_EMPTY);
}

/***********************************************************************
* test_circbuf_wrap_add() - Function to test if circular buffer can wrap
* near the boundary when data is added to it
* Input parameter - For this we initialize buffer and add data to it
* until buffer is full and check the head pointer with its previous value
* Expected Result - If the head pointer and previous value point
* at the same position then there is no error
***********************************************************************/
void test_circbuf_wrap_add(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;	cbuffer_init(test_buffer);
	uint8_t *last = (uint8_t *)(test_buffer->head);
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status;
	if((test_buffer->head)==last)
		status = NO_ERROR;
	else status = ERROR;

	assert_int_equal(status, NO_ERROR);
}

/***********************************************************************
* test_circbuf_wrap_remove() - Function to test if circular buffer can
* wrap near the boundary when data is removed from it
* Input parameter - For this we initialize buffer and add data to it
* until buffer is full and remove the same amount of data then check the
* tail pointer with its previous value
* Expected Result - If the tail pointer and previous value point
* at the same position then there is no error
***********************************************************************/
void test_circbuf_wrap_remove(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;
	cbuffer_init(test_buffer);
	uint8_t *last = (uint8_t *)(test_buffer->tail);
	cbuffer_add(test_buffer,data,length_buff);
	cbuffer_remove(test_buffer,length_buff);
	cbuff_state status;
	if((test_buffer->tail)==last)
		status = NO_ERROR;
	else status = ERROR;

	assert_int_equal(status, NO_ERROR);
}

/***********************************************************************
* test_circbuf_over_fill() - Function to test if circular buffer can
* handle when more data is added than its size
* Input parameter - For this we initialize buffer and add data more
* than its capacity
* Expected Result - Once the buffer is full if anymore data is addded to
* it, it will return a BUFFER_FULL enum from the function
***********************************************************************/
void test_circbuf_over_fill(void **state)
{
	CircBuff *test_buffer = (CircBuff *) malloc(sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_add(test_buffer,data,length_buff+1);
	assert_int_equal(status, BUFFER_FULL);
}


/***********************************************************************
* test_circbuf_over_empty() - Function to test if circular buffer can
* handle when more data is removed than available
* Input parameter - For this we initialize buffer and call remove function
* Expected Result - Since the buffer is already empty if we rempve anymore
* data from it it will return a BUFFER_EMPTY enum from the function
***********************************************************************/
void test_circbuf_over_empty(void **state)
{
	CircBuff *test_buffer = (CircBuff *) malloc(sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buffer->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buffer->buffer = cbufferT;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_remove(test_buffer,1);
	assert_int_equal(status, BUFFER_EMPTY);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
	cmocka_unit_test(test_circbuf_allocate_free),
	cmocka_unit_test(test_circbuf_invalid_pointer),
	cmocka_unit_test(test_circbuf_non_initialized_buffer),
	cmocka_unit_test(test_circbuf_add_remove),
	cmocka_unit_test(test_circbuf_buffer_full),	
	cmocka_unit_test(test_circbuf_buffer_empty),
    	cmocka_unit_test(test_circbuf_wrap_add),
    	cmocka_unit_test(test_circbuf_wrap_remove),
    	cmocka_unit_test(test_circbuf_over_fill),
    	cmocka_unit_test(test_circbuf_over_empty),
	cmocka_unit_test(test_big_to_little_invalid),
    	cmocka_unit_test(test_little_to_big_invalid),
    	cmocka_unit_test(test_big_to_little_valid_conversion),
    	cmocka_unit_test(test_little_to_big_valid_conversion),
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

