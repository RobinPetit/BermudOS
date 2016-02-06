#ifndef BERMUDOS_STRCONV_INT_H
#define BERMUDOS_STRCONV_INT_H

#include <stdint.h>

int str_to_int(const char * restrict, int *, int);

unsigned int int_to_str_lower(char * restrict, int, int);
unsigned int int_to_str_upper(char * restrict, int, int);
unsigned int int8_t_to_str_lower(char * restrict, int8_t, int);
unsigned int int8_t_to_str_upper(char * restrict, int8_t, int);
unsigned int int16_t_to_str_lower(char * restrict, int16_t, int);
unsigned int int16_t_to_str_upper(char * restrict, int16_t, int);
unsigned int int32_t_to_str_lower(char * restrict, int32_t, int);
unsigned int int32_t_to_str_upper(char * restrict, int32_t, int);
unsigned int int64_t_to_str_lower(char * restrict, int64_t, int);
unsigned int int64_t_to_str_upper(char * restrict, int64_t, int);

unsigned int unsigned_int_to_str_lower(char * restrict, unsigned int, int);
unsigned int unsigned_int_to_str_upper(char * restrict, unsigned int, int);
unsigned int uint8_t_to_str_lower(char * restrict, uint8_t, int);
unsigned int uint8_t_to_str_upper(char * restrict, uint8_t, int);
unsigned int uint16_t_to_str_lower(char * restrict, uint16_t, int);
unsigned int uint16_t_to_str_upper(char * restrict, uint16_t, int);
unsigned int uint32_t_to_str_lower(char * restrict, uint32_t, int);
unsigned int uint32_t_to_str_upper(char * restrict, uint32_t, int);
unsigned int uint64_t_to_str_lower(char * restrict, uint64_t, int);
unsigned int uint64_t_to_str_upper(char * restrict, uint64_t, int);

#endif /* BERMUDOS_STRCONV_INT_H */
