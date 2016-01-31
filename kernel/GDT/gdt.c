#include "gdt.h"

#define GDT_SET_BASE(gdt, address, index) \
	gdt[index].base_low    =  address        & 0xFFFF; \
	gdt[index].base_middle = (address >> 16) & 0xFF; \
	gdt[index].base_high   = (address >> 24) & 0xFF;

struct gdt_entry kernel_GDT[BERMUDOS_GDT_NB_ENTRY];
struct gdt_pointer gdt_location;

bool gdt_setup(void)
{
	bool status;
	gdt_location.limit = (sizeof(struct gdt_entry) * BERMUDOS_GDT_NB_ENTRY) - 1;
	gdt_location.base = (uint32_t)&kernel_GDT;

	status = gdt_set_entry(0, (uint32_t)(NULL), 0, 0, 0)  /* The GDT MUST start with a NULL entry */
		&& gdt_set_entry(1, (uint32_t)(NULL), 0xFFFFFFFF, GDT_ENTRY_DATA_SEGMENT, GDT_GRANULARITY_4KiB | GDT_PROTECTED_32_BIT)
		&& gdt_set_entry(2, (uint32_t)(NULL), 0xFFFFFFFF, GDT_ENTRY_CODE_SEGMENT, GDT_GRANULARITY_4KiB | GDT_PROTECTED_32_BIT);
	gdt_flush();
	return status;
}

bool gdt_set_entry(size_t idx, uint32_t base, uint32_t limit,
		uint8_t access, uint8_t granularity)
{
	if(idx >= BERMUDOS_GDT_NB_ENTRY)
		return false;
	GDT_SET_BASE(kernel_GDT, base, idx);
	kernel_GDT[idx].limit_low = limit & 0xFFFF;
	kernel_GDT[idx].limit_high = (limit >> 16) & 0x0F;
	kernel_GDT[idx].granularity = granularity;
	kernel_GDT[idx].access = access;
	return true;
}

