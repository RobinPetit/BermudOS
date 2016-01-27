#include "_memopti.h"

void split_bytes(size_t bytes, size_t *w_blocks, size_t *b_blocks,
                  void *dest, WORD **w_dest, BYTE **b_dest,
				  const void *src, const WORD **w_src, const BYTE **b_src)
{
	*w_blocks = bytes / sizeof(WORD);
	*b_blocks = bytes % sizeof(WORD);

	*w_src = (const WORD *)(src);
	*w_dest = (WORD *)(dest);
	*b_src = (const BYTE *)(&w_src[(ptrdiff_t)(w_blocks)]);
	*b_dest = (BYTE *)(&w_dest[(ptrdiff_t)(w_blocks)]);
}
