#include <string.h>

int strcmp(const char *a, const char *b)
{
	int i = 0;
	while(a[i] != '\0' && a[i] == b[i])
		++i;
	return a[i] - b[i];
}
