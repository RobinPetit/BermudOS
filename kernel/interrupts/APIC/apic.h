#ifndef APIC_H
#define APIC_H

#include <stdbool.h>

#define IA32_APIC_BASE_MSR 0x1B  /* id of base register */
#define IA32_APIC_BASE_MSR_BSP 0x0100  /* Processor is a boot strap processor */
#define IA32_APIC_BASE_MSR_ENABLE 0x0800

#define CPUID_APIC_BIT (1 << 9)

bool is_apic_compatible(void);

#endif /* APIC_H */
