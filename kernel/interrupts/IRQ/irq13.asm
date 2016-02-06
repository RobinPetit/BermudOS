extern irq_management
global irq13

section .text
irq13:
	cli
	push byte 0
	push byte 45
	jmp irq_management


