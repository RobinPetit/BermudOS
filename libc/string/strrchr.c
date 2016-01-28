#include <string.h>

char *strrchr(const char *str, int c)
{
	size_t length = strlen(str);
	while(length > 0 && str[length] != c)
		--length;
	if(str[length] == c)
		return &str[length];
	else
		return NULL;
}

