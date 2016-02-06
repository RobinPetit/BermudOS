extern irq_management
global irq5

section .text
irq5:
	cli
	push byte 0
	push byte 37
	jmp irq_management


