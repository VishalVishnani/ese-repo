#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

/************************************************************
* my_itoa() - It takes a 32 bit data and base value and
*             converts it to a ascii string.
*
* int8_t *str - Pointer where output string will be stored.
* int32_t data - 32 bit data which needs to be converted
                 to string.
* int32_t base - Represents the base value to which the
*                input data needs to be stored(ex. 2,8,10,16).
* int8_t(return)- Pointer where data is converted to.
*************************************************************/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);

/************************************************************
* my_atoi() - The function takes a pointer to the input
*             string which is converted to a 32 bit data.
*
* int8_t *str - Pointer to input string.
* int32_t(return) - Converted 32 bit data.
*************************************************************/
int32_t my_atoi(int8_t * str);

/*************************************************************
* big_to_little32() - Takes a pointer to a location in memory
*                     and converts a specified length to
*                     little endian notation.
*
* uint32_t *data - Pointer to start of string
* uint32_t length - Length of string that needs to be
*                   converted
* int8_t(return) - Return 0 if string converted successfully
**************************************************************/
int8_t big_to_little32(uint32_t * data,uint32_t length);

/*************************************************************
* little_to_big32() - Takes a pointer to a location in
*                     memory and converts a specified
*                     length to big endian notation.
*
* uint32_t *data - Pointer to start of string
* uint32_t length - Length of string that needs to be
*                   converted
* int8_t(return) - Return 0 if string converted successfully
**************************************************************/
int8_t little_to_big32(uint32_t * data,uint32_t length);

/*************************************************************
* reverse() - It takes a pointer to start of string and the
*             length upto which it needs to reverse.
* char *str - Pointer to the start of the string.
* int length - Length of string that needs to be reversed.
**************************************************************/
void reverse(int8_t *str, int lenght);

/*************************************************************
stringLength() - Function to find the length of a string,
                 takes the pointer to start of the string as
                 input and checks till Null character
char *str - Pointer to start of string
uint8_t(return) -
*************************************************************/
uint8_t stringLength(int8_t *str);

#endif // DATA_H_INCLUDED
