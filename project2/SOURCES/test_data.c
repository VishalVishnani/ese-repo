/*
 * test_data.c
 *
 *  Created on: Feb 28, 2017
 *      Author: viga7710
 */

#include<stdio.h>
#include<stdint.h>
#include"data.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void test_big_to_little_invalid(void **state)
{
	//double data = 0x12345678;
	double *ptr = NULL;
	double length = 4;
	enum data_status status = big_to_little32((uint32_t *)ptr,length);
	assert_int_equal(status, INVALID_POINTER);
}

void test_little_to_big_invalid(void **state)
{
	//double data = 0x12345678;
	double *ptr = NULL;
	double length = 4;
	enum data_status status = little_to_big32((uint32_t *)ptr,length);
	assert_int_equal(status, INVALID_POINTER);
}

void test_big_to_little_valid_conversion(void **state)
{
	uint32_t data = 0x12345678;
	uint32_t *ptr = &data;
	uint32_t length = 4;
	enum data_status status = big_to_little32(ptr,length);
	assert_int_equal(status, SUCCESSFUL_CONVERSION);
}

void test_little_to_big_valid_conversion(void **state)
{
	uint32_t data = 0x12345678;
	uint32_t *ptr = &data;
	uint32_t length = 4;
	enum data_status status = little_to_big32(ptr,length);
	assert_int_equal(status, SUCCESSFUL_CONVERSION);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_big_to_little_invalid),
    cmocka_unit_test(test_little_to_big_invalid),
    cmocka_unit_test(test_big_to_little_valid_conversion),
    cmocka_unit_test(test_little_to_big_valid_conversion),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}

