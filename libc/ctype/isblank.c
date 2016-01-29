#include <ctype.h>
#include <string.h>

int isblank(int c)
{
	return strchr(" \t", c) != NULL;
}
