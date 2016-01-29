#include <ctype.h>

int isxdigit(int c)
{
	int lower_c = tolower(c);
	return isdigit(c) || ('a' <= lower_c && lower_c <= 'f');
}
