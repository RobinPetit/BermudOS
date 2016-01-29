#include <string.h>

char *strcat(char * restrict dest, const char * restrict src)
{
	int i = 0;
	int dest_idx = strlen(dest);
	while(src[i] != '\0')
		dest[dest_idx++] = src[i++];
	dest[dest_idx] = '\0';
	return dest;
}
