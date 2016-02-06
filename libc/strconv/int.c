#include <strconv/strconv.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
/* #include <div64.h> */  /* find a way to make 64 bit division in 32 bit mode */

/* static prototypes */

static unsigned int int_to_str(char *restrict, int, int);
static unsigned int int8_t_to_str(char * restrict, int8_t, int);
static unsigned int int16_t_to_str(char * restrict, int16_t, int);
static unsigned int int32_t_to_str(char * restrict, int32_t, int);
static unsigned int int64_t_to_str(char * restrict, int64_t, int);
static unsigned int unsigned_int_to_str(char * restrict, unsigned int, int);
static unsigned int uint8_t_to_str(char * restrict, uint8_t, int);
static unsigned int uint16_t_to_str(char * restrict, uint16_t, int);
static unsigned int uint32_t_to_str(char * restrict, uint32_t, int);
static unsigned int uint64_t_to_str(char * restrict, uint64_t, int);
static unsigned int nb_of_digits_in_base(uint64_t, int);
static bool is_correct_digit_in_base(char, unsigned int);

static bool uses_upper = true;

/* interface functions */

unsigned int int_to_str_lower(char * restrict buffer, int value, int radix)
{
	uses_upper = false;
	return int_to_str(buffer, value, radix);
}

unsigned int int_to_str_upper(char * restrict buffer, int value, int radix)
{
	uses_upper = true;
	return int_to_str(buffer, value, radix);
}

unsigned int int8_t_to_str_lower(char * restrict buffer, int8_t value, int radix)
{
	uses_upper = false;
	return int8_t_to_str(buffer, value, radix);
}

unsigned int int8_t_to_str_upper(char * restrict buffer, int8_t value, int radix)
{
	uses_upper = true;
	return int8_t_to_str(buffer, value, radix);
}

unsigned int int16_t_to_str_lower(char * restrict buffer, int16_t value, int radix)
{
	uses_upper = false;
	return int16_t_to_str(buffer, value, radix);
}

unsigned int int16_t_to_str_upper(char * restrict buffer, int16_t value, int radix)
{
	uses_upper = true;
	return int16_t_to_str(buffer, value, radix);
}

unsigned int int32_t_to_str_lower(char * restrict buffer, int32_t value, int radix)
{
	uses_upper = false;
	return int32_t_to_str(buffer, value, radix);
}

unsigned int int32_t_to_str_upper(char * restrict buffer, int32_t value, int radix)
{
	uses_upper = true;
	return int32_t_to_str(buffer, value, radix);
}

unsigned int int64_t_to_str_lower(char * restrict buffer, int64_t value, int radix)
{
	uses_upper = false;
	return int64_t_to_str(buffer, value, radix);
}

unsigned int int64_t_to_str_upper(char * restrict buffer, int64_t value, int radix)
{
	uses_upper = true;
	return int64_t_to_str(buffer, value, radix);
}

unsigned int unsigned_int_to_str_lower(char * restrict buffer, unsigned int value, int radix)
{
	uses_upper = false;
	return unsigned_int_to_str(buffer, value, radix);
}

unsigned int unsigned_int_to_str_upper(char * restrict buffer, unsigned int value, int radix)
{
	uses_upper = true;
	return unsigned_int_to_str(buffer, value, radix);
}

unsigned int uint8_t_to_str_lower(char * restrict buffer, uint8_t value, int radix)
{
	uses_upper = false;;
	return uint8_t_to_str(buffer, value, radix);
}

unsigned int uint8_t_to_str_upper(char * restrict buffer, uint8_t value, int radix)
{
	uses_upper = true;
	return uint8_t_to_str(buffer, value, radix);
}

unsigned int uint16_t_to_str_lower(char * restrict buffer, uint16_t value, int radix)
{
	uses_upper = false;
	return uint16_t_to_str(buffer, value, radix);
}

unsigned int uint16_t_to_str_upper(char * restrict buffer, uint16_t value, int radix)
{
	uses_upper = true;
	return uint16_t_to_str(buffer, value, radix);
}

