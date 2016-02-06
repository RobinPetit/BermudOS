extern irq_management
global irq0

section .text
irq0:
	cli
	push byte 0
	push byte 32
	jmp irq_management


