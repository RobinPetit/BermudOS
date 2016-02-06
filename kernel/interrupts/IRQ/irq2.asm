extern irq_management
global irq2

section .text
irq2:
	cli
	push byte 0
	push byte 34
	jmp irq_management


