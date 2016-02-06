#include "irq.h"
#include "../../../io/out.h"

#define PIC_INITIALIZATION 0x11
#define IS_MASTER_PIC_IRQ(idx) (((idx)-0x20) < 8)
#define IS_SLAVE_PIC_IRQ(idx) (!IS_MASTER_PIC_IRQ(idx))

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

/* static prototypes */
static void irq_remap(void);

/* init as no IRQ */
static void *irq_routines[BERMUDOS_NB_IRQ] =
{
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL
};

bool set_irq(int idx, void (*function)(struct interrupt_stack_state *))
{
	if(idx >= BERMUDOS_NB_IRQ)
		return false;
	irq_routines[idx] = function;
	return true;
}

bool clear_irq(int idx)
{
	if(idx >= BERMUDOS_NB_IRQ)
		return false;
	irq_routines[idx] = NULL;
	return true;
}

/* PIC controller is programmable: move IRQs 0 -> 15 as interrupts 32 -> 47 */
static void irq_remap(void)
{
	/* send message to both PICS controllers so they are waiting for 3 next data bytes */
	outb(MASTER_PIC_DATA, PIC_INITIALIZATION);
	outb(SLAVE_PIC_DATA, PIC_INITIALIZATION);

	/* first data byte is new offset */
	outb(MASTER_PIC_DATA, 0x20);  /* IRQs 0 -> 7  are redirected to IDT at idx 32 -> 39 */
	outb(SLAVE_PIC_DATA, 0x28);   /* IRQs 8 -> 15 are redirected to IDT at idx 40 -> 47 */

	/* second data byte is wiring information */
	outb(MASTER_PIC_DATA, 0x04);  /* tells to MASTER_PIC that SLAVE_PIC is ar IRQ 2 */
	outb(SLAVE_PIC_DATA, 0x02);   /* tells SLAVE_PIC its identity */

	/* third data byte is environment information */
	outb(MASTER_PIC_DATA, 0x00);  /* clears information byte */
	outb(SLAVE_PIC_DATA, 0x00);   /* idem */
}

bool irq_setup(void)
{
	irq_remap();
	return idt_set_entry(0x20, (uint32_t)((void *)(irq0)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x21, (uint32_t)((void *)(irq1)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x22, (uint32_t)((void *)(irq2)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x23, (uint32_t)((void *)(irq3)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x24, (uint32_t)((void *)(irq4)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x25, (uint32_t)((void *)(irq5)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x26, (uint32_t)((void *)(irq6)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x27, (uint32_t)((void *)(irq7)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x28, (uint32_t)((void *)(irq8)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x29, (uint32_t)((void *)(irq9)),  CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x2A, (uint32_t)((void *)(irq10)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x2B, (uint32_t)((void *)(irq11)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x2C, (uint32_t)((void *)(irq12)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x2D, (uint32_t)((void *)(irq13)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x2E, (uint32_t)((void *)(irq14)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS))
		&& idt_set_entry(0x2F, (uint32_t)((void *)(irq15)), CODE_SEGMENT, MAKE_IDT_FLAG(SEGMENT_PRESENT, RING_OS));
}

void irq_handler(struct interrupt_stack_state *registers)
{
	void (*handler)(struct interrupt_stack_state *) = irq_routines[registers->interrupt_id - 32];
	if(handler != NULL)
		handler(registers);
	/* if irq is slave, then send EOI to SLAVE_PIC */
	if(IS_SLAVE_PIC_IRQ(registers->interrupt_id))
		outb(SLAVE_PIC_COMMAND, END_OF_INTERRUPT_SIGNAL);
	/* send EOI to MASTER_PIC anyway */
	outb(MASTER_PIC_COMMAND, END_OF_INTERRUPT_SIGNAL);
}

