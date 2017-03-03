/*
 * test_circbuff.c
 *
 *  Created on: Feb 28, 2017
 *      Author: viga7710
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "circbuff.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

uint8_t length_buff = 10;
uint8_t data[11] = {1,2,3,4,5,6,7,8,9,10,11};

void test_circbuf_allocate_free(void **state)
{
	CircBuff *test_buff = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuff_state status = cbuffer_memoryAllocate(test_buff,length_buff);
	assert_int_equal(status, NO_ERROR);
}

void test_circbuf_invalid_pointer(void **state)
{
	CircBuff *test_buff = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuff_state status = cbuffer_memoryAllocate(test_buff,0);
	assert_int_not_equal(status, BUFFER_ALLCATION_FAILURE);
}

void test_circbuf_non_initialized_buffer(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	(test_buffer->length) = length_buff;
	cbuff_state status;
	if((test_buffer->head) == NULL || (test_buffer->buffer) == NULL || (test_buffer->tail) == NULL)
		{
			status = ERROR;
		}
	else status = NO_ERROR;
	assert_int_equal(status, ERROR);
}

void test_circbuf_add_remove(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	(test_buffer->length) = length_buff;
	cbuffer_memoryAllocate(test_buffer,length_buff);
	cbuffer_init(test_buffer);	
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status = cbuffer_remove(test_buffer,length_buff);
	assert_int_equal(status, NO_ERROR);
}

void test_circbuf_buffer_full(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status = cbuffer_full(test_buffer);
	assert_int_equal(status, BUFFER_FULL);
}

void test_circbuf_buffer_empty(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_empty(test_buffer);
	assert_int_equal(status, BUFFER_EMPTY);
}

void test_circbuf_wrap_add(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	uint8_t *last = (uint8_t *)(test_buffer->head);
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status;	
	if((test_buffer->head)==last)
		status = NO_ERROR;
	else status = ERROR;

	assert_int_equal(status, NO_ERROR);
}

void test_circbuf_wrap_remove(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
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

void test_circbuf_over_fill(void **state)
{
	CircBuff *test_buffer = (CircBuff *) malloc(sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_add(test_buffer,data,length_buff+1);
	assert_int_equal(status, BUFFER_FULL);
}

void test_circbuf_over_empty(void **state)
{
	CircBuff *test_buffer = (CircBuff *) malloc(sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
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
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}

