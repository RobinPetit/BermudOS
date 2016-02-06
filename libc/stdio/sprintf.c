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

static int append_number(char * restrict dest, uint64_t number, unsigned int radix, bool upper, struct sprintf_arg_s *args, bool negative)
{
	char *save = dest;
	unsigned int i;
	unsigned int nb_digits;
	static char buffer[64];  /* static array (so it is not re-allocated each time) that may contain any conversion of number */
	int width_minus_prec;
	if(args->flags & MINUS)
		args->flags &= ~ZERO;  /* do not use zeros to right-pad */
	if(radix < 2 || radix > 36)
		return 0;  /* if radix is not handled (or does not exist), write nothing */

	/* check sign */
	if(negative)
	{
		if((int64_t)number < 0)  /* if value is actually negative */
		{
			*dest++ = '-';
			number = -(int64_t)(number);  /* rest assured no unsigned conversion has corrupted the value*/
		}
		else
		{
			if(args->flags & PLUS)  /* if sign is forced to appear */
				*dest++ = '+';
			else if(args->flags & SPACE)  /* if a space must appear if no sign is necessary */
				*dest++ = ' ';
		}
	}

	/* check prefix */
	if(args->flags & SHARP)
	{
		if(radix == 0x10)
		{
			*dest++ = '0';
			*dest++ = upper ? 'X' : 'x';
		}
		else if(radix == 0x08)
			*dest++ = '0';
	}

	nb_digits = upper ? uint64_t_to_str_upper(buffer, number, radix) : uint64_t_to_str_lower(buffer, number, radix);
	if(nb_digits > args->precision)
		args->precision = nb_digits;  /* precision is the minimum number of digits */
	width_minus_prec = args->width - args->precision;
	/* check padding */
	if(!(args->flags & MINUS))  /* if not left-aligned */
	{
		memsetb(dest, args->flags & ZERO ? '0' : ' ', width_minus_prec);
		dest += width_minus_prec;
	}
	for(i = 0; i < args->precision - nb_digits; ++i)
		*dest++ = '0';
	strncpy(dest, buffer, nb_digits);
	dest += nb_digits;
	if(args->flags & MINUS)  /* if left-aligned */
	{
		memset(dest, ' ', width_minus_prec);
		dest += width_minus_prec;
	}
	return dest - save;
}

static int append_formatted_arg(char * restrict dest, struct sprintf_arg_s *arg, va_list *arg_list)
{
	char *buf;
	void *ptr;
	size_t buf_len;
	int i = 0;
	int limit;
	int ret;
	int radix;
	uint64_t number;
	bool upper;
	bool negative;

	switch(arg->conversion_spec)
	{
	case '%':
		dest[0] = '%';
		break;
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
	case 'p':  /* address */
		ptr = va_arg(*arg_list, void *);
		ret = sprintf(dest, "0x%08X", (uint32_t)(ptr));
		break;
	default:
		if(strchr("odixX", arg->conversion_spec) == NULL)
			return 0;
		/* init radix */
		if(arg->conversion_spec == 'o')
			radix = 0x08;
		else if(arg->conversion_spec == 'd' || arg->conversion_spec == 'i')
			radix = 0x0A;
		else
			radix = 0x10;

		/* determine whether lowercase or upper case must be used */
		upper = arg->conversion_spec == 'X';

		/* determien if value may be negative */
		negative = (radix == 0x0A);

		/* use length modifier */
		if(arg->len_modifier == LONGLONG)
			number = (negative) ? va_arg(arg_list, int64_t) : va_arg(arg_list, uint64_t);
		else if(arg->len_modifier == NONE || arg->len_modifier == LONG)
			number = ((negative) ? (int64_t)va_arg(arg_list, int32_t) : (uint64_t)va_arg(arg_list, uint32_t));
		/* uint16_t is promoted to uint32_t */
		else if(arg->len_modifier == SHORT)
			number = ((negative) ? (int64_t)((int16_t)va_arg(arg_list, int32_t)) : (uint64_t)((uint16_t)va_arg(arg_list, uint32_t)));
		/* uint8_t is promoted to uint32_t */
		else if(arg->len_modifier == CHAR)
			number = (negative) ? (int64_t)((int8_t)va_arg(arg_list, int32_t)) : (uint64_t)((uint8_t)va_arg(arg_list, uint32_t));
		append_number(dest, number, radix, upper, arg, negative);
		break;
	}
	return ret;
}

