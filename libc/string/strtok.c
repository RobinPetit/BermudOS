#include <string.h>

char *strtok(char * restrict str, const char * restrict delimiters)
{
	static char *keeper = NULL;
	static char *ret;
	if(str != NULL)
		keeper = str;
	while(*keeper != '\0' && strchr(delimiters, *keeper) != NULL)
	{
		*keeper = '\0';
		++keeper;
	}
	ret = keeper;
	while(*keeper != '\0' && strchr(delimiters, *keeper) == NULL)
		++keeper;
	if(*keeper != '\0')
	{
		*keeper = '\0';
		++keeper;
	}
	return (char *)((*ret == '\0') ? NULL : ret);
}
