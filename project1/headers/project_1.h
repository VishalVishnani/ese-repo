#ifndef PROJECT_1_H_INCLUDED
#define PROJECT_1_H_INCLUDED

/********************************************
 * The function is used to call test_data1(),
 * test_data2() and test_memory() to test
 * functions in data.c and memory.c
 *******************************************/
void project_1_report(void);

/*********************************************************
 * The function is used to test the functions
 * big_to_little32() and little_to_big32() with set_1 data
 *********************************************************/
void test_data1(void);

/********************************************
 * The function is used to test the functions
 * my_itoa() and my_atoi() using set_2 data
 ********************************************/
void test_data2(void);

/*********************************************
 * The function is used to test functions like
 * my_reverse(), my_memset(), my_memmove() and
 * my_memzero() with set_2 data
 *********************************************/
void test_memory(void);
#endif // PROJECT_1_H_INCLUDED
