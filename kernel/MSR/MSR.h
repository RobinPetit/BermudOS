#ifndef MSR_H
#define MSR_H

#include <stdbool.h>
#include <stdint.h>

#define CPUID_MSR_BIT (1 << 5)

bool has_MSR(void);
uint64_t read_MSR_register(uint32_t);
void write_MSR_register(uint32_t, uint32_t, uint32_t);
void write_MSR_register64(uint32_t, uint64_t);

#endif /* MSR_H */
