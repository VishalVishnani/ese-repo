/*
 * test_memory.c
 *
 *  Created on: Feb 28, 2017
 *      Author: viga7710
 */



#include<stdio.h>
#include<stdint.h>
#include "memory.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

uint32_t length = 10;
uint32_t odd_length = 11;
uint8_t set[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

void test_memmove_invalid_pointer(void **state)
{
	uint8_t *src = &set[0];
	uint8_t *dst = NULL;
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

void test_memmove_no_overlap(void **state)
{
	uint8_t *src = &set[5];
	uint8_t *dst = &set[20];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_memmove_src_in_dst(void **state)
{
	uint8_t *src = &set[15];
	uint8_t *dst = &set[10];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_memmove_dst_in_src(void **state)
{
	uint8_t *src = &set[10];
	uint8_t *dst = &set[15];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}


void test_memset_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	uint8_t value = 5;
	enum memory_status status = my_memset(src,length,value);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

void test_memset_valid(void **state)
{
	uint8_t *src = &set[0];
	uint8_t value = 5;
	enum memory_status status = my_memset(src,length,value);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_memzero_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	enum memory_status status = my_memzero(src,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

void test_memzero_valid(void **state)
{
	uint8_t *src = &set[5];
	enum memory_status status = my_memzero(src,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_reverse_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	enum memory_status status = my_reverse(src,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

void test_reverse_odd(void **state)
{
	uint8_t *src = &set[10];
	enum memory_status status = my_reverse(src,odd_length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_reverse_even(void **state)
{
	uint8_t *src = &set[10];
	enum memory_status status = my_reverse(src,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

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