unsigned int uint32_t_to_str_lower(char * restrict buffer, uint32_t value, int radix)
{
	uses_upper = false;
	return uint32_t_to_str(buffer, value, radix);
}

unsigned int uint32_t_to_str_upper(char * restrict buffer, uint32_t value, int radix)
{
	uses_upper = true;
	return uint32_t_to_str(buffer, value, radix);
}

unsigned int uint64_t_to_str_lower(char * restrict buffer, uint64_t value, int radix)
{
	uses_upper = false;
	return uint64_t_to_str(buffer, value, radix);
}

unsigned int uint64_t_to_str_upper(char * restrict buffer, uint64_t value, int radix)
{
	uses_upper = true;
	return uint64_t_to_str(buffer, value, radix);
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

static unsigned int int_to_str(char *restrict buffer, int value, int radix)
{
	return int32_t_to_str(buffer, (int32_t)(value), radix);
}

static unsigned int int8_t_to_str(char * restrict buffer, int8_t value, int radix)
{
	return int32_t_to_str(buffer, (int32_t)(value), radix);
}

static unsigned int int16_t_to_str(char * restrict buffer, int16_t value, int radix)
{
	return int32_t_to_str(buffer, (int32_t)(value), radix);
}

static unsigned int int32_t_to_str(char * restrict buffer, int32_t value, int radix)
{
	unsigned int ret;
	bool negative = value < 0;
	ret = uint32_t_to_str(buffer + (negative ? 1 : 0), (uint32_t)(negative ? -value : value), radix);
	if(negative)
		buffer[0] = '-';
	return ret;
}

static unsigned int int64_t_to_str(char * restrict buffer, int64_t value, int radix)
{
	unsigned int ret;
	bool negative = value < 0;
	ret = uint64_t_to_str(buffer + (negative ? 1 : 0), (uint64_t)(negative ? -value : value), radix);
	if(negative)
		buffer[0] = '-';
	return ret;
}

static unsigned int unsigned_int_to_str(char * restrict buffer, unsigned int value, int radix)
{
	return uint32_t_to_str(buffer, (uint32_t)(value), radix);
}

static unsigned int uint8_t_to_str(char * restrict buffer, uint8_t value, int radix)
{
	return uint32_t_to_str(buffer, (uint32_t)(value), radix);
}

static unsigned int uint16_t_to_str(char * restrict buffer, uint16_t value, int radix)
{
	return uint32_t_to_str(buffer, (uint32_t)(value), radix);
}

static unsigned int uint32_t_to_str(char * restrict buffer, uint32_t value, int radix)
{
	unsigned int nb_digits = nb_of_digits_in_base(value, radix);
	unsigned int ret = nb_digits;
	buffer[nb_digits--] = '\0';
	while(value != 0)
	{
		uint32_t tmp = value % radix;
		buffer[nb_digits--] = ((tmp <= 9) ? '0' + tmp : tmp-10 + (uses_upper ? 'A' : 'a'));
		value /= radix;
	}
	return ret;
}

static unsigned int uint64_t_to_str(char * restrict buffer, uint64_t value, int radix)
{
	unsigned int nb_digits = nb_of_digits_in_base(value, radix);
	unsigned int ret = nb_digits;
	buffer[nb_digits--] = '\0';
	while(value != 0)
	{
		uint32_t tmp = do_div(value, radix);
		buffer[nb_digits--] = ((tmp <= 9) ? '0' + tmp : tmp-10 + (uses_upper ? 'A' : 'a'));
	}
	return ret;
}

static unsigned int nb_of_digits_in_base(uint64_t n, int radix)
{
	unsigned int digits = 0;
	while(n != 0)
	{
		do_div(n, radix);
		++digits;
	}
	return digits;
}

static bool is_correct_digit_in_base(char digit, unsigned int radix)
{
	digit = tolower(digit);
	if(radix <= 10)
		return '0' <= digit && digit <= (char)((radix-1) + '0');
	else
		return isdigit(digit) || ('a' <= digit && digit < (char)((radix-10) + 'a'));
}

