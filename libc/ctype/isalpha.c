#include <ctype.h>

int isalpha(int c)
{
	return ('a' <= c && c <= 'z') || ('A' <= 'c' && c <= 'Z');
}
