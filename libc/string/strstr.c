#include <string.h>

char *strstr(const char *a, const char *b)
{
	size_t i = 0;
	size_t j;
	size_t len_b = strlen(b);
	while(a[i] != '\0')
	{
		j = 0;
		while(a[i+j] == b[j])
			++j;
		if(j == len_b)
			return (char *)(&a[i]);
		++i;
	}
	return NULL;
}
