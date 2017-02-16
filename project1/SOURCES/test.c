#include <stdio.h>
#include <stdint.h>
#include <test.h>


uint8_t test_littlebig(uint32_t data)
{
if(data & 0x0000000F)
	return 0;
else return 1;
}
