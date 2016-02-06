#ifndef BERMUDOS_DIV64_H
#define BERMUDOS_DIV64_H

/* inspired from linux repository */

#define do_div(dividend, divisor)                             \
({                                                            \
	uint32_t __upper, __low, __high, __remainder, __divisor;  \
	__divisor = (divisor);                                    \
	asm(""                                                    \
	    : "=a" (__low), "=d" (__high) :                       \
		"A" (dividend));                                      \
	if ((__upper = __high) != 0)                              \
	{                                                         \
		__upper = __high % (__divisor);	                      \
		__high = __high / (__divisor);                        \
	}                                                         \
	asm("divl %2"                                             \
	    : "=a" (__low), "=d" (__remainder)                    \
		: "rm" (__divisor), "0" (__low), "1" (__upper));      \
	asm("" : "=A" (dividend) : "a" (__low), "d" (__high));    \
	/* return */ __remainder;                                 \
})

#endif /* BERMUDOS_DIV64_H */
