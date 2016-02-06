extern irq_management
global irq8

section .text
irq8:
	cli
	push byte 0
	push byte 40
	jmp irq_management


