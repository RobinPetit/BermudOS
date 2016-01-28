#include "memcpy.h"

/* Decompose into 32-bit blocks and 8-bit blocks so transfer
   may be faster */
void *memcpy(void *dest, const void *src, size_t bytes)
{
	size_t dword_blocks = bytes / sizeof(DWORD),
	       byte_blocks = bytes % sizeof(DWORD),
	       i;

	const DWORD *dword_src = (const DWORD *)(src);
	DWORD *dword_dest = (DWORD *)(dest);
	const BYTE *byte_src = (const BYTE *)(dword_src[dword_blocks]);
	BYTE *byte_dest = (BYTE *)(dword_dest[dword_blocks]);

	for(i = 0; i < dword_blocks; ++i)
		dword_dest[i] = dword_src[i];
	for(i = 0; i < byte_blocks; ++i)
		byte_dest[i] = byte_src[i];
	return dest;
}
