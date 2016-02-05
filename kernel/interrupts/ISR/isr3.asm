extern isr_management
global isr3

section .text
isr3:
	cli
	push byte 0
	push byte 3

	jmp isr_management


