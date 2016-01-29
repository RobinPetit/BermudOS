#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <mem/_memtypes.h>
#include "../../kernel/terminal/terminal.h"

#define BUFFER_LENGTH 32

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
static int print_arg(BYTE, BYTE, BYTE, va_list *);

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

	while(format[i] != '\0')
	{
		if(format[i] == '%')
		{
			i += find_flags(&flags, &format[i+1]);
			i += find_length_modifier(&len_modifier, &format[i+1]);
			if(format[i] != '\0')
				print_arg(flags, len_modifier, format[i], &arg_list);
			else
				break;
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
	bool loop = true;
	int i = 0;
	while(str[i] != '\0' && loop)
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
			loop = false;
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
	return (*modifier == NONE ? 0 : ((*modifier == CHAR || *modifier == LONGLONG) ? 2 : 1));
}

static int print_arg(BYTE flags, BYTE length_modifier, BYTE conversion_specifier, va_list *arg_list)
{
	static const char *lower_digits = "0123456789abcdef";
	static const char *upper_digits = "0123456789ABCDEF";
	const char *used_digits = (conversion_specifier == 'X' ? upper_digits : lower_digits);
	int idx = BUFFER_LENGTH-2;
	unsigned radix = ((conversion_specifier == 'd' || conversion_specifier == 'i') ? 10 :
	                  (conversion_specifier == 'o' ? 8 : 16));
	char buffer[BUFFER_LENGTH];
	bool negative = false;
	union
	{
		/*void *p_arg;*/
		int i_arg;
		/*unsigned u_arg;*/
		/*char c_arg;*/
		/*short s_arg;*/
		/*long l_arg;*/
		/*long long ll_arg;*/
	} arg;

	memsetb(buffer, '\0', BUFFER_LENGTH);
	switch(conversion_specifier)
	{
	case 'd':
	case 'i':
	case 'o':
	case 'x':
	case 'X':
		arg.i_arg = va_arg(*arg_list, int);
		if(arg.i_arg < 0)
		{
			negative = true;
			arg.i_arg = -arg.i_arg;
		}
		do
		{
			buffer[idx--] = used_digits[arg.i_arg%radix];
			arg.i_arg /= radix;
		}
		while(arg.i_arg != 0);
		if(negative)
			buffer[idx--] = '-';
		break;
	case '%':
		buffer[idx--] = '%';
		break;
	default:
		break;
	}
	terminal_putstring(&buffer[idx+1]);
}

