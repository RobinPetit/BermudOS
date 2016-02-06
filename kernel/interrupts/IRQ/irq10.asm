extern irq_management
global irq10

section .text
irq10:
	cli
	push byte 0
	push byte 42
	jmp irq_management


