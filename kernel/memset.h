#ifndef MEMSET_H
#define MEMSET_H

#include "_memtypes.h"
#include <stddef.h>
#include "_memtypes.h"

void *memsetb(void *, BYTE, size_t);
void *memsetw(void *, WORD, size_t);
void *memsetd(void *, DWORD, size_t);

#endif /* MEMSET_H */
