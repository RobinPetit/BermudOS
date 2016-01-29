#include <ctype.h>
#include <stddef.h>

int isspace(int c)
{
	return strchr(" \f\n\r\t\v", c) != NULL;
}
