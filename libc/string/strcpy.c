#include <string.h>

char *strcpy(char * restrict dest, const char * restrict src)
{
	int i = 0;
	while(src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return dest;
}
