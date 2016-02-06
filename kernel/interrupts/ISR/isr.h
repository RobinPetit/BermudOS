#ifndef ISR_H
#define ISR_H

#include <stdbool.h>
#include "../idt.h"

static const char * const interrupt_names[32] =
{
	/* 0x00 */ "Division By Zero Exception",
	/* 0x01 */ "Debug Exception",
	/* 0x02 */ "Non Maskable Interrupt Exception",
	/* 0x03 */ "Breakpoint Exception",
	/* 0x04 */ "Into Detected Overflow Exception",
	/* 0x05 */ "Out Of Bounds Exception",
	/* 0x06 */ "Invalid Opcode Exception",
	/* 0x07 */ "No Coprocessor Exception",
	/* 0x08 */ "Double Fault Exception",  /* puts an error code onto the stack */
	/* 0x09 */ "Coprocessor Segment Overrun",
	/* 0x0A */ "Bad TSS Exception",  /* puts an error code onto the stack */
	/* 0x0B */ "Segment Not Present Exception",  /* puts an error code onto the stack */
	/* 0x0C */ "Stack Fault Exception",  /* puts an error code onto the stack */
	/* 0x0D */ "General Protection Fault Exception",  /* puts an error code onto the stack */
	/* 0x0E */ "Page Fault Exception",  /* puts an error code onto the stack */
	/* 0x0F */ "Unknown Interrupt Exception",
	/* 0x10 */ "Coprocessor Fault",
	/* 0x11 */ "Alignment Check Exception",
	/* 0x12 */ "Machine Check Exception",
	/* 0x13 */ "Reserved Exception 0x13",
	/* 0x14 */ "Reserved Exception 0x14",
	/* 0x15 */ "Reserved Exception 0x15",
	/* 0x16 */ "Reserved Exception 0x16",
	/* 0x17 */ "Reserved Exception 0x17",
	/* 0x18 */ "Reserved Exception 0x18",
	/* 0x19 */ "Reserved Exception 0x19",
	/* 0x1A */ "Reserved Exception 0x1A",
	/* 0x1B */ "Reserved Exception 0x1B",
	/* 0x1C */ "Reserved Exception 0x1C",
	/* 0x1D */ "Reserved Exception 0x1D",
	/* 0x1E */ "Reserved Exception 0x1E",
	/* 0x1F */ "Reserved Exception 0x1F"
};

bool isrs_setup(void);
void fault_handler(struct interrupt_stack_state *);

#endif /* ISR_H */
