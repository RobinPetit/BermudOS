#include "MSR.h"
#include <cpuid.h>

bool has_MSR(void)
{
	unsigned int eax, ebx, ecx, edx;
	__get_cpuid(0x01, &eax, &ebx, &ecx, &edx);
	return (edx & CPUID_MSR_BIT) != 0;
}

uint64_t read_MSR_register(uint32_t ecx)
{
	uint32_t low, high;
	__asm__ __volatile__("rdmsr"
	                     : "=a"(low), "=d"(high)
	                     : "c"(ecx));
	return ((uint64_t)(high) << 32) | low;
}

void write_MSR_register64(uint32_t ecx, uint64_t msr_value)
{
	write_MSR_register(ecx, (uint32_t)(msr_value), (uint32_t)(msr_value >> 32));
}

void write_MSR_register(uint32_t ecx, uint32_t low, uint32_t high)
{
	__asm__ __volatile__("wrmsr"
	                     :
	                     : "a"(low), "c"(ecx), "d"(high));
}

