#ifndef IRQ_H
#define IRQ_H

#include "../idt.h"
#include <stdbool.h>

#define BERMUDOS_NB_IRQ 16

/* define actual ports for PICs */
#define MASTER_PIC_COMMAND 0x20
#define MASTER_PIC_DATA 0x21
#define SLAVE_PIC_COMMAND 0xA0
#define SLAVE_PIC_DATA 0xA1

#define END_OF_INTERRUPT_SIGNAL 0x20

bool set_irq(int, void (*)(struct interrupt_stack_state *));
bool clear_irq(int);
bool irq_setup(void);
void irq_handler(struct interrupt_stack_state *);

#endif /* IRQ_H */
