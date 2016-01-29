#include <strconv/strconv.h>
#include <ctype.h>
#include <stdbool.h>

/* static prototypes */

static int int_to_str(char *restrict, int, int);
static int nb_of_digits_in_base(int, int);
static bool is_correct_digit_in_base(char, unsigned int);

static bool uses_upper = true;

/* interface functions */

int int_to_str_lower(char * restrict str, int value, int radix)
{
	uses_upper = false;
	int_to_str(str, value, radix);
}

int int_to_str_upper(char * restrict str, int value, int radix)
{
	uses_upper = true;
	int_to_str(str, value, radix);
}

int str_to_int(const char * restrict str, int *value, int radix)
{
	int i = 0;
	*value = 0;
	while(is_correct_digit_in_base(str[i], radix))
	{
		*value *= radix;
		*value += (isdigit(str[i]) ? str[i] - '0' : tolower(str[i]) - 'a' + 10);
		++i;
	}
	return i;
}

/* static functions */

#include <stdio.h>

static int int_to_str(char *restrict buffer, int value, int radix)
{
	bool negative = value < 0;
	int i = 0;
	int nb_digits = nb_of_digits_in_base(value, radix) + (negative ? 1 : 0);
	int ret = nb_digits;
	buffer[nb_digits--] = '\0';
	if(negative)
		value = -value;
	while(value > 0)
	{
		int tmp = value % radix;
		/* we know that tmp >= 0 */
		buffer[nb_digits--] = ((tmp <= 9) ? '0' + tmp : tmp-10 + (uses_upper ? 'A' : 'a'));  
		value /= radix;
	}
	if(negative)
		buffer[0] = '-';
	return ret;
}

static int nb_of_digits_in_base(int n, int radix)
{
	int divisor = 1;
	int digits = 0;
	while(n / divisor != 0)
	{
		divisor *= radix;
		++digits;
	}
	return digits;
}

static bool is_correct_digit_in_base(char digit, unsigned int radix)
{
	digit = tolower(digit);
	if(radix <= 10)
		return '0' <= digit && digit <= (radix-1) + '0';
	else
		return isdigit(digit) || ('a' <= digit && digit < (radix-1) + 'a');
}

