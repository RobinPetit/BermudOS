#include <string.h>

size_t strcspn(const char *a, const char *b)
{
	size_t i = 0;
	while(strchr(b, a[i]) == NULL)
		++i;
	return i;
}
