#include <ctype.h>

int isprint(int c)
{
	return isblank(c) || isgraph(c);
}
