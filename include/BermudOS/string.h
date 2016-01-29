#ifndef BERMUDOS_STRING_H
#define BERMUDOS_STRING_H

#include <stddef.h>
#include <mem/_memtypes.h>

char *strrchr(const char *, int);
size_t strlen(const char *);

void *memsetb(void *, BYTE, size_t);
void *memsetw(void *, WORD, size_t);
void *memsetd(void *, DWORD, size_t);

void *memcpy(void *, const void *, size_t);

#endif /* BERMUDOS_STRING_H */
