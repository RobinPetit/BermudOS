extern irq_management
global irq3

section .text
irq3:
	cli
	push byte 0
	push byte 35
	jmp irq_management


