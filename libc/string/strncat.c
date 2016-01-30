#include <string.h>

char *strncat(char * restrict dest, const char * restrict src, size_t bytes)
{
	size_t i = 0;
	size_t dest_idx = strlen(dest);
	while(src[i] != '\0' && i < bytes)
		dest[dest_idx++] = src[i++];
	dest[dest_idx] = '\0';
	return dest;
}
