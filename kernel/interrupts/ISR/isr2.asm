extern isr_management
global isr2

section .text
isr2:
	cli
	push byte 0
	push byte 2

	jmp isr_management


