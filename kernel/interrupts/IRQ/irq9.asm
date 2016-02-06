extern irq_management
global irq9

section .text
irq9:
	cli
	push byte 0
	push byte 41
	jmp irq_management


