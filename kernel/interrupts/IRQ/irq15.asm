extern irq_management
global irq15

section .text
irq15:
	cli
	push byte 0
	push byte 47
	jmp irq_management


