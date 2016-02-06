extern irq_management
global irq14

section .text
irq14:
	cli
	push byte 0
	push byte 46
	jmp irq_management


