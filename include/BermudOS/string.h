#ifndef BERMUDOS_STRING_H
#define BERMUDOS_STRING_H

#include <stddef.h>
#include <mem/_memtypes.h>

/* STRINGS */

  /* copy */

char *strcpy(char * restrict, const char * restrict);
char *strncpy(char * restrict, const char * restrict, size_t);

  /* concatenation */

char *strcat(char * restrict, const char * restrict);
char * strncat(char * restrict, const char * restrict, size_t);

  /* comparison */

int strcmp(const char *, const char *);
int strncmp(const char *, const char *, size_t);

  /* search */

char *strchr(const char *, int);
size_t strcspn(const char *, const char *);
char *strpbrk(const char *, const char *);
char *strrchr(const char *, int);
size_t strspn(const char *, const char *);
char *strstr(const char *, const char *);
char *strtok(char * restrict, const char * restrict);

  /*  */

size_t strlen(const char *);

/* MEMORY */

#define memset(add, byte, length) memsetb(add, byte, length)
void *memsetb(void *, BYTE, size_t);
void *memsetw(void *, WORD, size_t);
void *memsetd(void *, DWORD, size_t);

void *memcpy(void *, const void *, size_t);
void *memmove(void *, const void *, size_t);
int memcmp(const void *, const void *, size_t);
void *memchr(const void *, int, size_t);

#endif /* BERMUDOS_STRING_H */
