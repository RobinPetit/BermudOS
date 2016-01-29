#include <string.h>

char *strncpy(char * restrict dest, const char * restrict src, size_t bytes)
{
	int i = 0;
	while(src[i] != '\0' && i < bytes)
		dest[i] = src[i++];
	return dest;
}
