extern irq_management
global irq4

section .text
irq4:
	cli
	push byte 0
	push byte 36
	jmp irq_management


