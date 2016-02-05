#ifndef SPRINTF_H
#define SPRINTF_H

#define ASTERISK  (1 << (sizeof(BYTE)*8 - 1))
#define NOT_MENTIONNED (1 << (sizeof(BYTE)*8 - 2))

struct sprintf_arg_s
{
	BYTE flags;            /* see sprintf_flags_e */
	BYTE width;            /* minimal number of printed characters (padding) */
	BYTE precision;        /* minimal number of decimal places */
	BYTE len_modifier;     /* see sprintf_length_modifier_e */
	char conversion_spec;  /* format value (d, x, c, etc.) */
};

enum sprintf_flags_e
{
	MINUS = 1 << 0,  /* left justifies */
	PLUS = 1 << 1,   /* forces to sign the value */
	SPACE = 1 << 2,  /* adds a space if no sign is written */
	SHARP = 1 << 3,  /* explicits the base the number is written in */
	ZERO = 1 << 4    /* uses '0' as padding instead of ' ' */
};

enum sprintf_length_modifier_e
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

#endif /* SPRINTF_H */
