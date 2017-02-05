#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{

  printf("\n%ld bytes for char",sizeof(char));
  printf("\n%ld bytes for int",sizeof(int));
  printf("\n%ld bytes for float",sizeof(float));
  printf("\n%ld bytes for short",sizeof(short));
  printf("\n%ld bytes for long",sizeof(long));
  printf("\n%ld bytes for long int",sizeof(long int));
  printf("\n%ld bytes for long long",sizeof(long long));
  printf("\n%ld bytes for int8_t",sizeof(int8_t));
  printf("\n%ld bytes for uint8_t",sizeof(uint8_t));
  printf("\n%ld bytes for uint16_t",sizeof(uint16_t));
  printf("\n%ld bytes for uint32_t",sizeof(uint32_t));
  printf("\n%ld bytes for char *",sizeof(char *));
  printf("\n%ld bytes for int *",sizeof(int *));
  printf("\n%ld bytes for float *",sizeof(float *));
  printf("\n%ld bytes for void *",sizeof(void *));
  printf("\n%ld bytes for void **",sizeof(void **));
  printf("\n%ld bytes for int8_t *",sizeof(int8_t *));
  printf("\n%ld bytes for int16_t *",sizeof(int16_t *));
  printf("\n%ld bytes for int32_t *",sizeof(int32_t *));
  printf("\n%ld bytes for size_t\n",sizeof(size_t));
  return 1;
}
