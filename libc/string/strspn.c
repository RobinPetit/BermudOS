#include <string.h>

size_t strspn(const char *a, const char *b)
{
	size_t i = 0;
	while(a[i] != '\0' && strchr(b, a[i]))
		++i;
	return i;
}
