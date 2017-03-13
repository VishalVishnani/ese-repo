/******************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 02/28/2017
*
* File : test_data.c
* Description : Source file for testing data functions
*               -test_big_to_little_invalid()
*               -test_little_to_big_invalid()
*               -test_big_to_little_valid_conversion()
*               -test_little_to_big_valid_conversion()
* Tester : Virag Gada, MS in Embedded Systems
* Testing environment : To test the functions we need
* to install the Cmocka framework libraries in our folder
* path and make changes to the test Makefile to include
* our source files and test files.
******************************************************/

#include<stdio.h>
#include<stdint.h>
#include"data.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

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
	double *ptr = NULL;
	double length = 4;
	enum data_status status = big_to_little32((uint32_t *)ptr,length);
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
	double *ptr = NULL;
	double length = 4;
	enum data_status status = little_to_big32((uint32_t *)ptr,length);
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

/*Function testing the unit tests by passing
* function pointers to cmoka_unit_test*/
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
