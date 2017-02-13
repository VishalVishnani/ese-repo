#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

/**************************************************************
* my_memmove() - It takes the source address pointer and length
*                and moves the block of data to the destination
*                address.
* uint8_t *src - Pointer to the start of memory to be moved.
* uint8_t *dst - Pointer to the destination memory address.
* uint32_t length - Length of the data to be moved
* int8_t(return) - Byte to send error message
*                  0 for error, 1 for no error
**************************************************************/
int8_t my_memmove(uint8_t * src,uint8_t * dst, uint32_t length);

/**************************************************************
* my_memset() - It takes the source address pointer copies a
*               value up to the length specified.
* uint8_t *src - Pointer to the start of memory to be moved.
* uint32_t length - Length of the data to be moved.
* uint8_t value - Data byte that is to be copied.
* int8_t(return) - Byte to send error message
*                  0 for error, 1 for no error.
**************************************************************/
int8_t my_memset(uint8_t *src,uint32_t length,uint8_t value);

/**************************************************************
* my_memzero() - It takes the source address pointer and clears
*                (writes 0) memory up to the length specified.
* uint8_t *src - Pointer to the start of memory to be cleared.
* uint32_t length - Length of the data to be cleared.
* int8_t(return) - Byte to send error message
*                  0 for error, 1 for no error.
**************************************************************/
int8_t my_memzero(uint8_t* src,uint32_t length);

/*************************************************************
* my_reverse() - It takes a pointer to start of string and the
*                length up to which it needs to reverse.
* char *str - Pointer to the start of the string.
* int length - Length of string that needs to be reversed.
* int8_t(return) - Byte to send error message
*                  0 for error, 1 for no error.
**************************************************************/
int8_t my_reverse(uint8_t * src,uint32_t length);

#endif // MEMORY_H_INCLUDED
