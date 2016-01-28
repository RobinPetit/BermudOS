#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "../../kernel/_memtypes.h"

enum
{
	MINUS=0,  /* left justifies */
	PLUS,     /* forces to sign the value */
	SPACE,    /* adds a space if no sign is written */
	SHARP,    /* explicits the base the number is written in */
	ZERO      /* uses '0' as padding instead of ' ' */
};

enum
{
	NONE=0,     /* no modifier is given (default) */
	CHAR,       /* hh */
	SHORT,      /* h */
	LONG,       /* l */
	LONGLONG,   /* ll */
	SIZE_T,     /* z */
	INTMAX_T,   /* j */
	PTRDIFF_T,  /* t */
	LONGDOUBLE  /* L */
};

static int find_flags(BYTE *, const char * restrict);
static int find_length_modifier(BYTE *, const char * restrict);

int printf(const char * restrict format, ...)
{
	int return_value;
	va_list arg_list;
	va_start(arg_list, format);
	return_value = vprintf(format, arg_list);
	va_end(arg_list);
	return return_value;
}

int vprintf(const char * restrict format, va_list arg_list)
{
	ptrdiff_t i = 0;
	BYTE flags;
	BYTE len_modifier = NONE;
	BYTE conversion_specifier;

	while(format[i] != '\0')
	{
		if(format[i] == '%')
		{
			i += find_flags(&flags, &format[i+1]);
			i += find_length_modifier(&len_modifier, &format[i+1]);
			if(format[i+1] != '\0')
				conversion_specifier = format[i++];
		}
		else
		{
			putchar(format[i]);
		}
		++i;
	}

	return 0;
}

static int find_flags(BYTE *flag, const char * restrict str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		switch(str[i])
		{
		case '0':
			*flag |= (1 << ZERO);
			break;
		case '-':
			*flag |= (1 << MINUS);
			break;
		case '+':
			*flag |= (1 << PLUS);
			break;
		case ' ':
			*flag |= (1 << SPACE);
			break;
		default:
			break;
		}
		++i;
	}
	return i;
}

static int find_length_modifier(BYTE *modifier, const char * restrict str)
{
	if(*str == 'h')
	{
		if(str[1] == 'h')
			*modifier = CHAR;
		else
			*modifier = SHORT;
	}
	else if(*str == 'l')
	{
		if(str[1] == 'l')
			*modifier = LONGLONG;
		else
			*modifier = LONG;
	}
	else if(*str == 'j')
		*modifier = INTMAX_T;
	else if(*str == 'z')
		*modifier = SIZE_T;
	else if(*str == 't')
		*modifier = PTRDIFF_T;
	else if(*str == 'L')
		*modifier = LONGDOUBLE;
	return *modifier == NONE ? 0 : ((*modifier == CHAR || *modifier == LONGLONG) ? 2 : 1);
}
