#include <string.h>

char *strpbrk(const char *a, const char *b)
{
	size_t span = strcspn(a, b);
	return (char *)(a[span] == '\0' ? NULL : &a[span]);
}
