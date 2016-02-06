extern irq_management
global irq12

section .text
irq12:
	cli
	push byte 0
	push byte 44
	jmp irq_management


