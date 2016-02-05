extern isr_management
global isr31

section .text
isr31:
	cli
	push byte 0
	push byte 31

	jmp isr_management


