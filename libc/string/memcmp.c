#include <string.h>

int memcmp(const void *a, const void *b, size_t bytes)
{
	const BYTE *byte_a = (const BYTE *)(a);
	const BYTE *byte_b = (const BYTE *)(b);
	int i = 0;
	while(i < bytes && byte_a[i] == byte_b[i])
		++i;
	return byte_a[i] - byte_b[i];
}
