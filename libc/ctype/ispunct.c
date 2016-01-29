#include <ctype.h>
#include <stddef.h>
#include <string.h>

int ispunct(int c)
{
	return strchr("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", c) != NULL;
}
