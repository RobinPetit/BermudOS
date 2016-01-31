#include <cpuid.h>
#include "apic.h"
#include <stdbool.h>
#include <stdint.h>
#include "../../MSR/MSR.h"

bool is_apic_compatible(void)
{
	unsigned int eax, ebx, ecx, edx;
	__get_cpuid(0x01, &eax, &ebx, &ecx, &edx);
	return (edx & CPUID_APIC_BIT) != 0;
}

void set_apic_base(uint32_t apic_base) {
	uint32_t low = (apic_base & 0xFFFFF100) | IA32_APIC_BASE_MSR_ENABLE;
	write_MSR_register(IA32_APIC_BASE_MSR, low, 0);
}
			   
uint32_t get_apic_base(void) {
	return (uint32_t)(read_MSR_register(IA32_APIC_BASE_MSR)) & 0xFFFFF000;
}

