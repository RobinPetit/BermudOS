#include <string.h>

void *memchr(const void *src, int value, size_t bytes)
{
	BYTE byte_value = (BYTE)(value);
	const BYTE *byte_src = (const BYTE *)(src);
	int i = 0;
	while(i < bytes && byte_src[i] != byte_value)
		++i;
	return (void *)((byte_src[i] == byte_value) ? &byte_src[i] : NULL);
}
