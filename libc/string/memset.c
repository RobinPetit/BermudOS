#include <string.h>

void *memsetb(void *address, BYTE value, size_t bytes)
{
	size_t i;
	BYTE *byte_array = (BYTE *)(address);
	
	for(i = 0; i < bytes; ++i)
		byte_array[i] = value&0xFF;
	
	return address;
}

void *memsetw(void *address, WORD value, size_t blocks)
{
	size_t i;
	WORD *word_array = (WORD *)(address);

	for(i = 0; i < blocks; ++i)
		word_array[i] = value;

	return address;
}

void *memsetd(void *address, DWORD value, size_t blocks)
{
	size_t i;
	DWORD *dword_array = (DWORD *)(address);

	for(i = 0; i < blocks; ++i)
		dword_array[i] = value;

	return address;
}

