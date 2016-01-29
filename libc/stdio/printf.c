#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <mem/_memtypes.h>
#include "../../kernel/terminal/terminal.h"
#include "printf.h"

#define BUFFER_LENGTH 32

static int find_flags(BYTE *, const char * restrict);
static int find_width(BYTE *, const char * restrict);
static int find_precision(BYTE *, const char * restrict);
static int find_length_modifier(BYTE *, const char * restrict);
static int print_arg(const struct printf_arg_s *, va_list *);

static int get_int_from_str(const char * restrict, int *);

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
	struct printf_arg_s arg;

	while(format[i] != '\0')
	{
		if(format[i] == '%')
		{
			i += find_flags(&arg.flags, &format[i+1]);
			i += find_width(&arg.width, &format[i+1]);
			i += find_precision(&arg.precision, &format[i+1]);
			i += find_length_modifier(&arg.len_modifier, &format[i+1]);
			arg.conversion_spec = format[i];
			if(format[i] != '\0')
				print_arg(&arg, &arg_list);
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
			*flag |= ZERO;
			break;
		case '-':
			*flag |= MINUS;
			break;
		case '+':
			*flag |= PLUS;
			break;
		case ' ':
			*flag |= SPACE;
			break;
		default:
			loop = false;
			break;
		}
		++i;
	}
	return i;
}

static int find_width(BYTE *width, const char * restrict str)
{
	int ret;
	int value;
	*width = (*str == '*') ? ASTERISK : 0;
	if(*width != 0)
		return 1;
	ret = get_int_from_str(str, &value);
	*width = (BYTE)(value);
	return ret;
}

static int find_precision(BYTE *precision, const char * restrict str)
{
	int ret;
	int value;
	*precision = NOT_MENTIONNED;
	if(*str != '.')
		return 0;
	if(str[1] == '*')
	{
		*precision = ASTERISK;
		return 1;
	}
	ret = get_int_from_str(str, &value);
	*precision = (BYTE)(value);
	return ret;
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

static int print_arg(const struct printf_arg_s *fmt_arg, va_list *arg_list)
{
	static const char *lower_digits = "0123456789abcdef";
	static const char *upper_digits = "0123456789ABCDEF";
	const char *used_digits = (fmt_arg->conversion_spec == 'X' ? upper_digits : lower_digits);
	int idx = BUFFER_LENGTH-2;
	unsigned radix = ((fmt_arg->conversion_spec == 'd' || fmt_arg->conversion_spec == 'i') ? 10 :
	                  (fmt_arg->conversion_spec == 'o' ? 8 : 16));
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
	switch(fmt_arg->conversion_spec)
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
		while(arg.i_arg != 0)
		{
			buffer[idx--] = used_digits[arg.i_arg%radix];
			arg.i_arg /= radix;
		}
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

static int get_int_from_str(const char * restrict str, int *value)
{
	int i = 0;
	*value = 0;
	while(isdigit(str[i]))
	{
		*value *= 10;
		*value += str[i++] - '0';
	}
	return i;
}

