#include "memset.h"

void *memset(void *address, int value, size_t bytes)
{
	size_t i;
	BYTE *byte_array = (BYTE *)(address);
	
	for(i = 0; i < bytes; ++i)
		byte_array[i] = value&0xFF;
	
	return address;
}
