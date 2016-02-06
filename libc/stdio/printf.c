#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <mem/_memtypes.h>
#include <strconv/strconv.h>
#include "../../kernel/terminal/terminal.h"
#include "printf.h"

static char buffer[512];  /* buffer to use sprintf and then write on screen */

int printf(const char * restrict format, ...)
{
	int return_value;
	va_list arg_list;
	va_start(arg_list, format);
	return_value = vsprintf(buffer, format, arg_list);
	terminal_putstring(buffer);
	va_end(arg_list);
	return return_value;
}

int vprintf(const char * restrict format, va_list arg_list)
{
	int ret = vsprintf(buffer, format, arg_list);
	terminal_putstring(buffer);
	return ret;
}

