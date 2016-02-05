#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define BERMUDOS_GDT_NB_ENTRY 3

#define GDT_ENTRY_DATA_SEGMENT 0x92
#define GDT_ENTRY_CODE_SEGMENT 0x9A

#define GDT_GRANULARITY(b) (b << 3)
#define GDT_PROTECTED_MODE(b) (b << 2)

#define GDT_GRANULARITY_1B GDT_GRANULARITY(0)
#define GDT_GRANULARITY_4KiB GDT_GRANULARITY(1)
#define GDT_PROTECTED_16_BIT GDT_PROTECTED_MODE(0)
#define GDT_PROTECTED_32_BIT GDT_PROTECTED_MODE(1)

struct gdt_entry  /* exactly 64 bits */
{
	union
	{
		struct
		{
			uint16_t limit_low;
			uint16_t base_low;
			uint8_t base_middle;
			uint8_t access;
			uint8_t limit_high:4;
			uint8_t granularity:4;
			uint8_t base_high;
		};
		struct
		{
			uint8_t bytes[8];
		};
	};
} __attribute__((packed));  /* GCC specification to force no padding bit */

struct gdt_pointer  /* exactly 48 bits */
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

bool gdt_setup(void);
bool gdt_set_entry(size_t, uint32_t, uint32_t, uint8_t, uint8_t);

#endif /* GDT_H */
