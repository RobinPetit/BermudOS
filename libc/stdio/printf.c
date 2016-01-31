#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <mem/_memtypes.h>
#include <strconv/strconv.h>
#include "../../kernel/terminal/terminal.h"
#include "printf.h"

#define BUFFER_LENGTH 32

static int find_flags(BYTE *, const char * restrict);
static int find_width(BYTE *, const char * restrict);
static int find_precision(BYTE *, const char * restrict);
static int find_length_modifier(BYTE *, const char * restrict);
static int print_arg(const struct printf_arg_s *, va_list *);

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
	unsigned int i = 0;
	struct printf_arg_s arg;

	while(format[i] != '\0')
	{
		if(format[i] == '%')
		{
			i += find_flags(&arg.flags, &format[i+1]);
			i += find_width(&arg.width, &format[i+1]);
			i += find_precision(&arg.precision, &format[i+1]);
			i += find_length_modifier(&arg.len_modifier, &format[i+1]);
			arg.conversion_spec = format[++i];
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
	ret = str_to_int(str, &value, 10);
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
	else
		*modifier = NONE;
	return (*modifier == NONE ? 0 : ((*modifier == CHAR || *modifier == LONGLONG) ? 2 : 1));
}

static int print_arg(const struct printf_arg_s *fmt_arg, va_list *arg_list)
{
	static unsigned int (*const int_to_str_fns[2])(char * restrict, int, int) =
	{
		int_to_str_lower, int_to_str_upper
	};
	static unsigned int (* const int8_t_to_str_fns[2])(char * restrict, int8_t, int) =
	{
		int8_t_to_str_lower, int8_t_to_str_upper
	};
	static unsigned int (* const int16_t_to_str_fns[2])(char * restrict, int16_t, int) =
	{
		int16_t_to_str_lower, int16_t_to_str_upper
	};
	static unsigned int (* const int32_t_to_str_fns[2])(char * restrict, int32_t, int) =
	{
		int32_t_to_str_lower, int32_t_to_str_upper
	};
	static unsigned int (* const uint32_t_to_str_fns[2])(char * restrict, uint32_t, int) =
	{
		uint32_t_to_str_lower, uint32_t_to_str_upper
	};
	unsigned radix = ((fmt_arg->conversion_spec == 'd' || fmt_arg->conversion_spec == 'i') ? 10 :
	                  (fmt_arg->conversion_spec == 'o' ? 8 : 16));
	char buffer[BUFFER_LENGTH];
	int lower_upper_idx = (fmt_arg->conversion_spec == 'X') ? 1 : 0;
	union
	{
		void *p_arg;
		int i_arg;
		unsigned int u_arg;
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
		if(fmt_arg->len_modifier == NONE)
			int_to_str_fns[lower_upper_idx](buffer, arg.i_arg, radix);
		else if(fmt_arg->len_modifier == CHAR)
			int8_t_to_str_fns[lower_upper_idx](buffer, (int8_t)(arg.i_arg), radix);
		else if(fmt_arg->len_modifier == SHORT)
			int16_t_to_str_fns[lower_upper_idx](buffer, (int16_t)(arg.i_arg), radix);
		else if(fmt_arg->len_modifier == LONG || fmt_arg->len_modifier == INTMAX_T
				|| fmt_arg->len_modifier == PTRDIFF_T)
			int32_t_to_str_fns[lower_upper_idx](buffer, (int32_t)(arg.i_arg), radix);
		/*else if(fmt_arg->len_modifier == LONGLONG)
			TODO: not handled yet */
		else if(fmt_arg->len_modifier == SIZE_T)
			uint32_t_to_str_fns[lower_upper_idx](buffer, (uint32_t)(arg.i_arg), radix);
		break;
	case 'u':
		arg.u_arg = va_arg(*arg_list, unsigned int);
		uint32_t_to_str_fns[lower_upper_idx](buffer, arg.u_arg, 10);
		break;
	case 'p':
		arg.p_arg = va_arg(*arg_list, void *);
		uint32_t_to_str_upper(buffer, arg.u_arg, 16);  /* print addresses as upper hex string */
		break;
	case '%':
		buffer[0] = '%';
		break;
	default:
		break;
	}
	terminal_putstring(buffer);
}


