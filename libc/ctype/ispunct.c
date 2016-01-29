#include <ctype.h>
#include <stddef.h>

int ispunct(int c)
{
	return strchr("!\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~", c) != NULL;
}
