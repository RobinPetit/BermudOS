#include <string.h>

void *memmove(void *dest, const void *src, size_t bytes)
{
	BYTE buffer[bytes];
	memcpy(buffer, src, bytes);
	memcpy(dest, buffer, bytes);
	return dest;
}
