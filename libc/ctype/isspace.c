#include <ctype.h>
#include <stddef.h>
#include <string.h>

int isspace(int c)
{
	return strchr(" \f\n\r\t\v", c) != NULL;
}
