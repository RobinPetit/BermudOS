#include "memcpy.h"
#include "_memopti.h"

/* Decompose into 32-bit blocks and 8-bit blocks so transfer
   may be faster */
void *memcpy(void *dest, const void *src, size_t bytes)
{
	size_t word_blocks,
	       byte_blocks,
		   i;

	const WORD *word_src;
	WORD *word_dest; 
	const BYTE *byte_src; 
	BYTE *byte_dest;

	split_bytes(bytes, &word_blocks, &byte_blocks,
	            dest, &word_dest, &byte_dest,
				src, &word_src, &byte_src);

	for(i = 0; i < word_blocks; ++i)
		word_dest[i] = word_src[i];
	for(i = 0; i < byte_blocks; ++i)
		byte_dest[i] = byte_src[i];
	return dest;
}
