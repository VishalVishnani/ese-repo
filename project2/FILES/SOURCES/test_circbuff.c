/******************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 02/28/2017
*
* File : test_memory.c
* Description : Source file for testing memory functions
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
#include "circbuff.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*********************************************************
* Defining global variables required for out test function
* length_buff gives length of buffer to access
* data[11] array to behave as a buffer
*********************************************************/
uint8_t length_buff = 10;
uint8_t data[11] = {1,2,3,4,5,6,7,8,9,10,11};

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
	CircBuff *test_buff = (CircBuff *) calloc(1,sizeof(CircBuff));
	uint8_t * cbufferT=NULL;
	(test_buff->length) = length_buff;
	cbufferT = cbuffer_memoryAllocate(cbufferT,length_buff);
	test_buff->buffer = cbufferT;
	cbuffer_init(test_buff);
	cbuff_state status = cbuffer_Destroy(test_buff,cbufferT);
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
	//CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	//cbuffer_memoryAllocate(test_buffer,length_buff);
	//(test_buffer->length) = length_buff;
	//cbuffer_init(test_buffer);
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

/*Function testing the unit tests by passing
* function pointers to cmoka_unit_test*/
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
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
