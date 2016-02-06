extern irq_management
global irq11

section .text
irq11:
	cli
	push byte 0
	push byte 43
	jmp irq_management


