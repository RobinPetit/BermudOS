extern irq_management
global irq6

section .text
irq6:
	cli
	push byte 0
	push byte 38
	jmp irq_management


