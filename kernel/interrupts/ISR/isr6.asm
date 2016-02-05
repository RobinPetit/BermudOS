extern isr_management
global isr6

section .text
isr6:
	cli
	push byte 0
	push byte 6

	jmp isr_management


