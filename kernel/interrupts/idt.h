#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define BERMUDOS_IDT_NB_ENTRY 0x0100

struct idt_entry
{
	uint16_t base_low;
	uint16_t segment;
	uint8_t null_padding;  /* MAY NOT be something else than 0 */
	uint8_t const_padding:5;  /* MAY NTO be something else than 0b01110 */
	uint8_t flags:3;
	uint16_t base_high;
} __attribute__((packed));

struct idt_pointer
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

void idt_load(void);
bool idt_set_entry(size_t, uint32_t, uint16_t, uint8_t);
bool idt_setup(void);

#endif  /* IDCT_H */
