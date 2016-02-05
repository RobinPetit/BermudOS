#ifndef BERMUDOS_STDIO_H
#define BERMUDOS_STDIO_H

#include <stdarg.h>

int printf(const char * restrict, ...);
int vprintf(const char * restrict, va_list);

int sprintf(char *, const char *, ...);
int vsprintf(char *, const char *, va_list);

int puts(const char * restrict);

int putchar(int);

#endif /* BERMUDOS_STDIO_H */
