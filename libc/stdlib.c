#include "stdlib.h"
#include <stdint.h>

void *memcpy(void *dest, void *src, size_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++)
		*((uint8_t*)dest + i) = *((uint8_t*)src+i);
	return dest;
}
