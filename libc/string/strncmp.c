#include <string.h>

int strncmp(const char *a, const char *b, size_t bytes)
{
	int i = 0;
	while(a[i] != '\0' && i < bytes && a[i] == b[i])
		++i;
	return a[i] - b[i];
}
