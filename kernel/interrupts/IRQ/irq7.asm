extern irq_management
global irq7

section .text
irq7:
	cli
	push byte 0
	push byte 39
	jmp irq_management


