#include "idt.h"
#include <string.h>

struct idt_entry kernel_IDT[BERMUDOS_IDT_NB_ENTRY];
struct idt_pointer idt_location;

void idt_load(void)
{
	__asm__ __volatile__ ("lidt %0":: "m"(idt_location));
}

bool idt_set_entry(size_t idx, uint32_t base, uint16_t seg, uint8_t flags)
{
	if(idx >= BERMUDOS_IDT_NB_ENTRY)
		return false;
	kernel_IDT[idx].base_low = (uint16_t)(base);
	kernel_IDT[idx].base_high = (uint16_t)(base >> 16);
	kernel_IDT[idx].segment = seg;
	kernel_IDT[idx].null_padding = 0;
	kernel_IDT[idx].const_padding = 0x0E;
	kernel_IDT[idx].flags = flags & 0x03;
	return true;
}

bool idt_setup(void)
{
	idt_location.limit = (sizeof(struct idt_entry) * BERMUDOS_IDT_NB_ENTRY) - 1;
	idt_location.base = (uint32_t)(&kernel_IDT);
	memset(&kernel_IDT, 0, sizeof(struct idt_entry) * BERMUDOS_IDT_NB_ENTRY);
	idt_load();
	return true;
}

