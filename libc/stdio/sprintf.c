#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <mem/_memtypes.h>
#include <strconv/strconv.h>
#include "sprintf.h"

static int find_flags(BYTE *, const char * restrict);
static int find_width(BYTE *, const char * restrict);
static int find_precision(BYTE *, const char * restrict);
static int find_length_modifier(BYTE *, const char * restrict);
static int append_formatted_arg(char * restrict, struct sprintf_arg_s *, va_list *);

int sprintf(char *dest, const char * restrict format, ...)
{
	int return_value;
	va_list arg_list;
	va_start(arg_list, format);
	return_value = vsprintf(dest, format, arg_list);
	va_end(arg_list);
	return return_value;
}

int vsprintf(char * restrict dest, const char * restrict format, va_list args)
{
	int ret = 0;
	int i = 0;
	struct sprintf_arg_s arg;

	while(format[i] != '\0')
	{
		if(format[i] == '%')
		{
			i += find_flags(&arg.flags, &format[i+1]);
			i += find_width(&arg.width, &format[i+1]);
			i += find_precision(&arg.precision, &format[i+1]);
			i += find_length_modifier(&arg.len_modifier, &format[i+1]);
			arg.conversion_spec = format[++i];
			printf("flags = 0x%X, width = 0x%X, prec = 0x%X, conversion specifier = ", arg.flags, arg.width, arg.precision);
			putchar(arg.conversion_spec); putchar('\n');
			if(format[i] == '\0')
				break;
			else
			{
				int j;
				for(j = 0; j < 1000000000; ++j);
				ret += append_formatted_arg(&dest[ret], &arg, &args);
			}
		}
		else
			dest[ret++] = format[i];
		++i;
	}
	dest[ret] = '\0';
	return ret;
}

static int find_flags(BYTE *flag, const char * restrict str)
{
	bool loop = true;
	int i = 0;
	*flag = 0;
	while(str[i] != '\0' && loop)
	{
		if(str[i] == '0')
		{
			if(*flag & ZERO)  /* if flag ZERO is already set */
				return i;    /* 	we might have %00d so 2nd char '0' must be trated as width */
			*flag |= ZERO;
		}
		else if(str[i] == '-')
			*flag |= MINUS;
		else if(str[i] == '+')
			*flag |= PLUS;
		else if(str[i] == ' ')
			*flag |= SPACE;
		else if(str[i] == '#')
			*flag |= SHARP;
		else
		{
			loop = false;
			--i;
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
	ret = str_to_int(str, &value, 10);
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
	ret = str_to_int(&str[1], &value, 10);
	*precision = (BYTE)(value);
	return ret+1;
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
	else
		*modifier = NONE;
	return (*modifier == NONE ? 0 : ((*modifier == CHAR || *modifier == LONGLONG) ? 2 : 1));
}

static int append_formatted_arg(char * restrict dest, struct sprintf_arg_s *arg, va_list *arg_list)
{
	char *buf;
	size_t buf_len;
	int i = 0;
	int limit;
	int ret;
	switch(arg->conversion_spec)
	{
	case 'c':  /* character */
		limit = arg->width - 1;
		if(!(arg->flags & MINUS))  /* if not left-aligned */
			for(i = 0; i < limit; ++i)
				dest[i] = ' ';
		dest[i] = (char)va_arg(*arg_list, int);  /* char is promoted to int in '...' */
		if(arg->flags & MINUS)  /* if left-aligned */
			for(i = 0; i < limit; ++i)
				dest[1+i] = ' ';
		ret = arg->width == 0 ? 1 : arg->width;
		break;
	case 's':  /* string */
		buf = va_arg(*arg_list, char *);
		if(buf == NULL)
			buf = "<NULL>";
		buf_len = strlen(buf);
		/* if precision is given, no more characters are written than provided */
		if(arg->precision != NOT_MENTIONNED && arg->precision < buf_len)
				buf_len = arg->precision;
		limit = arg->width - buf_len;
		if(!(arg->flags & MINUS))  /* if not left-aligned */
			for(i = 0; i < limit; ++i)
				dest[i] = ' ';
		strncpy(dest + (arg->flags & MINUS || limit <= 0 ? 0 : limit), buf, buf_len);
		if(arg->flags & MINUS)  /* if left-aligned */
			for(i = 0; i < limit; ++i)
				dest[buf_len+i] = ' ';
		ret = (limit > 0) ? buf_len + limit : buf_len;
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

