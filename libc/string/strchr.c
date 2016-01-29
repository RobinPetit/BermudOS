#include <string.h>

char *strchr(const char *str, int c)
{
	int i = 0;
	while(str[i] != '\0' && str[i] != c)
		++i;
	return (char *)((str[i] == '\0') ? NULL : &str[i]);
}
