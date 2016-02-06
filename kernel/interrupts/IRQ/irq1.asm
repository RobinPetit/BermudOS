extern irq_management
global irq1

section .text
irq1:
	cli
	push byte 0
	push byte 33
	jmp irq_management


