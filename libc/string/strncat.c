#include <string.h>

char *strncat(char * restrict dest, const char * restrict src, size_t bytes)
{
	int i = 0;
	int dest_idx = strlen(dest);
	while(src[i] != '\0' && i < bytes)
		dest[dest_idx++] = src[i++];
	dest[dest_idx] = '\0';
	return dest;
}
