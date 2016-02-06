#include "isr.h"
#include <stdio.h>

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

bool isrs_setup(void)
{
	return idt_set_entry(0,  (uint32_t)((void *)(isr0)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(1,  (uint32_t)((void *)(isr1)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(2,  (uint32_t)((void *)(isr2)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(3,  (uint32_t)((void *)(isr3)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(4,  (uint32_t)((void *)(isr4)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(5,  (uint32_t)((void *)(isr5)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(6,  (uint32_t)((void *)(isr6)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(7,  (uint32_t)((void *)(isr7)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(8,  (uint32_t)((void *)(isr8)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(9,  (uint32_t)((void *)(isr9)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(10, (uint32_t)((void *)(isr10)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(11, (uint32_t)((void *)(isr11)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(12, (uint32_t)((void *)(isr12)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(13, (uint32_t)((void *)(isr13)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(14, (uint32_t)((void *)(isr14)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(15, (uint32_t)((void *)(isr15)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(16, (uint32_t)((void *)(isr16)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(17, (uint32_t)((void *)(isr17)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(18, (uint32_t)((void *)(isr18)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(19, (uint32_t)((void *)(isr19)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(20, (uint32_t)((void *)(isr20)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(21, (uint32_t)((void *)(isr21)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(22, (uint32_t)((void *)(isr22)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(23, (uint32_t)((void *)(isr23)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(24, (uint32_t)((void *)(isr24)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(25, (uint32_t)((void *)(isr25)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(26, (uint32_t)((void *)(isr26)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(27, (uint32_t)((void *)(isr27)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(28, (uint32_t)((void *)(isr28)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(29, (uint32_t)((void *)(isr29)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(30, (uint32_t)((void *)(isr30)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(31, (uint32_t)((void *)(isr31)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS));
}

void fault_handler(struct interrupt_stack_state *registers)
{
	if(registers->interrupt_id < 32)
	{
		printf("Exception caught: %s\n... Halting ...\n", interrupt_names[registers->interrupt_id]);
		while(true)
			;
	}
}

